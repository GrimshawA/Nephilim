#include <Nephilim/UIWindow.h>
#include <Nephilim/Text.h>
#include <Nephilim/UILabel.h>

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

/// Construct the window
UIWindow::UIWindow() : m_surfaceContainerLock(false), m_timeSinceLastMouseMovement(0.f), m_backgroundColor(Color::White){
	m_surfaces.push_back(new UISurface());
	m_surfaces.back()->setContext(&m_state);

	m_backgroundColor =  Color(0,0,0,0);
};

/// Creates a new surface, which is underneath the relativeSurface specified
UISurface* UIWindow::createSurfaceBelow(UISurface* relativeSurface, const String& name){
	if(!relativeSurface) return NULL;

	for(std::vector<UISurface*>::iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++){
		if((*it) == relativeSurface){
			// This where where to insert
			UISurface* surface = new UISurface();
			surface->setSize(m_bounds.width, m_bounds.height);
			surface->setName(name);
			m_surfaces.insert(it, surface);
			return surface;
		}
	}

	return NULL;
};

/// Get a surface by its name
UISurface* UIWindow::getSurfaceByName(const String& name){
	for(std::vector<UISurface*>::iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++){
		if((*it)->getName() == name){
			return (*it);
		}
	}
	return NULL;
};

UIStateContext& UIWindow::getContext(){
	return m_state;
}

/// Makes a list of controls from a selector - CSS like
UIWindow::ControlList UIWindow::selectControls(const String& selector)
{
	ControlList list;

	return list;
}

/// Sets new boundaries to this UIWindow
void UIWindow::setRect(Rect<float> rect){
	m_bounds = rect;

	// resize happened
	for(std::vector<UISurface*>::iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++){
		(*it)->setPosition(m_bounds.left, m_bounds.top);
		(*it)->setSize(m_bounds.width, m_bounds.height);
		(*it)->processSizeChange();
	}

	// Finnaly, since the UIWindow rectangle changed, its time to adjust all the children that require it
};

/// Get the position of the exact middle of this UIWindow
Vec2f UIWindow::getMiddlePosition(){
	return Vec2f(m_bounds.left + m_bounds.width/2, m_bounds.top + m_bounds.height/2);
};

/// Get the surface closer to the user
UISurface* UIWindow::getTopSurface(){
	if(m_surfaces.empty()) return NULL;
	else{
		return m_surfaces[0];
	}
};

void UIWindow::showMessageBox(const String& message)
{
	cout<<"Message: "<<message<<endl;
	UIControl* modalBackground = new UIControl();
	
	modalBackground->setProperty<Color>("background-color", Color(0,0,0, 80));
	
	UISurface* surface = addSurface("modal");
	surface->addControl(modalBackground);
	modalBackground->setRect(surface->getRect());

	UILabel* label = new UILabel(message);
	label->setSize(700,50);
	label->setCenter(modalBackground->getMiddlePosition());
	label->setProperty<Color>("background-color", Color(0,0,0));
	label->setProperty<Color>("color", Color::White);
	modalBackground->addControl(label);
};


/// Returns a control in the hierarchy with the name, or NULL if not found
UIControl* UIWindow::getControlByName(const String& name){
	UIControl* control = NULL;
	for(std::vector<UISurface*>::const_iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++){
		control = (*it)->getControlByName(name);
		if(control != NULL) return control; // the surface returned something
	}

	return NULL; // Nothing found.
};

UISurface* UIWindow::addSurface(const String& name)
{
	UISurface* surface = new UISurface();
	surface->setName(name);
	surface->setPosition(m_bounds.left, m_bounds.top);
	surface->setSize(m_bounds.width, m_bounds.height);
	surface->setContext(&m_state);

	if(!m_surfaceContainerLock)
		m_surfaces.push_back(surface);
	else
	{
		// Schedule add
		PendingChange change;
		change.type = Add;
		change.surface = surface;
		m_pendingChanges.push_back(change);
	}

	return surface;
};


/// Draw the UI
void UIWindow::draw(Renderer* renderer){
	renderer->drawDebugQuad(m_bounds.left + m_bounds.width/2, m_bounds.top + m_bounds.height/2, 0, m_bounds.width, m_bounds.height, m_backgroundColor);
	renderer->drawDebugLine(Vec2f(m_bounds.left, m_bounds.top), Vec2f(m_bounds.left + m_bounds.width, m_bounds.top), m_topBorderColor);
	renderer->drawDebugLine(Vec2f(m_bounds.left, m_bounds.top + m_bounds.height), Vec2f(m_bounds.left + m_bounds.width, m_bounds.top + m_bounds.height), m_bottomBorderColor);
	renderer->drawDebugLine(Vec2f(m_bounds.left, m_bounds.top), Vec2f(m_bounds.left, m_bounds.top + m_bounds.height), m_leftBorderColor);
	renderer->drawDebugLine(Vec2f(m_bounds.left + m_bounds.width, m_bounds.top), Vec2f(m_bounds.left + m_bounds.width, m_bounds.top + m_bounds.height), m_rightBorderColor);

	/// Draw surfaces bottom to top
	for(std::vector<UISurface*>::iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++){
		(*it)->draw(renderer);
	}	
};

