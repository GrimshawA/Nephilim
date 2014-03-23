#include <Nephilim/UIView.h>
#include <Nephilim/UIScroller.h>
#include <Nephilim/UIViewComponent.h>
#include <Nephilim/Logger.h>

#include <Nephilim/UILoader.h>

#include <algorithm>

NEPHILIM_NS_BEGIN

UIView::UIView()
: RefCountable()
, m_parent(NULL)
, m_positionFlags(0)
, m_sizeFlags(0)
, m_childrenLock(0)
, mCore(NULL)
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
, mRect(0.f, 0.f, 1.f, 1.f)
, m_pointerPressCount(0)
{

}


/// Construct and assign a parent directly
UIView::UIView(UIView* parent)
: RefCountable()
, m_parent(parent)
, m_positionFlags(0)
, m_sizeFlags(0)
, m_childrenLock(0)
, mCore(NULL)
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
, mRect(0.f, 0.f, 1.f, 1.f)
, m_pointerPressCount(0)
{
	if(parent)
	{
		parent->attach(this);
	}
}

UIView::~UIView()
{
	// Release all components to prevent leaks
	for(size_t i = 0; i < components.size(); ++i)
	{
		components[i]->onRelease(this);
		delete components[i];
	}

	// I am being destroyed, destroy children
	for(size_t i = 0; i < m_children.size(); ++i)
	{
		delete m_children[i];
	}
}

/// Load the hierarchy of this view from a file and configure itself
void UIView::load(const String& filename)
{
	UILoader uiLoader;
	uiLoader.configure(this, filename);
}

/// Add a component to the view
void UIView::addComponent(UIViewComponent* component)
{
	if(!component)
		return;

	components.push_back(component);
	component->onAttach(this);
}

/// Add a new component from a pre registered type
void UIView::addComponent(const String& name)
{
	if(name == "scroller")
	{
		addComponent(new UIComponentScroll());
	}
}

/// Called before rendering the children UIView ( Virtual )
void UIView::preRender(Renderer* renderer){}

/// Called after rendering the children UIView ( Virtual )
void UIView::postRender(Renderer* renderer){}

void UIView::setPosition(float x, float y)
{
	// Offset children
	vec2 offset = vec2(x,y) - getPosition();

	// -- update the top-left position of this control
	mRect.left = x;
	mRect.top = y;

	updateLayout();

	offsetChildrenPosition(offset);

	onPositionChanged();
}

void UIView::setPosition(vec2 position)
{
	setPosition(position.x, position.y);
}

vec2 UIView::getPosition()
{
	return vec2(mRect.left, mRect.top);
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
		Log("Cant clear now");
		return;
	}

	// I am being destroyed, destroy children
	for(size_t i = 0; i < m_children.size(); ++i)
	{
		delete m_children[i];
	}

	m_children.clear();
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
	m_backgroundColor.a = static_cast<Uint8>(alpha * 255);
}

float UIView::axGetAlpha()
{
	return static_cast<float>(m_backgroundColor.a / 255);
}

void UIView::axKillTrigger()
{
	destroy();
}

void UIView::offsetChildrenPosition(vec2 offset)
{
	for(size_t i = 0; i < m_children.size(); ++i)
	{
		m_children[i]->setPosition(m_children[i]->getPosition() + offset);
	}
}

/// Set the flags for sizing
void UIView::setSizeFlags(Uint64 flags)
{
	m_sizeFlags = flags;

	processSizeFlags();
}

void UIView::commitAnimation(AxBase* animation)
{
	animation->addTarget(this);
	animation->deduceInitialParameters();
	m_animations.commit(animation);
}

/// Get the sizing flags
Uint64 UIView::getSizeFlags()
{
	return m_sizeFlags;
}

/// Check if there is a particular sizing flag
bool UIView::hasSizeFlag(Uint64 flag)
{
	return ( (m_sizeFlags & flag) == flag);
}

/// Get the current positioning flags
Uint64 UIView::getPositionFlags()
{
	return m_positionFlags;
}

