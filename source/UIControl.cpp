#include <Nephilim/UIControl.h>
#include <Nephilim/Logger.h>

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

/// Base constructor of controls
UIControl::UIControl()
: RefCountable()
, m_parent(NULL)
, m_positionFlags(0)
, m_sizeFlags(0)
,
		m_stateContext(NULL),
		m_hasFocus(false),
		m_layoutController(NULL),
		m_backgroundColor(91,91,91),
		m_topBorderColor(69,69,69),
		m_leftBorderColor(m_topBorderColor),
		m_rightBorderColor(m_topBorderColor),
		m_bottomBorderColor(m_topBorderColor),
		m_clipChildren(false),
		m_clipContents(false),
		m_visible(true),
		m_drawBorder(true),
		m_stretchForContents(false),
		m_hovered(false)
{

	m_resizeAnimation.addAnimable(this);
	m_positionAnimation.addAnimable(this);

	m_minimumDimensions = Vec2f(10,10);
	m_maximumDimensions = Vec2f(5000,5000);
};

/// Get the coordinates of the top-left corner of the control
vec2 UIControl::getPosition()
{
	return vec2(m_bounds.left, m_bounds.top);
}

/// Set the flags for sizing
void UIControl::setSizeFlags(Uint64 flags)
{
	m_sizeFlags = flags;

	processSizeFlags();
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

/// Callback to handle events
bool UIControl::onEventNotification(Event& event){
	for(std::vector<UIControl*>::const_iterator it = m_children.begin(); it != m_children.end(); it++){
		(*it)->onEventNotification(event);
	}
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
		cout<<"Cant focus an element without a hierarchy"<<endl;
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

	for(std::vector<UIControl*>::iterator it = m_children.begin(); it != m_children.end(); it++){
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
	if(!m_hovered)
	{
		setPseudoClass("hover", true);
		onMouseEnter();
		m_hovered = true;

		
	}

	onMouseMove();

	for(std::vector<UIControl*>::iterator it = m_children.begin(); it != m_children.end(); it++){
		FloatRect controlRect = (*it)->getBounds();
		FloatRect testRect(controlRect.left, controlRect.top, controlRect.width - 1, controlRect.height - 1);

		if(testRect.contains(x,y))
		{
			(*it)->processMouseMove(x,y);
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
	bool result = false;
	if(isFocusable())
	{
		focus();
	}

	for(std::vector<UIControl*>::iterator it = m_children.begin(); it != m_children.end(); it++){
		if((*it)->getBounds().contains(x,y))
		{
			result = true;
			(*it)->processMouseButtonPressed(x,y, button);
		}
	}

	return result;
}

/// Enables or disables a pseudo class
void UIControl::setPseudoClass(const String& name, bool active)
{
	if(active)
	{
		//cout<<"[UIControl] Pseudoclass enabled: "<<name<<endl;
	}
};

void UIControl::bindSignal(const String& name, ASSlot* slot)
{
	/*if(name == "click")
	{
		//cout<<"Attempting to bind click to a slot"<<endl;
		onClick.connect(MAKE_SLOT_OBJECT(ASSlot, slot, trigger));
	}

	if(name == "mousemove")
	{
		//cout<<"[UIControl] Mouse move attachment."<<endl;
		onMouseMove.connect(MAKE_SLOT_OBJECT(ASSlot, slot, trigger));
	}

	if(name == "mouseenter")
	{
		onMouseEnter.connect(MAKE_SLOT_OBJECT(ASSlot, slot, trigger));
	}

	if(name == "mouseleave")
	{
		onMouseLeave.connect(MAKE_SLOT_OBJECT(ASSlot, slot, trigger));
	}
	if(name == "resize")
	{
		//cout<<"[UIControl] Resize Attachment"<<endl;
		onSizeChanged.connect(MAKE_SLOT_OBJECT(ASSlot, slot, trigger));
	}*/
}


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
};

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


/// Adds a new control ... wrong API todo
void UIControl::attach(UIControl* control){
	m_children.push_back(control);
	control->addReference();
	// Assign
	control->m_parent = this;
	control->setContext(m_stateContext);

	control->processSizeChange(getSize().x, getSize().y);

	updateLayout();
};

/// Callback when the control is resized
void UIControl::onResize(){

}

/// Resizes the control over a defined time
/// The lower border of the control will become at target position
void UIControl::resizeToPoint(float x, float y, float duration){
	Vec2f size;
	size.x = x - m_bounds.left;
	size.y = y - m_bounds.top;
	// ensure min and max
	if(size.x < m_minimumDimensions.x)size.x = m_minimumDimensions.x;
	if(size.y < m_minimumDimensions.y)size.y = m_minimumDimensions.y;
	if(size.x > m_maximumDimensions.x)size.x = m_maximumDimensions.x;
	if(size.y > m_maximumDimensions.y)size.y = m_maximumDimensions.y;

	m_resizeAnimation.setDestination(size.x,size.y);
	m_resizeAnimation.setDuration(duration);
	m_resizeAnimation.stop();
	m_resizeAnimation.play();
};

void UIControl::resize(float width, float height, float duration)
{
	m_resizeAnimation.setDestination(width,height);
	m_resizeAnimation.setDuration(duration);
	m_resizeAnimation.stop();
	m_resizeAnimation.play();
};

void UIControl::reposition(float x, float y, float duration)
{
	m_positionAnimation.setDestination(x, y);
	m_positionAnimation.setDuration(duration);
	m_positionAnimation.stop();
	m_positionAnimation.play();
};



/// Making this class able to animate sizes
void UIControl::animable_set_size(float x, float y){
	setSize(x,y);
	onResize();
};

Vec2f UIControl::animable_get_size(){
	return Vec2f(m_bounds.width, m_bounds.height);
};

void UIControl::animable_set_position(float x, float y)
{
	m_bounds.left = x;
	m_bounds.top = y;
};

Vec2f UIControl::animable_get_position()
{
	return Vec2f(m_bounds.left, m_bounds.top);
};

/// Set the position of the control
void UIControl::setPosition(float x, float y)
{
	m_bounds.left = x;
	m_bounds.top = y;

	updateLayout();
};

/// Update layout of children
void UIControl::updateLayout()
{
	if(m_layoutController)
	{
		m_layoutController->doLayout(this);
	}
}

/// Update the control
void UIControl::onUpdate(float elapsedTime){

	m_resizeAnimation.onUpdate(elapsedTime);
	m_positionAnimation.onUpdate(elapsedTime);

	for(std::vector<UIControl*>::const_iterator it = m_children.begin(); it != m_children.end(); it++){
		(*it)->onUpdate(elapsedTime);
	}
};

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

	renderer->setModelMatrix(transform * m_transform);

	/// Draw the background color and borders - TODO: no debug draw
	vec4 middlePoint = transform * m_transform * vec4(0,0,0,1);
	//renderer->drawDebugQuad(middlePoint.x + m_bounds.width/2, middlePoint.y + m_bounds.height/2, 0,m_bounds.width, m_bounds.height, m_backgroundColor);
	
	renderer->setModelMatrix(transform * m_transform);
	RectangleShape rect;
	rect.setPosition(m_bounds.left, m_bounds.top);
	rect.setSize(m_bounds.width, m_bounds.height);
	rect.setColor(m_backgroundColor);
	renderer->draw(rect);
	renderer->setModelMatrix(transform * m_transform);

	if(m_drawBorder)
	{
		//renderer->drawDebugLine(Vec2f(m_bounds.left, m_bounds.top), Vec2f(m_bounds.left + m_bounds.width, m_bounds.top), m_topBorderColor);
		//renderer->drawDebugLine(Vec2f(m_bounds.left, m_bounds.top + m_bounds.height), Vec2f(m_bounds.left + m_bounds.width, m_bounds.top + m_bounds.height), m_bottomBorderColor);
		//renderer->drawDebugLine(Vec2f(m_bounds.left, m_bounds.top), Vec2f(m_bounds.left, m_bounds.top + m_bounds.height), m_leftBorderColor);
		//renderer->drawDebugLine(Vec2f(m_bounds.left + m_bounds.width, m_bounds.top), Vec2f(m_bounds.left + m_bounds.width, m_bounds.top + m_bounds.height), m_rightBorderColor);

	}


	draw(renderer);
	/*
	// clip?
	if(m_clipChildren)renderer->enableClipping(FloatRect(m_bounds.left,m_bounds.top,m_bounds.width, m_bounds.height));

	// Let children render as well
	for(std::vector<UIControl*>::const_iterator it = m_children.begin(); it != m_children.end(); it++){
		(*it)->innerDraw(renderer, transform * m_transform);
	}

	if(m_clipChildren)renderer->disableClipping();*/
}



/// Immediately sets the center of the control to a new position
void UIControl::setCenter(Vec2f position){
	setCenter(position.x, position.y);
};

/// Callback when the position of the control changed, for updating nested objects
void UIControl::onPositionChanged(){

};

/// Define a new name for this control
void UIControl::setName(const String& name){
	m_name = name;
};

/// Get the name of the control
String UIControl::getName(){
	return m_name;
};

NEPHILIM_NS_END
