#include <Nephilim/UI/Widget.h>
#include <Nephilim/UI/UxEvent.h>

#include <Nephilim/Graphics/VertexArray.h>
#include <Nephilim/Graphics/GL/GLHelpers.h>

#include <Nephilim/UI/UIController.h>
#include <Nephilim/Foundation/StringList.h>
#include <Nephilim/Foundation/Logging.h>

#include <Nephilim/UI/UILoaderXML.h>

#include <algorithm>

NEPHILIM_NS_BEGIN

Widget::Widget()
: UxNode()
, position(0.f, 0.f, 0.f)
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
Widget::Widget(Widget* parent)
: UxNode(parent)
, m_childrenLock(0)
, m_hasFocus(false)
, m_clipChildren(false)
, m_clipContents(false)
, m_visible(true)
, m_hovered(false)
, m_pointerPressCount(0)
{
	
}

Widget::~Widget()
{
	// Release all components to prevent leaks
	for (std::size_t i = 0; i < mControllers.size(); ++i)
	{
		mControllers[i]->onRelease(this);
		delete mControllers[i];
	}

	// I am being destroyed, destroy children
	for (std::size_t i = 0; i < mChildren.size(); ++i)
	{
		delete mChildren[i];
	}
}

/// Called on subclasses to draw custom stuff
void Widget::onPaint(UIPainter& painter){}

/// Called when the view receives a mouse/touch related event
void Widget::onPointerEvent(const UIPointerEvent& event){}

/// Called to handle a key press event
void Widget::keyPressEvent(UxKeyEvent* key){}

/// Creates a new UIView, names it and attaches it as a child, then returns it
Widget* Widget::createChild(const String& name)
{
	// Instance a new view
	Widget* view = new Widget();
	view->setName(name);

	// Attach
	attach(view);

	view->onSetup();

	return view;
}

/// Set a new size to the widget
void Widget::setSize(Vector2D _size)
{
	setSize(_size.x, _size.y);
}

/// Get the current width of this widget
float Widget::width()
{
	return size.x;
}

/// Get the current height of this widget
float Widget::height()
{
	return size.y;
}

/// Refresh the visual styles on this view
void Widget::updateStyles()
{
	for (auto it = mControllers.begin(); it != mControllers.end(); ++it)
	{
		(*it)->updateStyles();
	}
}

/// Set styles directly to the view
void Widget::setStyleSheet(const String& stylesheet)
{

}

/// Load the hierarchy of this view from a file and configure itself
void Widget::load(const String& filename)
{
	Log("=> LOADING XML FILE INTO THE UI");
	UILoaderXML uiLoader;
	uiLoader.loadFromFile(filename, this);
}

void Widget::setProperty(const String& str)
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

		for(std::size_t i = 0; i < mControllers.size(); ++i)
		{
			mControllers[i]->onPropertySet(target_object, paramValue);
		}
}	
}

/// Add a component to the view
void Widget::addController(UIController* component)
{
	if(!component)
		return;

	mControllers.push_back(component);
	component->mParent = this;
	component->onAttach(this);
}

/// Set any flags for the view
void Widget::setFlag(Uint32 flags)
{
	mFlags |= flags;
}

bool Widget::hasFlags(Uint32 flags)
{
	return (mFlags & flags) == flags;
}


void Widget::addStringProperty(const String& propertyName, const String& propertyValue)
{
	mStringProperties[propertyName] = propertyValue;
}

String Widget::getStringProperty(const String& propertyName)
{
	return mStringProperties[propertyName];
}

/// Called before rendering the children UIView ( Virtual )
void Widget::preRender(GraphicsDevice* renderer){}

/// Called after rendering the children UIView ( Virtual )
void Widget::postRender(GraphicsDevice* renderer){}

void Widget::setPosition(float x, float y)
{
	// Offset children
	vec2 offset = vec2(x,y) - getPosition();

	onPositionChanged();

	// update the correct vars
	position.x = x;
	position.y = y;
}

void Widget::setPosition(vec2 position)
{
	setPosition(position.x, position.y);
}

vec2 Widget::getPosition()
{
	return vec2(position.x, position.y);
}

void Widget::setLocalPosition(float x, float y)
{
	Widget* parent = getParent();
	if(parent)
	{
		setPosition(parent->getPosition() + vec2(x,y));
	}
}

