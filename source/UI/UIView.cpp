#include <Nephilim/UI/UIView.h>
#include <Nephilim/UI/UxEvent.h>

#include <Nephilim/Graphics/VertexArray.h>
#include <Nephilim/Graphics/GL/GLHelpers.h>

#include <Nephilim/UI/UIController.h>
#include <Nephilim/Foundation/StringList.h>
#include <Nephilim/Foundation/Logging.h>

#include <Nephilim/UI/UILoaderXML.h>

#include <algorithm>

NEPHILIM_NS_BEGIN

UIView::UIView()
: RefCountable()
, position(0.f, 0.f, 0.f)
, m_parent(NULL)
, m_childrenLock(0)
, m_hasFocus(false)
, m_clipChildren(false)
, m_clipContents(false)
, m_visible(true)
, m_hovered(false)
, m_pointerPressCount(0)
{
	rotation_x = rotation_y = rotation_z = 0.f;

	mFlags = 0;
}


/// Construct and assign a parent directly
UIView::UIView(UIView* parent)
: RefCountable()
, m_parent(parent)
, m_childrenLock(0)
, m_hasFocus(false)
, m_clipChildren(false)
, m_clipContents(false)
, m_visible(true)
, m_hovered(false)
, m_pointerPressCount(0)
{
	if(parent)
	{
		parent->attach(this);
	}
}

/// Called on subclasses to draw custom stuff
void UIView::onPaint(UIPainter& painter){}

/// Called when the view receives a mouse/touch related event
void UIView::onPointerEvent(const UIPointerEvent& event){}

UIView::~UIView()
{
	// Release all components to prevent leaks
	for(std::size_t i = 0; i < components.size(); ++i)
	{
		components[i]->onRelease(this);
		delete components[i];
	}

	// I am being destroyed, destroy children
	for(std::size_t i = 0; i < m_children.size(); ++i)
	{
		delete m_children[i];
	}
}

//#include <Nephilim/UI/UIComponentTouchScroll.h>

/// Creates a new UIView, names it and attaches it as a child, then returns it
UIView* UIView::createChild(const String& name)
{
	// Instance a new view
	UIView* view = new UIView();
	view->setName(name);

	// Attach
	attach(view);

	view->onSetup();

	return view;
}

/// Set a new size to the widget
void UIView::setSize(Vector2D _size)
{
	setSize(_size.x, _size.y);
}

/// Get the current width of this widget
float UIView::width()
{
	return size.x;
}

/// Get the current height of this widget
float UIView::height()
{
	return size.y;
}

/// Refresh the visual styles on this view
void UIView::updateStyles()
{
	for (auto it = components.begin(); it != components.end(); ++it)
	{
		(*it)->updateStyles();
	}
}

/// Set styles directly to the view
void UIView::setStyleSheet(const String& stylesheet)
{

}

/// Load the hierarchy of this view from a file and configure itself
void UIView::load(const String& filename)
{
	Log("=> LOADING XML FILE INTO THE UI");
	UILoaderXML uiLoader;
	uiLoader.loadFromFile(filename, this);
}

void UIView::setProperty(const String& str)
{
	StringList fields = str.split('=');
	if(fields.size() == 2)
	{
		while(fields[0].size() > 0 && fields[0].at(fields[0].size()-1) == ' ')
			fields[0].erase(fields[0].size()-1);

		StringList target_object = fields[0].split('.');


		String paramValue = fields[1];
		while(paramValue.size() > 0 && paramValue[0] == ' ')
			paramValue.erase(paramValue.begin());

		for(std::size_t i = 0; i < components.size(); ++i)
		{
			components[i]->onPropertySet(target_object, paramValue);
		}
}	
}

/// Add a component to the view
void UIView::addController(UIController* component)
{
	if(!component)
		return;

	components.push_back(component);
	component->mParent = this;
	component->onAttach(this);
}

/// Set any flags for the view
void UIView::setFlag(Uint32 flags)
{
	mFlags |= flags;
}

bool UIView::hasFlags(Uint32 flags)
{
	return (mFlags & flags) == flags;
}


void UIView::addStringProperty(const String& propertyName, const String& propertyValue)
{
	mStringProperties[propertyName] = propertyValue;
}

