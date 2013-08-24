#include <Nephilim/UIControl.h>
#include <Nephilim/Logger.h>

#include <algorithm>

NEPHILIM_NS_BEGIN

UIControl* UIControl::object = NULL;

UIControl::UIControl()
: RefCountable()
, m_parent(NULL)
, m_positionFlags(0)
, m_sizeFlags(0)
, m_childrenLock(0)
, m_stateContext(NULL)
, m_hasFocus(false)
, m_layoutController(NULL)
, m_backgroundColor(91,91,91)
, m_topBorderColor(69,69,69)
, m_leftBorderColor(m_topBorderColor)
, m_rightBorderColor(m_topBorderColor)
, m_bottomBorderColor(m_topBorderColor)
, m_clipChildren(false)
, m_clipContents(false)
, m_visible(true)
, m_drawBorder(true)
, m_stretchForContents(false)
, m_hovered(false)
, drawColoredBackground(true)
, m_bounds(0.f, 0.f, 1.f, 1.f)
, m_pointerPressCount(0)
{
}

UIControl::~UIControl()
{
	// I am being destroyed, destroy children
	for(size_t i = 0; i < m_children.size(); ++i)
	{
		delete m_children[i];
	}
}

void UIControl::setPosition(float x, float y)
{
	// Offset children
	vec2 offset = vec2(x,y) - getPosition();

	m_bounds.left = x;
	m_bounds.top = y;

	if(this == object)
	{
		Log("Setting position !!");
	}

	updateLayout();

	offsetChildrenPosition(offset);

	onPositionChanged();
}

void UIControl::setPosition(vec2 position)
{
	setPosition(position.x, position.y);
}

vec2 UIControl::getPosition()
{
	return vec2(m_bounds.left, m_bounds.top);
}

void UIControl::setLocalPosition(float x, float y)
{
	UIControl* parent = getParent();
	if(parent)
	{
		setPosition(parent->getPosition() + vec2(x,y));
	}
}

void UIControl::setLocalPosition(vec2 localPosition)
{
	setLocalPosition(localPosition.x, localPosition.y);
}

vec2 UIControl::getLocalPosition()
{
	UIControl* parent = getParent();
	
	if(!parent)
		return vec2(0.f, 0.f);

	return getPosition() - parent->getPosition();
}

void UIControl::detach(UIControl* control)
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

/// Feeds the position of the control to the animation systems
vec2 UIControl::axGetPosition2D()
{
	return getPosition();
}

void UIControl::axSetPosition2D(vec2 position)
{
	setPosition(position.x, position.y);
}

void UIControl::axSetAlpha(float alpha)
{
	m_backgroundColor.a = static_cast<Uint8>(alpha * 255);
}

float UIControl::axGetAlpha()
{
	return static_cast<float>(m_backgroundColor.a / 255);
}

void UIControl::axKillTrigger()
{
	destroy();
}

void UIControl::offsetChildrenPosition(vec2 offset)
{
	for(size_t i = 0; i < m_children.size(); ++i)
	{
		m_children[i]->setPosition(m_children[i]->getPosition() + offset);
	}
}

/// Set the flags for sizing
void UIControl::setSizeFlags(Uint64 flags)
{
	m_sizeFlags = flags;

	processSizeFlags();
}

void UIControl::commitAnimation(AxBase* animation)
{
	animation->addTarget(this);
	animation->deduceInitialParameters();
	m_animations.commit(animation);
}

/// Get the sizing flags
Uint64 UIControl::getSizeFlags()
{
	return m_sizeFlags;
}

/// Check if there is a particular sizing flag
bool UIControl::hasSizeFlag(Uint64 flag)
{
	return ( (m_sizeFlags & flag) == flag);
}

/// Get the current positioning flags
Uint64 UIControl::getPositionFlags()
{
	return m_positionFlags;
}

/// Check the existence of a particular flag for positioning
bool UIControl::hasPositionFlag(Uint64 flag)
{
	return ( (m_positionFlags & flag) == flag);
}


/// Set positioning flags to the control
void UIControl::setPositionFlags(Uint64 flags)
{
	m_positionFlags = flags;

	//(~(Uint64)0))

	processPositionFlags();
}