void Widget::setLocalPosition(vec2 localPosition)
{
	setLocalPosition(localPosition.x, localPosition.y);
}

vec2 Widget::getLocalPosition()
{
	Widget* parent = getParent();
	
	if(!parent)
		return vec2(0.f, 0.f);

	return getPosition() - parent->getPosition();
}

void Widget::detach(Widget* control)
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
		mChildren.erase(std::find(mChildren.begin(), mChildren.end(), control));
	}
}

/// Feeds the position of the control to the animation systems
vec2 Widget::axGetPosition2D()
{
	return getPosition();
}

void Widget::axSetPosition2D(vec2 position)
{
	setPosition(position.x, position.y);
}

void Widget::axSetAlpha(float alpha)
{
	
}

float Widget::axGetAlpha()
{
	return 1.f;
}

void Widget::axKillTrigger()
{
	destroy();
}

void Widget::offsetChildrenPosition(vec2 offset)
{
	for(std::size_t i = 0; i < mChildren.size(); ++i)
	{
		static_cast<Widget*>(mChildren[i])->setPosition(static_cast<Widget*>(mChildren[i])->getPosition() + offset);
	}
}

/// Set the new Z value
void Widget::setZ(float _z)
{
	position.z = _z;
	//Log("Z set to %f", _z);
}

/// This function allows to start an animation out of its definition file
void Widget::startAnimation(const String& animationAsset)
{
	UIAnimationLoaderXML loader;
	Animation* anim = loader.load(animationAsset, this);
	if (anim)
	{
		commitAnimation(anim);
	}
}

void Widget::commitAnimation(Animation* animation)
{
	animation->addTarget(this);
	animation->deduceInitialParameters();
	m_animations.commit(animation);
}

bool Widget::hasAnimatedChildren()
{
	for(std::size_t i = 0; i < mChildren.size(); ++i)
	{
		if (static_cast<Widget*>(mChildren[i])->hasAnimations())
		{
			return true;
		}
		else if(static_cast<Widget*>(mChildren[i])->hasAnimatedChildren())
			return true;
	}

	return false;
}

/// Check if this control has any animation going on
bool Widget::hasAnimations()
{
	return m_animations.m_animations.size() > 0;
}


void Widget::onChildRemoved(Widget* control)
{

}

void Widget::printHierarchy(int tabs)
{
	String tabss;
	for(int i = 0; i < tabs; ++i)
		tabss += "\t";

	Log("%s: %s", tabss.c_str(), getName());

	for(std::size_t i = 0; i < mChildren.size(); ++i)
	{
		if(!isScheduledForRemoval(static_cast<Widget*>(mChildren[i])))
			static_cast<Widget*>(mChildren[i])->printHierarchy(tabs + 1);
	}

	for(std::vector<UIControlOperation>::iterator it = m_pendingOperations.begin(); it != m_pendingOperations.end(); ++it)
	{
		if(it->type == UIControlOperation::Attachment)
			it->control->printHierarchy(tabs + 1);
	}
}

bool Widget::isScheduledForRemoval(Widget* v)
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
String Widget::getToolTipLabel(){
	return "";
};

/// Get the number of children of this control
int Widget::getChildCount()
{
	return static_cast<int>(mChildren.size());
};

/// Get a child at a index
Widget* Widget::getChild(int index)
{
	return static_cast<Widget*>(mChildren[index]);
};

/// Get the current size of the control
vec2 Widget::getSize()
{
	return size;
}

/// Callback to render itself, renders children
void Widget::draw(GraphicsDevice* renderer, mat4 transform)
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

void Widget::dispatchEvent(const Event& event)
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
	for (ChildrenIterator it = mChildren.begin(); it != mChildren.end(); ++it)
	{
		static_cast<Widget*>(*it)->dispatchEvent(modEvent);
	}
	m_childrenLock--;

	if(m_childrenLock == 0)
		applyPendingOperations();


	// -- deliver events to the controllers
	for(std::size_t i = 0; i < mControllers.size(); ++i)
	{
		mControllers[i]->onEvent(event, this);
	}
}

bool Widget::onEventNotification(Event& event)
{
	
	return false;
};

/// Is the control able to get input focus or not?
bool Widget::isFocusable()
{
	return false;
};