String UIView::getStringProperty(const String& propertyName)
{
	return mStringProperties[propertyName];
}

/// Called before rendering the children UIView ( Virtual )
void UIView::preRender(GraphicsDevice* renderer){}

/// Called after rendering the children UIView ( Virtual )
void UIView::postRender(GraphicsDevice* renderer){}

void UIView::setPosition(float x, float y)
{
	// Offset children
	vec2 offset = vec2(x,y) - getPosition();

	onPositionChanged();

	// update the correct vars
	position.x = x;
	position.y = y;
}

void UIView::setPosition(vec2 position)
{
	setPosition(position.x, position.y);
}

vec2 UIView::getPosition()
{
	return vec2(position.x, position.y);
}

void UIView::setLocalPosition(float x, float y)
{
	UIView* parent = getParent();
	if(parent)
	{
		setPosition(parent->getPosition() + vec2(x,y));
	}
}

void UIView::setLocalPosition(vec2 localPosition)
{
	setLocalPosition(localPosition.x, localPosition.y);
}

vec2 UIView::getLocalPosition()
{
	UIView* parent = getParent();
	
	if(!parent)
		return vec2(0.f, 0.f);

	return getPosition() - parent->getPosition();
}

void UIView::detach(UIView* control)
{
	if(!control)
		return;

	if(m_childrenLock > 0)
	{
		// schedule
		UIControlOperation op;
		op.type = UIControlOperation::Detachment;
		op.control = control;
		m_pendingOperations.push_back(op);
	}
	else
	{
		m_children.erase(std::find(m_children.begin(), m_children.end(), control));
	}
}

/// Destroy all children, needs revising
void UIView::clear()
{
	if(m_childrenLock > 0)
	{
		// Post pone the clearing
		for(std::size_t i = 0; i < m_children.size(); ++i)
		{
			UIControlOperation action;
			action.control = m_children[i];
			action.type = UIControlOperation::Destruction;
			m_pendingOperations.push_back(action);
		}
	}
	else
	{
		// I am being destroyed, destroy children
		for(std::size_t i = 0; i < m_children.size(); ++i)
		{
			delete m_children[i];
		}

		m_children.clear();
	}
}

/// Feeds the position of the control to the animation systems
vec2 UIView::axGetPosition2D()
{
	return getPosition();
}

void UIView::axSetPosition2D(vec2 position)
{
	setPosition(position.x, position.y);
}

void UIView::axSetAlpha(float alpha)
{
	
}

float UIView::axGetAlpha()
{
	return 1.f;
}

void UIView::axKillTrigger()
{
	destroy();
}

void UIView::offsetChildrenPosition(vec2 offset)
{
	for(std::size_t i = 0; i < m_children.size(); ++i)
	{
		m_children[i]->setPosition(m_children[i]->getPosition() + offset);
	}
}

/// Set the new Z value
void UIView::setZ(float _z)
{
	position.z = _z;
	//Log("Z set to %f", _z);
}

/// This function allows to start an animation out of its definition file
void UIView::startAnimation(const String& animationAsset)
{
	UIAnimationLoaderXML loader;
	Animation* anim = loader.load(animationAsset, this);
	if (anim)
	{
		commitAnimation(anim);
	}
}

void UIView::commitAnimation(Animation* animation)
{
	animation->addTarget(this);
	animation->deduceInitialParameters();
	m_animations.commit(animation);
}

bool UIView::hasAnimatedChildren()
{
	for(std::size_t i = 0; i < m_children.size(); ++i)
	{
		if(m_children[i]->hasAnimations())
		{
			return true;
		}
		else if(m_children[i]->hasAnimatedChildren())
			return true;
	}

	return false;
}

/// Check if this control has any animation going on
bool UIView::hasAnimations()
{
	return m_animations.m_animations.size() > 0;
}


void UIView::onChildRemoved(UIView* control)
{

}