void UIControl::onChildRemoved(UIControl* control)
{

}

/// Attempt to process positional flags
void UIControl::processPositionFlags()
{
	// Lets set the position flags now
	if(getParent() && getContext())
	{
		if( hasPositionFlag(UIPositionFlag::AttachBottom))
		{
			setPosition(m_bounds.left, getParent()->getSize().y - getSize().y);
		}
	}
}

/// Attempt to process size flags
void UIControl::processSizeFlags()
{
	// Lets set the position flags now
	if(getParent() && getContext())
	{
		
	}
}

/// Requests a tool tip text label from the control
/// If only a empty string is returned, no tooltip is shown
String UIControl::getToolTipLabel(){
	return "";
};

/// Get the number of children of this control
int UIControl::getChildCount()
{
	return static_cast<int>(m_children.size());
};

/// Get a child at a index
UIControl* UIControl::getChild(int index)
{
	return m_children[index];
};

/// Get the current size of the control
Vec2f UIControl::getSize()
{
	return Vec2f(m_bounds.width, m_bounds.height);
}

/// Set a new layout to the control
void UIControl::setLayout(UILayout* layout){
	m_layoutController = layout;

	// Perform the layouting
	m_layoutController->doLayout(this);
};

/// Get the currently assigned layout controller
/// \return NULL if there is no layout controller assigned
UILayout* UIControl::getLayout(){
	return m_layoutController;
};


/// Callback to render itself, renders children
void UIControl::draw(Renderer* renderer){

};

void UIControl::dispatchEvent(const Event& event)
{
	// -- No handling of the event in this control or its children
	if(!m_visible)
	{
		return;
	}

	/// Create a modifiable event, pass it to the control for possible alteration
	Event modEvent = event;
	onEventNotification(modEvent);

	m_childrenLock++;
	for(std::vector<UIControl*>::iterator it = m_children.begin(); it != m_children.end(); ++it)
	{
		(*it)->dispatchEvent(modEvent);
	}
	m_childrenLock--;

	if(m_childrenLock == 0)
		applyPendingOperations();
}

bool UIControl::onEventNotification(Event& event)
{
	
	return false;
};

/// Get bounds of the control
FloatRect UIControl::getBounds(){
	return m_bounds;
};

/// Is the control able to get input focus or not?
bool UIControl::isFocusable()
{
	return false;
};

/// Attempts focus on this control
bool UIControl::focus()
{
	// Fails to get focus if it is not focusable
	if(!isFocusable()) return false;

	if(getContext())
	{
		getContext()->m_focusControl = this;
		m_hasFocus = true;
	}
	else
	{
		//cout<<"Cant focus an element without a hierarchy"<<endl;
	}

	return true;
};

/// Check if the control currently has focus
bool UIControl::hasFocus()
{
	return m_hasFocus;
};

/// Hierarchicly sets the context to all children
void UIControl::setContext(UICore* states)
{
	m_stateContext = states;

	for(std::vector<UIControl*>::iterator it = m_children.begin(); it != m_children.end(); ++it)
	{
		(*it)->setContext(states);
	}

	switchLanguage();
}

/// Remove focus from the element
void UIControl::blur()
{
	m_hasFocus = false;
};

bool UIControl::onKeyPressed(Keyboard::Key key)
{

	return false;
}

bool UIControl::onTextEvent(Uint32 code)
{
	return false;
};

/// Reload all graphics because they were destroyed and are unavailable now
void UIControl::reloadGraphicalAssets()
{
//	TESTLOG("GL REQUIRES")

	for(std::vector<UIControl*>::iterator it = m_children.begin(); it != m_children.end(); it++){
		// lets see!
		(*it)->reloadGraphicalAssets();
	}
}

void UIControl::switchLanguage()
{
	innerLanguageSwitch();

	for(std::vector<UIControl*>::iterator it = m_children.begin(); it != m_children.end(); it++){
		// lets see!
		(*it)->switchLanguage();
	}
}