/// Update the state of the ui
void UIWindow::update(float elapsedTime){
	m_timeSinceLastMouseMovement += elapsedTime;
	if(m_timeSinceLastMouseMovement >= 1.2f){
		// time to show a tool tip
		m_showingToolTip = true;
	}

	for(std::vector<UISurface*>::reverse_iterator it = m_surfaces.rbegin(); it != m_surfaces.rend(); it++){
		(*it)->onUpdate(elapsedTime);
	}
};

/// Pushes a new event through the ui system
bool UIWindow::pushEvent(Event& event){
	bool result = true;
	/// Tooltip related
	if(event.type == Event::MouseMoved){
		m_timeSinceLastMouseMovement = 0.f; m_showingToolTip = false;
	
		//test drag
		if(m_state.m_dragControl)
		{
			m_state.m_dragControl->setPosition(event.mouseMove.x - m_state.m_dragOffset.x, event.mouseMove.y - m_state.m_dragOffset.y);
		}
	}

	if(event.type == Event::Resume)
	{

		m_state.m_defaultFont.loadFromFile("Brutality.ttf");

		for(std::vector<UISurface*>::iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++){
			(*it)->reloadGraphicalAssets();
			TESTLOG("RELOADING SURFACE")

		}
	}


	// Handling keyboard
	if(event.type == Event::KeyPressed)
	{
		// Deliver input to the focused control
		if(m_state.m_focusControl)
		{
			m_state.m_focusControl->onKeyPressed(event.key.code);
		}
	}
	else if(event.type == Event::KeyReleased)
	{

	}
	else if(event.type == Event::TextEntered)
	{
		// Deliver input to the focused control
		if(m_state.m_focusControl)
		{
			m_state.m_focusControl->onTextEvent(event.text.unicode);
		}
	}

	// lock for iteration
	m_surfaceContainerLock = true;
	for(std::vector<UISurface*>::const_iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++){
		if(!(*it)->onEventNotification(event)){
			result = false; // no propagation of the event for lower layers if the surface returns false
			break;
		}
	}
	m_surfaceContainerLock = false;


	// Handle events
	switch(event.type)
	{
		case Event::MouseMoved:
			{
				result = processMouseMove(event.mouseMove.x, event.mouseMove.y);
			}
		break;

		case Event::MouseButtonPressed:
			{
				// if the click is outside the focus control, unfocus it
				if(m_state.m_focusControl)
				{
					if(!m_state.m_focusControl->getBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						m_state.m_focusControl->blur();
						m_state.m_focusControl->onLostFocus();
						m_state.m_focusControl = NULL;
					}
				}
				result = processMouseButtonPressed(event.mouseButton.x, event.mouseButton.y, event.mouseButton.button);
			}
		break;
	}

	// now that surfaces were processed, apply changes to surfaces container
	// the updates in the container are only considered in the next event, so it is not wrongly consumed
	applyPendingChanges();

	return result;
};

/// Set the current language of the ui system
void UIWindow::setLanguage(const String& shortLanguageName)
{
	m_state.m_activeLanguage = shortLanguageName;
	m_state.m_localization.m_currentLanguage = shortLanguageName;
	for(std::vector<UISurface*>::const_iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++){
		(*it)->switchLanguage();
	}
};

/// Process a mouse press event
bool UIWindow::processMouseButtonPressed(int x, int y, Mouse::Button button)
{
	for(std::vector<UISurface*>::const_iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++){
		(*it)->processMouseButtonPressed(x,y,button);
	}
	return false;
}

/// Process a mouve movement event
bool UIWindow::processMouseMove(int x, int y)
{
	for(std::vector<UISurface*>::const_iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++){
		(*it)->processMouseMove(x,y);
	}
	return false;
}


void UIWindow::applyPendingChanges()
{
	for(unsigned int i = 0; i < m_pendingChanges.size(); i++)
	{
		switch(m_pendingChanges[i].type)
		{
			case Add:
				m_surfaces.push_back(m_pendingChanges[i].surface);
			break;
		}
	}
	m_pendingChanges.clear();
};



NEPHILIM_NS_END