/// Check the existence of a particular flag for positioning
bool UIView::hasPositionFlag(Uint64 flag)
{
	return ( (m_positionFlags & flag) == flag);
}


/// Set positioning flags to the control
void UIView::setPositionFlags(Uint64 flags)
{
	m_positionFlags = flags;

	//(~(Uint64)0))

	processPositionFlags();
}

void UIView::onChildRemoved(UIView* control)
{

}

/// Attempt to process positional flags
void UIView::processPositionFlags()
{
	// Lets set the position flags now
	if(getParent() && getContext())
	{
		if( hasPositionFlag(UIPositionFlag::AttachBottom))
		{
			setPosition(mRect.left, getParent()->getSize().y - getSize().y);
		}
	}
}

/// Attempt to process size flags
void UIView::processSizeFlags()
{
	// Lets set the position flags now
	if(getParent() && getContext())
	{
		
	}
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
Vec2f UIView::getSize()
{
	return Vec2f(mRect.width, mRect.height);
}

/// Set a new layout to the control
void UIView::setLayout(UILayout* layout){
	m_layoutController = layout;

	// Perform the layouting
	m_layoutController->doLayout(this);
};

/// Get the currently assigned layout controller
/// \return NULL if there is no layout controller assigned
UILayout* UIView::getLayout()
{
	return m_layoutController;
};


/// Callback to render itself, renders children
void UIView::draw(Renderer* renderer)
{
	// back
	
	if(components.size() == 0)
	{
		RectangleShape backgroundRect;
		backgroundRect.setColor(Color::Grass);
		backgroundRect.setRect(getBounds());
		renderer->draw(backgroundRect);
	}
	

	/*
	if(m_children.size() > 0)
	{
		RectangleShape scrollBarBackground;
		scrollBarBackground.setSize(17.f, getSize().y);
		scrollBarBackground.setPosition(getPosition().x + getSize().y - 17.f, getPosition().y);
		scrollBarBackground.setColor(Color::Blue);
		renderer->draw(scrollBarBackground);

		float lowestY = m_children[0]->getPosition().y;
		float highestY = m_children[0]->getPosition().y + m_children[0]->getSize().y;
		for(size_t i = 0; i < m_children.size(); ++i)
		{
			if(m_children[i]->getPosition().y < lowestY)
			{
				lowestY = m_children[i]->getPosition().y;
			}

			if(m_children[i]->getPosition().y + m_children[i]->getSize().y > highestY)
			{
				highestY = m_children[i]->getPosition().y + m_children[i]->getSize().y;
			}
		}

		Log("Window %f to %f, Content %f to %f", getPosition().y, getPosition().y + getSize().y, lowestY, highestY);

		float beginPercent = (getPosition().y - lowestY) / (highestY  - lowestY);
		float endPercent = (getPosition().y + getSize().y - lowestY) / (highestY  - lowestY);

		Log("You are viewing %f pc of the content", beginPercent);

		RectangleShape scrollBarPaddle;
		scrollBarPaddle.setSize(17.f, getSize().y * (endPercent-beginPercent));
		scrollBarPaddle.setPosition(getPosition().x + getSize().y - 17.f, getPosition().y + getSize().y * beginPercent);
		scrollBarPaddle.setColor(Color::Red);
		renderer->draw(scrollBarPaddle);
	}*/
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
	for(size_t i = 0; i < components.size(); ++i)
	{
		components[i]->onEvent(event, this);
	}
}

bool UIView::onEventNotification(Event& event)
{
	
	return false;
};

/// Get bounds of the control
FloatRect UIView::getBounds(){
	return mRect;
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
bool UIView::hasFocus()
{
	return m_hasFocus;
};

/// Hierarchicly sets the context to all children
void UIView::setContext(UICore* states)
{
	mCore = states;

	// -- Being inserted in a UICanvas hierarchy
	setPositionFlags(mCore->defaultPositionFlags);
	setSizeFlags(mCore->defaultSizeFlags);

	for(std::vector<UIView*>::iterator it = m_children.begin(); it != m_children.end(); ++it)
	{
		(*it)->setContext(states);
	}

	switchLanguage();
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

void UIView::switchLanguage()
{
	innerLanguageSwitch();

	for(std::vector<UIView*>::iterator it = m_children.begin(); it != m_children.end(); it++){
		// lets see!
		(*it)->switchLanguage();
	}
}

void UIView::processSizeChange(float previousWidth, float previousHeight, float newWidth, float newHeight)
{
	// -- If the control was previously at a uninitialized size, don't process any flags
	if(previousHeight == 0.f || previousWidth == 0.f)
		return;

	// -- Go through children and adapt them according to their flags
	for(std::vector<UIView*>::iterator it = m_children.begin(); it != m_children.end(); ++it)
	{
		// -- Auto Resize: Ensure the same % width of the parent is occupied
		if((*it)->hasSizeFlag(UISizeFlag::KeepRelativeSizeX))
		{
			float percent = (*it)->getSize().x / previousWidth;
			(*it)->setSize(newWidth * percent, (*it)->getSize().y);
		}

		// -- Auto Resize: Ensure the same % height of the parent is occupied
		if((*it)->hasSizeFlag(UISizeFlag::KeepRelativeSizeY))
		{
			float percent = (*it)->getSize().y / previousHeight;
			(*it)->setSize((*it)->getSize().x, newHeight * percent);
		}

		// -- Auto Reposition: Ensure the control sits at the same % of the parent widget
		if((*it)->hasPositionFlag(UIPositionFlag::KeepRelativePositionX))
		{
			float percent = ((*it)->getPosition().x - getPosition().x) / previousWidth;
			(*it)->setPosition(getPosition().x + (newWidth * percent), (*it)->getPosition().y);
		}

		// -- Auto Reposition: Ensure the control sits at the same % of the parent widget
		if((*it)->hasPositionFlag(UIPositionFlag::KeepRelativePositionY))
		{
			float percent = ((*it)->getPosition().y - getPosition().y) / previousHeight;
			(*it)->setPosition((*it)->getPosition().x, getPosition().y + (newHeight * percent));
		}
	}
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
		FloatRect controlRect = (*it)->getBounds();
		FloatRect testRect(controlRect.left, controlRect.top, controlRect.width - 1, controlRect.height - 1);

		(*it)->processMouseMove(x,y);

		if(testRect.contains(x,y))
		{
			if(!(*it)->m_hovered)
			{
				(*it)->setPseudoClass("hover", true);
				(*it)->m_hovered = true;
				(*it)->onMouseEnter();
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

bool UIView::processTouchMove(int x, int y)
{
	onMouseMove();

	for(std::vector<UIView*>::iterator it = m_children.begin(); it != m_children.end(); it++)
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
bool UIView::processMouseButtonPressed(int x, int y, Mouse::Button button)
{
	if(!m_visible)
	{
		return true;
	}

	m_childrenLock++;
	for(std::vector<UIView*>::iterator it = m_children.begin(); it != m_children.end(); it++)
	{
		if((*it)->getBounds().contains(x,y) && (*it)->m_visible)
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
		if((*it)->getBounds().contains(x,y) && (*it)->m_visible)
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
	return mRect;
};

/// Get the position of the exact middle of this UIWindow
Vec2f UIView::getMiddlePosition(){
	return Vec2f(mRect.left + mRect.width/2, mRect.top + mRect.height/2);
};


/// Returns the UIWindow context or NULL if not attached
UICore* UIView::getContext()
{
	return mCore;
};

UIView* UIView::getParent()
{
	return m_parent;
}

void UIView::applyPendingOperations()
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


void UIView::attach(UIView* control)
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

	if(mCore)
		control->setContext(mCore);

	//control->processSizeChange(getSize().x, getSize().y);

//	updateLayout();
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
	if(getName() == name)
		return this;

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
	if(m_childrenLock > 0)
	{
		UIControlOperation op;
		op.type =  UIControlOperation::Destruction;
		op.control = child;
		m_pendingOperations.push_back(op);
	}
}

/// Callback when the control is resized
void UIView::onResize(){

}

/// Resizes the control over a defined time
/// The lower border of the control will become at target position
void UIView::resizeToPoint(float x, float y, float duration){

};

void UIView::resize(float width, float height, float duration)
{

};

/// Update layout of children
void UIView::updateLayout()
{
	if(m_layoutController)
	{
		m_layoutController->doLayout(this);
	}
}

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

	for(size_t i = 0; i < components.size(); ++i)
	{
		components[i]->onUpdate(Time::fromSeconds(elapsedTime), this);
	}
}

/// Get the current size of the control that encompasses all its children
FloatRect UIView::getContentBounds()
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
bool UIView::respondsToLayouts(){
	return true;
};

void UIView::setSize(float width, float height)
{
	// -- This control is about to be resized, might need to do some automatic operations on children
	processSizeChange(mRect.width, mRect.height, width, height);

	float pX = mRect.width;
	float pY = mRect.height;

	mRect.width = width;
	mRect.height = height;
	
	onResize();

	onSizeChanged();

	updateLayout();

	// Let components know a resize was made
	for(size_t i = 0; i < components.size(); ++i)
	{
		components[i]->onResize(this);
	}
};

/// Immediately sets the center of the control to a new position
void UIView::setCenter(float x, float y)
{
	mRect.setCenter(x,y);
	onPositionChanged();

	updateLayout();
};

void UIView::innerDraw(Renderer* renderer, const mat4& transform )
{
	// Invisible UIView, stop rendering itself or children
	if(!m_visible)
	{
		return;
	}

	if(m_clipContents)
	{
		renderer->pushClippingRect(FloatRect(mRect.left,mRect.top,mRect.width, mRect.height));
	}
	draw(renderer);


	for(size_t i = 0; i < components.size(); ++i)
	{
		components[i]->onRender(renderer, this);
	}
	if(m_clipContents)
	{
		renderer->popClippingRect();
	}
	// -- Pre Render Step (Before Children)
	preRender(renderer);
	
	// clip the overflowing children
	if(m_clipChildren)
	{
		if(getContext()->transformPointerCoordinates)
		{
			renderer->pushClippingRect(FloatRect(mRect.left / getContext()->targetWindowSize.x,mRect.top / getContext()->targetWindowSize.y,mRect.width / getContext()->targetWindowSize.x, mRect.height / getContext()->targetWindowSize.y), true);
		}
		else
		{
			renderer->pushClippingRect(FloatRect(mRect.left,mRect.top,mRect.width, mRect.height));
		}
	}

	// Let children render as well
	for(std::vector<UIView*>::const_iterator it = m_children.begin(); it != m_children.end(); it++){
		(*it)->innerDraw(renderer, transform * m_transform);
	}

	if(m_clipChildren)
		renderer->popClippingRect();

	// -- Post Render Step (After Children)
	postRender(renderer);
}

void UIView::enableAutoResize(bool enable)
{
	if(enable)
	{
		setPositionFlags(UIPositionFlag::KeepRelativePositionX | UIPositionFlag::KeepRelativePositionY);
		setSizeFlags(UISizeFlag::KeepRelativeSizeX | UISizeFlag::KeepRelativeSizeY);
	}
}

/// Returns the first component with the given type
UIViewComponent* UIView::getComponentByType(UIViewComponent::Type type)
{
	for(size_t i = 0; i < components.size(); ++i)
	{
		if(components[i]->component_id == type)
		{
			return components[i];
		}
	}
	return NULL;
}

/// Immediately sets the center of the control to a new position
void UIView::setCenter(Vec2f position)
{
	setCenter(position.x, position.y);
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
String UIView::getName()
{
	return m_name;
}

NEPHILIM_NS_END