/// Attempts focus on this control
bool Widget::focus()
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
bool Widget::hasFocus()
{
	return m_hasFocus;
};

/// Hierarchicly sets the context to all children
void Widget::setContext(UICore* states)
{
	_core = states;

	for(ChildrenIterator it = mChildren.begin(); it != mChildren.end(); ++it)
	{
		static_cast<Widget*>(*it)->setContext(states);
	}
}

/// Remove focus from the element
void Widget::blur()
{
	m_hasFocus = false;
};

bool Widget::onKeyPressed(Keyboard::Key key)
{

	return false;
}

bool Widget::onTextEvent(Uint32 code)
{
	return false;
};

/// Move the widget around, relative to where it currently is
void Widget::move(float x, float y)
{
	setPosition(getPosition() + vec2(x, y));
}

/// Process a mouve movement event
/// Returns false if the mouse isnt on any control
bool Widget::processMouseMove(int x, int y)
{
	if(!m_visible)
	{
		return true;
	}

	onMouseMove();

	for(ChildrenIterator it = mChildren.begin(); it != mChildren.end(); it++)
	{
		FloatRect controlRect = static_cast<Widget*>(*it)->getRect();
		FloatRect testRect(controlRect.left, controlRect.top, controlRect.width - 1, controlRect.height - 1);

		static_cast<Widget*>(*it)->processMouseMove(x, y);

		//if (testRect.contains(x, y))
		if (static_cast<Widget*>(*it)->isHit(vec2(x, y)))
		{
			if (!static_cast<Widget*>(*it)->m_hovered)
			{
				static_cast<Widget*>(*it)->setPseudoClass("hover", true);
				static_cast<Widget*>(*it)->m_hovered = true;
				static_cast<Widget*>(*it)->onMouseEnter();
			}
		}

		else
		{
			// mouse is not in it, is it just leaving now?
			if (static_cast<Widget*>(*it)->m_hovered)
			{
				static_cast<Widget*>(*it)->setPseudoClass("hover", false);
				static_cast<Widget*>(*it)->onMouseLeave();
				static_cast<Widget*>(*it)->m_hovered = false;
			}
		}
	}

	return false;
}

bool Widget::isHit(vec2 point)
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


bool Widget::processTouchMove(int x, int y)
{
	onMouseMove();

	for(ChildrenIterator it = mChildren.begin(); it != mChildren.end(); it++)
	{
		FloatRect controlRect = static_cast<Widget*>(*it)->getRect();
		FloatRect testRect(controlRect.left, controlRect.top, controlRect.width - 1, controlRect.height - 1);

		static_cast<Widget*>(*it)->processTouchMove(x, y);

		if(testRect.contains(x,y))
		{
			if (!static_cast<Widget*>(*it)->m_hovered)
			{
				static_cast<Widget*>(*it)->setPseudoClass("hover", true);
				static_cast<Widget*>(*it)->m_hovered = true;
			}
		}
		else
		{
			// mouse is not in it, is it just leaving now?
			if (static_cast<Widget*>(*it)->m_hovered)
			{
				static_cast<Widget*>(*it)->setPseudoClass("hover", false);
				static_cast<Widget*>(*it)->onMouseLeave();
				static_cast<Widget*>(*it)->m_hovered = false;
			}
		}
	}

	return false;
}


/// Process a mouse press event
bool Widget::processMouseButtonPressed(int x, int y, Mouse::Button button)
{
	if(!m_visible)
	{
		return true;
	}

	m_childrenLock++;
	for(ChildrenIterator it = mChildren.begin(); it != mChildren.end(); it++)
	{
		//if ((*it)->getBounds().contains(x, y) && (*it)->m_visible)
		if (static_cast<Widget*>(*it)->m_visible && static_cast<Widget*>(*it)->isHit(vec2(x, y)))
		{
			static_cast<Widget*>(*it)->m_pointerPressCount++;
		}

		static_cast<Widget*>(*it)->processMouseButtonPressed(x, y, button);

	}
	m_childrenLock--;

	if(m_childrenLock == 0)
		applyPendingOperations();

	return true;
}