void UIView::printHierarchy(int tabs)
{
	String tabss;
	for(int i = 0; i < tabs; ++i)
		tabss += "\t";

	Log("%s: %s", tabss.c_str(), getName());

	for(std::size_t i = 0; i < m_children.size(); ++i)
	{
		if(!isScheduledForRemoval(m_children[i]))
			m_children[i]->printHierarchy(tabs + 1);
	}

	for(std::vector<UIControlOperation>::iterator it = m_pendingOperations.begin(); it != m_pendingOperations.end(); ++it)
	{
		if(it->type == UIControlOperation::Attachment)
			it->control->printHierarchy(tabs + 1);
	}
}

bool UIView::isScheduledForRemoval(UIView* v)
{
	for(std::vector<UIControlOperation>::iterator it = m_pendingOperations.begin(); it != m_pendingOperations.end(); ++it)
	{
		if(it->type == UIControlOperation::Destruction && it->control == v)
			return true;
	}

	return false;
}

/// Requests a tool tip text label from the control
/// If only a empty string is returned, no tooltip is shown
String UIView::getToolTipLabel(){
	return "";
};

/// Get the number of children of this control
int UIView::getChildCount()
{
	return static_cast<int>(m_children.size());
};

/// Get a child at a index
UIView* UIView::getChild(int index)
{
	return m_children[index];
};

/// Get the current size of the control
vec2 UIView::getSize()
{
	return size;
}

/// Callback to render itself, renders children
void UIView::draw(GraphicsDevice* renderer, mat4 transform)
{
	/*VertexArray va;
	va.addAttribute(sizeof(float), 2, VertexFormat::Position);
	va.addAttribute(sizeof(float), 4, VertexFormat::Color);
	va.allocateData(6);

	struct vertex_f
	{
		vec2 p;
		vec4 c;
	};

	vertex_f* va_raw = reinterpret_cast<vertex_f*>(&va.data[0]);

	va_raw[0].p = vec2(size.x, 0.f);
	va_raw[1].p = vec2(size.x, size.y);
	va_raw[2].p = vec2(0.f, size.y);

	va_raw[3].p = vec2(size.x, 0.f);
	va_raw[4].p = vec2(0.f, size.y);
	va_raw[5].p = vec2(0.f, 0.f);

	va_raw[0].c = vec4(float(col.r) / 255.f, float(col.g) / 255.f, float(col.b) / 255.f, float(col.a) / 255.f);
	va_raw[1].c = vec4(float(col.r) / 255.f, float(col.g) / 255.f, float(col.b) / 255.f, float(col.a) / 255.f);
	va_raw[2].c = vec4(float(col.r) / 255.f, float(col.g) / 255.f, float(col.b) / 255.f, float(col.a) / 255.f);
	va_raw[3].c = vec4(float(col.r) / 255.f, float(col.g) / 255.f, float(col.b) / 255.f, float(col.a) / 255.f);
	va_raw[4].c = vec4(float(col.r) / 255.f, float(col.g) / 255.f, float(col.b) / 255.f, float(col.a) / 255.f);
	va_raw[5].c = vec4(float(col.r) / 255.f, float(col.g) / 255.f, float(col.b) / 255.f, float(col.a) / 255.f);

	renderer->enableVertexAttribArray(0);
	renderer->enableVertexAttribArray(1);

	renderer->setVertexAttribPointer(0, 2, GL_FLOAT, false, va.getVertexSize(), &va.data[0] + va.getAttributeOffset(0));
	renderer->setVertexAttribPointer(1, 4, GL_FLOAT, false, va.getVertexSize(), &va.data[0] + va.getAttributeOffset(1));

	renderer->setModelMatrix(transform);
	renderer->setDefaultTexture();
	renderer->drawArrays(Render::Primitive::Triangles, 0, 6);

	renderer->disableVertexAttribArray(0);
	renderer->disableVertexAttribArray(1);
	*/

	//renderer->setModelMatrix(transform);
}