/// Called to re adjust children positions and sizes if needed
void UIControl::processSizeChange(float previousWidth, float previousHeight)
{
	// Parent control had its size updated

	if(hasSizeFlag(UISizeFlag::KeepRelativeSizeX))
	{
		float p = m_bounds.width / previousWidth;
		setSize(m_parent->getSize().x * p, getSize().y);
	}

	if(hasPositionFlag(UIPositionFlag::KeepRelativePositionX))
	{
		float p = m_bounds.left / previousWidth;
		setPosition(m_parent->getSize().x * p, m_bounds.top);
	}



	processPositionFlags();


	// size changed, update.
	if(m_sizePolicy.widthPolicy == UISizePolicy::ParentProportional && m_parent)
	{
		setSize(m_parent->getSize().x * m_sizePolicy.width, m_parent->getSize().y * m_sizePolicy.height);
//		PRINTLOG("f", "surface size: %f   width: %f\n", m_parent->getSize().x, m_sizePolicy.width);
	}
	// size changed, update.
	if(m_positionPolicy.widthPolicy == UISizePolicy::ParentProportional && m_parent)
	{
		setPosition(m_parent->getSize().x * m_positionPolicy.width, m_parent->getSize().y * m_positionPolicy.height);
//		PRINTLOG("f", "surface size: %f   width: %f\n", m_parent->getSize().x, m_positionPolicy.width);
	}

	for(std::vector<UIControl*>::iterator it = m_children.begin(); it != m_children.end(); it++){

		// lets see!
		(*it)->processSizeChange(previousWidth, previousHeight);
	}
}

/// Set the placement proportion of the control
void UIControl::setPlacement(float xFactor, float yFactor)
{
	// assign proportion mode
	m_positionPolicy.widthPolicy = UISizePolicy::ParentProportional;
	m_positionPolicy.width = xFactor;
	m_positionPolicy.height = yFactor;
};

/// Set the proportion of the control , relative to its parent
void UIControl::setProportion(float widthFactor, float heightFactor)
{
	if(m_parent)
	{
		setSize(m_parent->getSize().x * widthFactor, m_parent->getSize().y * heightFactor);
	}

	// assign proportion mode
	m_sizePolicy.widthPolicy = UISizePolicy::ParentProportional;
	m_sizePolicy.width = widthFactor;
	m_sizePolicy.height = heightFactor;
};