/// Process a mouse release event
void Widget::processMouseButtonReleased(int x, int y, Mouse::Button button, UIEventResult& info)
{
	if(!m_visible)
	{
		return;
	}

	m_childrenLock++;
	for(ChildrenIterator it = mChildren.begin(); it != mChildren.end(); it++)
	{
		//if((*it)->getBounds().contains(x,y) && (*it)->m_visible)
		if (static_cast<Widget*>(*it)->m_visible && static_cast<Widget*>(*it)->isHit(vec2(x, y)))
		{
			if (static_cast<Widget*>(*it)->m_pointerPressCount > 0)
				static_cast<Widget*>(*it)->onClick();
			static_cast<Widget*>(*it)->m_pointerPressCount = 0;
		}		
		static_cast<Widget*>(*it)->processMouseButtonReleased(x, y, button, info);
	}
	m_childrenLock--;

	if(m_childrenLock == 0) 
		applyPendingOperations();
}

/// Enables or disables a pseudo class
void Widget::setPseudoClass(const String& name, bool active)
{
	//Log("Class enabled %s", name.c_str());
	m_classInfo[name] = active;
};

/// Deep clone of the control and its hierarchy
Widget* Widget::clone()
{
	return new Widget(*this);
}

void Widget::setRect(FloatRect rect)
{
	setPosition(rect.left, rect.top);
	setSize(rect.width, rect.height);
}

void Widget::setRect(float left, float top, float width, float height)
{
	setRect(FloatRect(left, top, width, height));
}


FloatRect Widget::getRect()
{
	return FloatRect(position.x, position.y, size.x, size.y);
}

/// Get the global coordinates for this widget
FloatRect Widget::getGlobalRect()
{
	Vector3D WorldPos = getWorldPosition();
	return FloatRect(WorldPos.x, WorldPos.y, size.x, size.y);
}

/// Get the position of the exact middle of this UIWindow
Vec2f Widget::getMiddlePosition()
{
	return Vec2f(position.x + size.x / 2.f, position.y + size.y / 2.f);
}

Widget* Widget::getParent()
{
	return static_cast<Widget*>(mParent);
}

void Widget::applyPendingOperations()
{
	if(m_childrenLock > 0) return ;

	for(std::size_t i = 0; i < m_pendingOperations.size(); ++i)
	{
		switch(m_pendingOperations[i].type)
		{
		case UIControlOperation::Attachment:
			{
				mChildren.push_back(m_pendingOperations[i].control);
			} break;

		case UIControlOperation::Destruction:
			{
				mChildren.erase(std::find(mChildren.begin(), mChildren.end(), m_pendingOperations[i].control));
				onChildRemoved(m_pendingOperations[i].control);
				delete m_pendingOperations[i].control;
			} break;
		
		case UIControlOperation::Detachment:
			{
				mChildren.erase(std::find(mChildren.begin(), mChildren.end(), m_pendingOperations[i].control));
				onChildRemoved(m_pendingOperations[i].control);
			} break;

		}
	}

	m_pendingOperations.clear();
}


void Widget::attach(Widget* control)
{
	// Failure to attach
	if(!control)
		return;

	// Notify components of new added control
	for(std::vector<UIController*>::iterator it = mControllers.begin(); it != mControllers.end(); ++it)
	{
		(*it)->onChildAttached(control);
	}

	onNewChild(control);

	if(m_childrenLock == 0)
	{
		mChildren.push_back(control);
	}
	else
	{
		UIControlOperation action;
		action.control = control;
		action.type = UIControlOperation::Attachment;
		m_pendingOperations.push_back(action);
	}

	// Assign
	control->mParent = this;

	if(_core)
		control->setContext(_core);

	onChildAdded(control);
}

/// Called on the subclass when a new child is added
void Widget::onChildAdded(Widget* widget)
{
}

/// Makes the control invisible
void Widget::hide()
{
	m_visible = false;
}

/// Makes the control visible
void Widget::show()
{
	m_visible = true;
}

/// Find a control by its name in the control tree
Widget* Widget::findByName(const String& name)
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
			Widget* v = it->control->findByName(name);
			if(v)
				return v;
		}
	}

	// Is any of the children the requested view?
	for(ChildrenIterator it = mChildren.begin(); it != mChildren.end(); it++)
	{
		Widget* cntrl = static_cast<Widget*>(*it)->findByName(name);
		if(cntrl)
		{
			return cntrl;
		}
	}

	return NULL;
}