void UIView::dispatchEvent(const Event& event)
{
	// -- No handling of the event in this control or its children
	if(!m_visible)
	{
		return;
	}

	/// Create a modifiable event, pass it to the control for possible alteration
	Event modEvent = event;
	onEventNotification(modEvent);

	if (event.isPointerType())
	{
		UIPointerEvent pointerEvent;
		pointerEvent.windowSpace = event.getPointerPosition();

		if (event.isPointerPressed())
		{
			pointerEvent.eventType = UIPointerEvent::Pressed;
			pointerEvent.effectingButton = event.mouseButton.button;
		}
		else if (event.isPointerReleased())
		{
			pointerEvent.eventType = UIPointerEvent::Released;
			pointerEvent.effectingButton = event.mouseButton.button;
		}
		else
		{
			pointerEvent.eventType = UIPointerEvent::Moved;
		}

		onPointerEvent(pointerEvent);
	}

	m_childrenLock++;
	for(std::vector<UIView*>::iterator it = m_children.begin(); it != m_children.end(); ++it)
	{
		(*it)->dispatchEvent(modEvent);
	}
	m_childrenLock--;

	if(m_childrenLock == 0)
		applyPendingOperations();

	if(event.type == Event::KeyPressed)
	{
		if(event.key.code == Keyboard::Down && getName() == "gringo")
		{
			offsetChildrenPosition(vec2(0.f, -10.f));
		}
		if(event.key.code == Keyboard::Up && getName() == "gringo")
		{
			offsetChildrenPosition(vec2(0.f, 10.f));
		}
	}

	// -- deliver events to the components
	for(std::size_t i = 0; i < components.size(); ++i)
	{
		components[i]->onEvent(event, this);
	}
}

bool UIView::onEventNotification(Event& event)
{
	
	return false;
};

/// Is the control able to get input focus or not?
bool UIView::isFocusable()
{
	return false;
};

/// Attempts focus on this control
bool UIView::focus()
{
	// Fails to get focus if it is not focusable
	if(!isFocusable()) return false;

	if(getCore())
	{
		getCore()->m_focusControl = this;
		m_hasFocus = true;
	}
	else
	{
		//cout<<"Cant focus an element without a hierarchy"<<endl;
	}

	return true;
};

/// Check if the control currently has focus
bool UIView::hasFocus()
{
	return m_hasFocus;
};

/// Hierarchicly sets the context to all children
void UIView::setContext(UICore* states)
{
	_core = states;

	for(std::vector<UIView*>::iterator it = m_children.begin(); it != m_children.end(); ++it)
	{
		(*it)->setContext(states);
	}
}

/// Remove focus from the element
void UIView::blur()
{
	m_hasFocus = false;
};

bool UIView::onKeyPressed(Keyboard::Key key)
{

	return false;
}

bool UIView::onTextEvent(Uint32 code)
{
	return false;
};

/// Reload all graphics because they were destroyed and are unavailable now
void UIView::reloadGraphicalAssets()
{
//	TESTLOG("GL REQUIRES")

	for(std::vector<UIView*>::iterator it = m_children.begin(); it != m_children.end(); it++){
		// lets see!
		(*it)->reloadGraphicalAssets();
	}
}

/// Move the widget around, relative to where it currently is
void UIView::move(float x, float y)
{
	setPosition(getPosition() + vec2(x, y));
}

/// Process a mouve movement event
/// Returns false if the mouse isnt on any control
bool UIView::processMouseMove(int x, int y)
{
	if(!m_visible)
	{
		return true;
	}

	onMouseMove();

	for(std::vector<UIView*>::iterator it = m_children.begin(); it != m_children.end(); it++)
	{
		FloatRect controlRect = (*it)->getRect();
		FloatRect testRect(controlRect.left, controlRect.top, controlRect.width - 1, controlRect.height - 1);

		(*it)->processMouseMove(x,y);

		//if (testRect.contains(x, y))
		if ((*it)->isHit(vec2(x, y)))
		{
			if (!(*it)->m_hovered)
			{
				(*it)->setPseudoClass("hover", true);
				(*it)->m_hovered = true;
				(*it)->onMouseEnter();
			}
		}

		else
		{
			// mouse is not in it, is it just leaving now?
			if ((*it)->m_hovered)
			{
				(*it)->setPseudoClass("hover", false);
				(*it)->onMouseLeave();
				(*it)->m_hovered = false;
			}
		}
	}

	return false;
}