/// Process a mouve movement event
/// Returns false if the mouse isnt on any control
bool UIControl::processMouseMove(int x, int y)
{
	onMouseMove();

	for(std::vector<UIControl*>::iterator it = m_children.begin(); it != m_children.end(); it++)
	{
		FloatRect controlRect = (*it)->getBounds();
		FloatRect testRect(controlRect.left, controlRect.top, controlRect.width - 1, controlRect.height - 1);

		(*it)->processMouseMove(x,y);

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

bool UIControl::processTouchMove(int x, int y)
{
	onMouseMove();

	for(std::vector<UIControl*>::iterator it = m_children.begin(); it != m_children.end(); it++)
	{
		FloatRect controlRect = (*it)->getBounds();
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
bool UIControl::processMouseButtonPressed(int x, int y, Mouse::Button button)
{
	m_childrenLock++;
	for(std::vector<UIControl*>::iterator it = m_children.begin(); it != m_children.end(); it++)
	{
		if((*it)->getBounds().contains(x,y))
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
void UIControl::processMouseButtonReleased(int x, int y, Mouse::Button button, UIEventResult& info)
{
	m_childrenLock++;
	for(std::vector<UIControl*>::iterator it = m_children.begin(); it != m_children.end(); it++){
		if((*it)->getBounds().contains(x,y))
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
void UIControl::setPseudoClass(const String& name, bool active)
{
	//Log("Class enabled %s", name.c_str());
	m_classInfo[name] = active;
};

/// Deep clone of the control and its hierarchy
UIControl* UIControl::clone()
{
	return new UIControl(*this);
}

void UIControl::setRect(FloatRect rect)
{
	setPosition(rect.left, rect.top);
	setSize(rect.width, rect.height);
	m_transform = mat4::translate(rect.left, rect.top, 0.f);
}

void UIControl::setRect(float left, float top, float width, float height)
{
	setRect(FloatRect(left, top, width, height));
}


FloatRect UIControl::getRect()
{
	return m_bounds;
};

/// Get the position of the exact middle of this UIWindow
Vec2f UIControl::getMiddlePosition(){
	return Vec2f(m_bounds.left + m_bounds.width/2, m_bounds.top + m_bounds.height/2);
};


/// Returns the UIWindow context or NULL if not attached
UICore* UIControl::getContext()
{
	return m_stateContext;
};

UIControl* UIControl::getParent()
{
	return m_parent;
}

void UIControl::applyPendingOperations()
{
	if(m_childrenLock > 0) return ;

	for(size_t i = 0; i < m_pendingOperations.size(); ++i)
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


void UIControl::attach(UIControl* control)
{
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

	if(m_stateContext)
		control->setContext(m_stateContext);

	//control->processSizeChange(getSize().x, getSize().y);

//	updateLayout();
}

/// Makes the control invisible
void UIControl::hide()
{
	m_visible = false;
}

/// Makes the control visible
void UIControl::show()
{
	m_visible = true;
}

/// Find a control by its name in the control tree
UIControl* UIControl::findByName(const String& name)
{
	if(getName() == name)
		return this;

	for(std::vector<UIControl*>::const_iterator it = m_children.begin(); it != m_children.end(); it++)
	{
		UIControl* cntrl = (*it)->findByName(name);
		if(cntrl)
		{
			return cntrl;
		}
	}

	return NULL;
}

/// Destroys the control and removes from the hierarchy
void UIControl::destroy()
{
	UIControl* parent = getParent();
	if(parent)
	{
		// I can remove myself from my parent's list
		parent->destroyChild(this);
	}
}

void UIControl::destroyChild(UIControl* child)
{
	if(m_childrenLock > 0)
	{
		UIControlOperation op;
		op.type =  UIControlOperation::Destruction;
		op.control = child;
		m_pendingOperations.push_back(op);
	}
}

/// Callback when the control is resized
void UIControl::onResize(){

}

/// Resizes the control over a defined time
/// The lower border of the control will become at target position
void UIControl::resizeToPoint(float x, float y, float duration){

};

void UIControl::resize(float width, float height, float duration)
{

};

/// Update layout of children
void UIControl::updateLayout()
{
	if(m_layoutController)
	{
		m_layoutController->doLayout(this);
	}
}

void UIControl::onUpdate(float elapsedTime)
{	
}

void UIControl::update(float elapsedTime)
{
	m_childrenLock++;
	for(std::vector<UIControl*>::const_iterator it = m_children.begin(); it != m_children.end(); it++){
		(*it)->update(elapsedTime);
	}
	m_childrenLock--;

	if(m_childrenLock == 0)
	{
		applyPendingOperations();
	}

	m_animations.update(elapsedTime);

	onUpdate(elapsedTime);

}

/// Get the current size of the control that encompasses all its children
FloatRect UIControl::getContentBounds()
{
	FloatRect bounds = getBounds();

	for(int i = 0; i < getChildCount(); i++)
	{
		// get bounds of the children
		FloatRect cbounds = getChild(i)->getContentBounds();

		if(getChild(i)->m_visible)
		{
			// stretch to children if needed
			if(cbounds.left < bounds.left) bounds.left = cbounds.left;
			if(cbounds.top < bounds.top) bounds.top = cbounds.top;
			if(cbounds.left + cbounds.width > bounds.left + bounds.width) bounds.width = cbounds.left + cbounds.width - bounds.left;
			if(cbounds.top + cbounds.height > bounds.top + bounds.height) bounds.height = cbounds.top + cbounds.height - bounds.top;
		}
	}
	return bounds;
};

/// Returns true when the control is subject of being layout in a grid or other organization form
/// Most controls don't implement this function, as their default behavior is to respond to layouts always
bool UIControl::respondsToLayouts(){
	return true;
};

void UIControl::setSize(float width, float height)
{
	float pX = m_bounds.width;
	float pY = m_bounds.height;

	m_bounds.width = width;
	m_bounds.height = height;

	for(std::vector<UIControl*>::iterator it = m_children.begin(); it != m_children.end(); it++)
	{
		// tell children that the size of this control has changed
		(*it)->processSizeChange(pX, pY);
	}

	onResize();

	onSizeChanged();

	if(m_parent && m_parent->m_stretchForContents) // Goes up the tree
	{
		float bottom = m_parent->getBounds().top + m_parent->getBounds().height;
		// warn parent to stretch
		float lowestBottom = m_parent->getBounds().top;
		for(int i = 0; i < m_parent->getChildCount(); i++)
		{
			if(m_parent->getChild(i)->getBounds().top + m_parent->getChild(i)->getBounds().height > bottom) bottom = m_parent->getChild(i)->getBounds().top + m_parent->getChild(i)->getBounds().height;
		}
		m_parent->setSize(m_parent->getBounds().width, bottom - m_parent->getBounds().top);
	}

	updateLayout();
};

/// Immediately sets the center of the control to a new position
void UIControl::setCenter(float x, float y){
	m_bounds.setCenter(x,y);
	onPositionChanged();

	updateLayout();
};

void UIControl::innerDraw(Renderer* renderer, const mat4& transform )
{
	if(!m_visible)return; // no drawing or propagation - ghost

	//renderer->setModelMatrix(transform * m_transform);

	/// Draw the background color and borders - TODO: no debug draw
	vec4 middlePoint = transform * m_transform * vec4(0,0,0,1);
	//renderer->drawDebugQuad(middlePoint.x + m_bounds.width/2, middlePoint.y + m_bounds.height/2, 0,m_bounds.width, m_bounds.height, m_backgroundColor);
	
//	renderer->setModelMatrix(transform * m_transform);
	if(drawColoredBackground)
	{
		RectangleShape rect;
		rect.setPosition(m_bounds.left, m_bounds.top);
		rect.setSize(m_bounds.width, m_bounds.height);
		rect.setColor(m_backgroundColor);
		renderer->draw(rect);
	}

	//renderer->setModelMatrix(transform * m_transform);

	if(m_drawBorder)
	{
		//renderer->drawDebugLine(Vec2f(m_bounds.left, m_bounds.top), Vec2f(m_bounds.left + m_bounds.width, m_bounds.top), m_topBorderColor);
		//renderer->drawDebugLine(Vec2f(m_bounds.left, m_bounds.top + m_bounds.height), Vec2f(m_bounds.left + m_bounds.width, m_bounds.top + m_bounds.height), m_bottomBorderColor);
		//renderer->drawDebugLine(Vec2f(m_bounds.left, m_bounds.top), Vec2f(m_bounds.left, m_bounds.top + m_bounds.height), m_leftBorderColor);
		//renderer->drawDebugLine(Vec2f(m_bounds.left + m_bounds.width, m_bounds.top), Vec2f(m_bounds.left + m_bounds.width, m_bounds.top + m_bounds.height), m_rightBorderColor);

	}


	draw(renderer);
	
	// clip the overflowing children
	if(m_clipChildren)
	{
		if(getContext()->transformPointerCoordinates)
		{
			renderer->pushClippingRect(FloatRect(m_bounds.left / getContext()->targetWindowSize.x,m_bounds.top / getContext()->targetWindowSize.y,m_bounds.width / getContext()->targetWindowSize.x, m_bounds.height / getContext()->targetWindowSize.y), true);
		}
		else
		{
			renderer->pushClippingRect(FloatRect(m_bounds.left,m_bounds.top,m_bounds.width, m_bounds.height));
		}
	}

	// Let children render as well
	for(std::vector<UIControl*>::const_iterator it = m_children.begin(); it != m_children.end(); it++){
		(*it)->innerDraw(renderer, transform * m_transform);
	}

	if(m_clipChildren)
		renderer->popClippingRect();
}



/// Immediately sets the center of the control to a new position
void UIControl::setCenter(Vec2f position){
	setCenter(position.x, position.y);
};

/// Callback when the position of the control changed, for updating nested objects
void UIControl::onPositionChanged()
{
}

/// Define a new name for this control
void UIControl::setName(const String& name){
	m_name = name;
};

/// Get the name of the control
String UIControl::getName(){
	return m_name;
};

NEPHILIM_NS_END