/// Destroys the control and removes from the hierarchy
void Widget::destroy()
{
	Widget* parent = getParent();
	if(parent)
	{
		// I can remove myself from my parent's list
		parent->destroyChild(this);
	}
}

void Widget::destroyChild(Widget* child)
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
void Widget::onResize(){}

/// Resizes the control over a defined time
/// The lower border of the control will become at target position
void Widget::resizeToPoint(float x, float y, float duration){

};

void Widget::resize(float width, float height, float duration)
{

};

void Widget::onUpdate(float elapsedTime)
{	

}

void Widget::update(float elapsedTime)
{
	m_childrenLock++;
	for (ChildrenIterator it = mChildren.begin(); it != mChildren.end(); it++)
	{
		static_cast<Widget*>(*it)->update(elapsedTime);
	}
	m_childrenLock--;

	if(m_childrenLock == 0)
	{
		applyPendingOperations();
	}

	m_animations.update(elapsedTime);

	onUpdate(elapsedTime);

	for(std::size_t i = 0; i < mControllers.size(); ++i)
	{
		mControllers[i]->onUpdate(Time::fromSeconds(elapsedTime), this);
	}
}

/// Get the current size of the control that encompasses all its children
FloatRect Widget::childrenRect()
{
	FloatRect boundingRect(0.f, 0.f, size.x, size.y);

	for(std::size_t i = 0; i < getChildCount(); i++)
	{
		Widget* c = getChild(i);

		// get bounds of the children
		if (c->position.y + c->size.y >= boundingRect.height)
		{
			boundingRect.height = c->position.y + c->size.y;
		}
	}
	return boundingRect;
};

void Widget::setSize(float width, float height)
{
	// -- This control is about to be resized, might need to do some automatic operations on children
//	processSizeChange(size.x, size.y, width, height);

	float pX = size.x;
	float pY = size.y;

	size.x = width;
	size.y = height;

	// Let components know a resize was made
	for(std::size_t i = 0; i < mControllers.size(); ++i)
	{
		mControllers[i]->onResize(this);
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


void Widget::drawItself(GraphicsDevice* renderer, const mat4& transform )
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
		* mat4::translate(-anchor.x,-anchor.y,0.f);

	mat4 absoluteTransform = transform * localTransform;

	this->matrix = absoluteTransform;

	// Tel
	draw(renderer, absoluteTransform);

	renderer->setModelMatrix(absoluteTransform);


	for(std::size_t i = 0; i < mControllers.size(); ++i)
	{
		mControllers[i]->onRender(renderer, this, absoluteTransform);
	}

	if(m_clipContents)
	{
		renderer->popClippingRect();
	}

	// -- Pre Render Step (Before Children)
	preRender(renderer);

	localTransform = mat4::translate(scrolling_offset.x, scrolling_offset.y, 0.f) * mat4::translate(position) * mat4::rotatey(rotation_y) * mat4::rotatex(rotation_x) * mat4::rotatez(rotation_z)
		* mat4::translate(-anchor.x, -anchor.y, 0.f);

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
	for(ChildrenIterator it = mChildren.begin(); it != mChildren.end(); it++)
	{
		static_cast<Widget*>(*it)->drawItself(renderer, absoluteTransform);
	}

	if(m_clipChildren)
		renderer->popClippingRect();

	// -- Post Render Step (After Children)
	postRender(renderer);
}

/// Get the current world position
vec3 Widget::getWorldPosition()
{
	return matrix * vec3(0.f, 0.f, 0.f);
}

void Widget::enableAutoResize(bool enable)
{

}

/// Returns the first component with the given type
UIController* Widget::getComponentByType(UIController::Type type)
{
	for(std::size_t i = 0; i < mControllers.size(); ++i)
	{
		if(mControllers[i]->component_id == type)
		{
			return mControllers[i];
		}
	}
	return NULL;
}

/// Callback when the position of the control changed, for updating nested objects
void Widget::onPositionChanged()
{
}

vec2 Widget::getCenter()
{
	return vec2(getPosition() + getSize() / 2.f);
}

/// Define a new name for this control
void Widget::setName(const String& name){
	m_name = name;
};

/// Get the name of the control
const char* Widget::getName()
{
	return m_name.c_str();
}

NEPHILIM_NS_END