bool UIView::isHit(vec2 point)
{
	// transform point to be in this view local space, for a simple rect test then
	vec4 view_local = matrix.inverse() * vec4(point.x, point.y, 0.f, 1.f);

	if (m_name == "captainScreenButton")
	{
		Log("UIView::isHit() with mouse=%f %f became %f %f in local", point.x, point.y, view_local.x, view_local.y);
	}


	if (   (view_local.x >= 0.f) 
		&& (view_local.x <= size.x)
		&& (view_local.y >= 0.f)
		&& (view_local.y <= size.y) )
	{
		return true;
	}
	else
	{
		return false;
	}

}


bool UIView::processTouchMove(int x, int y)
{
	onMouseMove();

	for(std::vector<UIView*>::iterator it = m_children.begin(); it != m_children.end(); it++)
	{
		FloatRect controlRect = (*it)->getRect();
		FloatRect testRect(controlRect.left, controlRect.top, controlRect.width - 1, controlRect.height - 1);

		(*it)->processTouchMove(x,y);

		if(testRect.contains(x,y))
		{
			if(!(*it)->m_hovered)
			{
				(*it)->setPseudoClass("hover", true);
				(*it)->m_hovered = true;
			}
		}
		else
		{
			// mouse is not in it, is it just leaving now?
			if((*it)->m_hovered)
			{
				(*it)->setPseudoClass("hover", false);
				(*it)->onMouseLeave();
				(*it)->m_hovered = false;
			}
		}
	}

	return false;
}


/// Process a mouse press event
bool UIView::processMouseButtonPressed(int x, int y, Mouse::Button button)
{
	if(!m_visible)
	{
		return true;
	}

	m_childrenLock++;
	for(std::vector<UIView*>::iterator it = m_children.begin(); it != m_children.end(); it++)
	{
		//if ((*it)->getBounds().contains(x, y) && (*it)->m_visible)
		if ((*it)->m_visible && (*it)->isHit(vec2(x,y)))
		{
			(*it)->m_pointerPressCount++;
		}

		(*it)->processMouseButtonPressed(x,y, button);

	}
	m_childrenLock--;

	if(m_childrenLock == 0)
		applyPendingOperations();

	return true;
}

/// Process a mouse release event
void UIView::processMouseButtonReleased(int x, int y, Mouse::Button button, UIEventResult& info)
{
	if(!m_visible)
	{
		return;
	}

	m_childrenLock++;
	for(std::vector<UIView*>::iterator it = m_children.begin(); it != m_children.end(); it++)
	{
		//if((*it)->getBounds().contains(x,y) && (*it)->m_visible)
		if ((*it)->m_visible && (*it)->isHit(vec2(x, y)))
		{
			if((*it)->m_pointerPressCount > 0)
				(*it)->onClick();
			(*it)->m_pointerPressCount = 0;
		}		
		(*it)->processMouseButtonReleased(x,y, button, info);
	}
	m_childrenLock--;

	if(m_childrenLock == 0) 
		applyPendingOperations();
}

/// Enables or disables a pseudo class
void UIView::setPseudoClass(const String& name, bool active)
{
	//Log("Class enabled %s", name.c_str());
	m_classInfo[name] = active;
};

/// Deep clone of the control and its hierarchy
UIView* UIView::clone()
{
	return new UIView(*this);
}

void UIView::setRect(FloatRect rect)
{
	setPosition(rect.left, rect.top);
	setSize(rect.width, rect.height);
	m_transform = mat4::translate(rect.left, rect.top, 0.f);
}

void UIView::setRect(float left, float top, float width, float height)
{
	setRect(FloatRect(left, top, width, height));
}


FloatRect UIView::getRect()
{
	return FloatRect(position.x, position.y, size.x, size.y);
};

/// Get the position of the exact middle of this UIWindow
Vec2f UIView::getMiddlePosition()
{
	return Vec2f(position.x + size.x / 2.f, position.y + size.y / 2.f);
}

UIView* UIView::getParent()
{
	return m_parent;
}

void UIView::applyPendingOperations()
{
	if(m_childrenLock > 0) return ;

	for(std::size_t i = 0; i < m_pendingOperations.size(); ++i)
	{
		switch(m_pendingOperations[i].type)
		{
		case UIControlOperation::Attachment:
			{
				m_children.push_back(m_pendingOperations[i].control);
			} break;

		case UIControlOperation::Destruction:
			{
				m_children.erase(std::find(m_children.begin(), m_children.end(), m_pendingOperations[i].control));
				onChildRemoved(m_pendingOperations[i].control);
				delete m_pendingOperations[i].control;
			} break;
		
		case UIControlOperation::Detachment:
			{
				m_children.erase(std::find(m_children.begin(), m_children.end(), m_pendingOperations[i].control));
				onChildRemoved(m_pendingOperations[i].control);
			} break;

		}
	}

	m_pendingOperations.clear();
}


void UIView::attach(UIView* control)
{
	// Failure to attach
	if(!control)
		return;

	// Notify components of new added control
	for(std::vector<UIController*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		(*it)->onChildAttached(control);
	}

	onNewChild(control);

	if(m_childrenLock == 0)
	{
		m_children.push_back(control);
	}
	else
	{
		UIControlOperation action;
		action.control = control;
		action.type = UIControlOperation::Attachment;
		m_pendingOperations.push_back(action);
	}


	control->addReference();
	// Assign
	control->m_parent = this;

	if(_core)
		control->setContext(_core);

	onChildAdded(control);
}

/// Called on the subclass when a new child is added
void UIView::onChildAdded(UIView* widget)
{
}

/// Makes the control invisible
void UIView::hide()
{
	m_visible = false;
}

/// Makes the control visible
void UIView::show()
{
	m_visible = true;
}

/// Find a control by its name in the control tree
UIView* UIView::findByName(const String& name)
{
	// Is this the requested view?
	if(getName() == name)
		return this;

	// Let's make sure its not in pending attachments
	for(std::vector<UIControlOperation>::iterator it = m_pendingOperations.begin(); it != m_pendingOperations.end(); ++it)
	{
		if((*it).type ==  UIControlOperation::Attachment && (*it).control->getName() == name)
		{
			return (*it).control;
		}
		else if(it->type == UIControlOperation::Attachment)
		{
			// Propagate to this control children too
			UIView* v = it->control->findByName(name);
			if(v)
				return v;
		}
	}

	// Is any of the children the requested view?
	for(std::vector<UIView*>::const_iterator it = m_children.begin(); it != m_children.end(); it++)
	{
		UIView* cntrl = (*it)->findByName(name);
		if(cntrl)
		{
			return cntrl;
		}
	}

	return NULL;
}

/// Destroys the control and removes from the hierarchy
void UIView::destroy()
{
	UIView* parent = getParent();
	if(parent)
	{
		// I can remove myself from my parent's list
		parent->destroyChild(this);
	}
}

void UIView::destroyChild(UIView* child)
{
	UIControlOperation op;
	op.type =  UIControlOperation::Destruction;
	op.control = child;
	m_pendingOperations.push_back(op);	
	
	// -- if not busy, apply the changes now
	if (m_childrenLock == 0)
	{
		applyPendingOperations();
	}
}

/// Virtual
void UIView::onResize(){}

/// Resizes the control over a defined time
/// The lower border of the control will become at target position
void UIView::resizeToPoint(float x, float y, float duration){

};

void UIView::resize(float width, float height, float duration)
{

};

void UIView::onUpdate(float elapsedTime)
{	

}

void UIView::update(float elapsedTime)
{
	m_childrenLock++;
	for(std::vector<UIView*>::const_iterator it = m_children.begin(); it != m_children.end(); it++){
		(*it)->update(elapsedTime);
	}
	m_childrenLock--;

	if(m_childrenLock == 0)
	{
		applyPendingOperations();
	}

	m_animations.update(elapsedTime);

	onUpdate(elapsedTime);

	for(std::size_t i = 0; i < components.size(); ++i)
	{
		components[i]->onUpdate(Time::fromSeconds(elapsedTime), this);
	}
}

/// Get the current size of the control that encompasses all its children
FloatRect UIView::childrenRect()
{
	FloatRect boundingRect(0.f, 0.f, size.x, size.y);

	for(std::size_t i = 0; i < getChildCount(); i++)
	{
		UIView* c = getChild(i);

		// get bounds of the children
		if (c->position.y + c->size.y >= boundingRect.height)
		{
			boundingRect.height = c->position.y + c->size.y;
		}
	}
	return boundingRect;
};

void UIView::setSize(float width, float height)
{
	// -- This control is about to be resized, might need to do some automatic operations on children
//	processSizeChange(size.x, size.y, width, height);

	float pX = size.x;
	float pY = size.y;

	size.x = width;
	size.y = height;

	// Let components know a resize was made
	for(std::size_t i = 0; i < components.size(); ++i)
	{
		components[i]->onResize(this);
	}

	onResize();
	
	// Last thing
	sizeChanged();

	// After size changed, let's notify the hierarchy it happened for layouters etc
	UxEvent event;
	event.type = 1;
	event.emitter = this;
	if (getParent())
		getParent()->dispatch(event);
};


void UIView::drawItself(GraphicsDevice* renderer, const mat4& transform )
{
	// Invisible UIView, stop rendering itself or children
	if(!m_visible)
	{
		return;
	}

	if(m_clipContents)
	{
		renderer->pushClippingRect(FloatRect(position.x, position.y, size.x, size.y));
	}

	mat4 localTransform = mat4::translate(position) * mat4::rotatey(rotation_y) * mat4::rotatex(rotation_x) * mat4::rotatez(rotation_z) 
		* mat4::translate(-pivot.x,-pivot.y,0.f);

	mat4 absoluteTransform = transform * localTransform;

	this->matrix = absoluteTransform;

	// Tel
	draw(renderer, absoluteTransform);

	renderer->setModelMatrix(absoluteTransform);


	for(std::size_t i = 0; i < components.size(); ++i)
	{
		components[i]->onRender(renderer, this, absoluteTransform);
	}

	if(m_clipContents)
	{
		renderer->popClippingRect();
	}

	// -- Pre Render Step (Before Children)
	preRender(renderer);

	localTransform = mat4::translate(scrolling_offset.x, scrolling_offset.y, 0.f) * mat4::translate(position) * mat4::rotatey(rotation_y) * mat4::rotatex(rotation_x) * mat4::rotatez(rotation_z)
		* mat4::translate(-pivot.x, -pivot.y, 0.f);

	absoluteTransform = transform * localTransform;

	// We setup a painter and pass it on for actual safe rendering with no hacks or boilerplate
	UIPainter painter;
	painter.graphicsDevice = renderer;
	painter.baseMatrix = absoluteTransform;
	if (getCore())
		painter.activeFont = getCore()->m_defaultFont;
	onPaint(painter);

	// clip the overflowing children
	if(m_clipChildren)
	{	
		renderer->setClippingEnabled(true);
		renderer->setClippingRect(FloatRect(getWorldPosition().x, getWorldPosition().y, size.x, size.y));

		//renderer->pushClippingRect(FloatRect(getWorldPosition().x,getWorldPosition().y, size.x, size.y));
	}



	// Let children render as well
	for(std::vector<UIView*>::const_iterator it = m_children.begin(); it != m_children.end(); it++)
	{
		(*it)->drawItself(renderer, absoluteTransform);
	}

	if(m_clipChildren)
		renderer->popClippingRect();

	// -- Post Render Step (After Children)
	postRender(renderer);
}

/// Get the current world position
vec3 UIView::getWorldPosition()
{
	return matrix * vec3(0.f, 0.f, 0.f);
}

void UIView::enableAutoResize(bool enable)
{

}

/// Returns the first component with the given type
UIController* UIView::getComponentByType(UIController::Type type)
{
	for(std::size_t i = 0; i < components.size(); ++i)
	{
		if(components[i]->component_id == type)
		{
			return components[i];
		}
	}
	return NULL;
}

/// Callback when the position of the control changed, for updating nested objects
void UIView::onPositionChanged()
{
}

vec2 UIView::getCenter()
{
	return vec2(getPosition() + getSize() / 2.f);
}

/// Define a new name for this control
void UIView::setName(const String& name){
	m_name = name;
};

/// Get the name of the control
const char* UIView::getName()
{
	return m_name.c_str();
}

NEPHILIM_NS_END
