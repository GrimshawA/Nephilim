#include <Nephilim/UI/UICanvas.h>
#include <Nephilim/UI/UIWindow.h>
#include <Nephilim/Graphics/Text.h>
#include <Nephilim/UI/UILabel.h>
#include <Nephilim/UI/CSSLoader.h>

#include <algorithm>

NEPHILIM_NS_BEGIN

UICanvas::UICanvas()
: m_surfaceContainerLock(0)
, m_backgroundColor(Color::Transparent)
{
	_core = &m_state;
}

/// Name of this node
UICanvas::UICanvas(const String& name)
: UxNode()
, m_surfaceContainerLock(0)
, m_backgroundColor(Color::Transparent)
{
	_core = &m_state;
}

/// Get the object name of this node
const char* UICanvas::getName()
{
	return m_name.c_str();
}

/// Get the class name of this node
const char* UICanvas::getClassName()
{
	return "UICanvas";
}


void UICanvas::render(GraphicsDevice* gdi)
{
	draw(gdi);
}

/// Adds a layer to this canvas for 2D controls
void UICanvas::addLayer2D(const String& name)
{
	addSurface(name);
}

/// Adds a layer to this canvas for 3D controls
void UICanvas::addLayer3D(const String& name)
{
	addSurface(name);
}

/// Load a stylesheet file into the canvas
bool UICanvas::loadStylesheet(const String& filename)
{
	CSSLoader css_loader;
	return css_loader.load(filename, getCore().stylesheet);
}

/// Update the window size of the UI canvas
/// This will effectively change the size of all subwindows to match the new canvas size, if they are fullscreen
void UICanvas::setWindowSize(int w, int h)
{
	for (std::vector<UIWindow*>::iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++)
	{
		(*it)->setSize(w, h);
	}
}

void UICanvas::onDraw(GraphicsDevice* renderer)
{
	//m_backgroundColor = Color::White;
	//renderer->drawDebugQuad(m_bounds.left + m_bounds.width/2, m_bounds.top + m_bounds.height/2, 0, m_bounds.width, m_bounds.height, m_backgroundColor);
	//renderer->drawDebugLine(Vec2f(m_bounds.left, m_bounds.top), Vec2f(m_bounds.left + m_bounds.width, m_bounds.top), m_topBorderColor);
	//renderer->drawDebugLine(Vec2f(m_bounds.left, m_bounds.top + m_bounds.height), Vec2f(m_bounds.left + m_bounds.width, m_bounds.top + m_bounds.height), m_bottomBorderColor);
	//renderer->drawDebugLine(Vec2f(m_bounds.left, m_bounds.top), Vec2f(m_bounds.left, m_bounds.top + m_bounds.height), m_leftBorderColor);
	//renderer->drawDebugLine(Vec2f(m_bounds.left + m_bounds.width, m_bounds.top), Vec2f(m_bounds.left + m_bounds.width, m_bounds.top + m_bounds.height), m_rightBorderColor);

	/// Draw surfaces bottom to top
	m_surfaceContainerLock++;
	for(std::vector<UIWindow*>::iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++)
	{
		(*it)->draw(renderer);
	}
	m_surfaceContainerLock--;

	if (getCore().dragElement)
	{
		getCore().dragElement->drawItself(renderer, mat4::identity);
		Log("Rendering the drag element");
	}
}

UIWindow* UICanvas::getLayer(const String& name)
{
	UIWindow* found = NULL;
	for(std::vector<UIWindow*>::iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++)
	{
		if((*it)->getName() == name)
		{
			found = (*it);
		}
	}

	if(!found)
	{
		for(unsigned int i = 0; i < m_pendingChanges.size(); i++)
		{
			if(m_pendingChanges[i].type == Add && m_pendingChanges[i].surface->getName() == name)
			{
				found = m_pendingChanges[i].surface;
			}
		}
	}

	return found;
}

UICore& UICanvas::getCore()
{
	return m_state;
}

/// Makes a list of controls from a selector - CSS like
UICanvas::ControlList UICanvas::selectControls(const String& selector)
{
	ControlList list;

	return list;
}

/// Sets new boundaries to this UIWindow
void UICanvas::setRect(Rect<float> rect)
{
	m_bounds = rect;

	// resize happened
	for(std::vector<UIWindow*>::iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++){
		(*it)->setPosition(m_bounds.left, m_bounds.top);
		(*it)->setSize(m_bounds.width, m_bounds.height);
	}

	// Finnaly, since the UIWindow rectangle changed, its time to adjust all the children that require it
};

/// Set the new boundaries for this document
void UICanvas::setRect(float left, float top, float width, float height)
{
	setRect(FloatRect(left,top,width, height));
}

/// Print hierarchy information for debugging
void UICanvas::printHierarchy()
{
	// resize happened
	for(std::vector<UIWindow*>::iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++)
	{
		(*it)->printHierarchy();
	}
}

/// Get the position of the exact middle of this UIWindow
Vec2f UICanvas::getMiddlePosition()
{
	return Vec2f(m_bounds.left + m_bounds.width/2, m_bounds.top + m_bounds.height/2);
};

void UICanvas::clearUnusedSurfaces()
{

}

/// Push a new modal surface to the top, it will destroy itself once there are no more controls in it
void UICanvas::pushModalSurface()
{
	addSurface("auto_modal");
	top()->setModal(true);
}

//debug
void UICanvas::debugData()
{
	Log("Surface count: %d", m_surfaces.size());
	for(std::vector<UIWindow*>::const_iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++){
		//Log("Surface: %s", (*it)->getName().c_str());
	}
}

/// Get the current surface count
int UICanvas::getSurfaceCount()
{
	return static_cast<int>(m_surfaces.size());
}

/// Get a surface by its name. It will be created if it does not yet exist
UIWindow* UICanvas::operator[](const String& name)
{
	UIWindow* surface = getLayer(name);
	if(!surface)
	{
		surface = addSurface(name);
	}

	return surface;
}

UIWindow* UICanvas::top()
{
	if(m_surfaces.empty())
	{
		return NULL;
	}
	else
	{
		UIWindow* lastSurface = m_surfaces.back();
		for(std::size_t i = 0; i < m_pendingChanges.size(); ++i)
		{
			if(m_pendingChanges[i].type == Add)
			{
				lastSurface = m_pendingChanges[i].surface;
			}
		}
		return lastSurface;
	}
}

void UICanvas::showMessageBox(const String& message)
{
	Widget* modalBackground = new Widget();
	
	UIWindow* surface = addSurface("modal");
	surface->attach(modalBackground);
	modalBackground->setRect(surface->getRect());

	UILabel* label = new UILabel(message);
	label->setSize(700,50);
	//label->setCenter(modalBackground->getMiddlePosition());
	modalBackground->attach(label);
};


/// Returns a control in the hierarchy with the name, or NULL if not found
Widget* UICanvas::getControlByName(const String& name)
{
	Widget* control = NULL;
	for(std::vector<UIWindow*>::const_iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++)
	{
		control = (*it)->findByName(name);
		if(control != NULL) return control; // the surface returned something
	}

	return NULL; // Nothing found.
};

UIWindow* UICanvas::addSurface(const String& name)
{
	UIWindow* surface = new UIWindow();
	surface->setName(name);
	surface->setPosition(m_bounds.left, m_bounds.top);
	surface->setSize(m_bounds.width, m_bounds.height);
	surface->setContext(&m_state);
	surface->m_parentDocument = this;

	if(m_surfaceContainerLock == 0)
	{
		m_surfaces.push_back(surface);
	}
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

/// Create a window for this canvas
UIWindow* UICanvas::createWindow(const String& name)
{
	UIWindow* window = getLayer(name);
	if (!window)
	{
		addLayer2D(name);
		window = getLayer(name);
	}

	mChildren.push_back(window);

	return window;
}

/// Draw the UI
void UICanvas::draw(GraphicsDevice* renderer)
{
	/// Draw surfaces bottom to top
	for(std::vector<UIWindow*>::iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++)
	{
		if ((*it)->m_visible)
		{
			//Log("Drawing window: %s", (*it)->getName().c_str());
			(*it)->draw(renderer);
		}
	}


	if (getCore().dragElement)
	{
		getCore().dragElement->drawItself(renderer, mat4::identity);
	}

	if (getCore().contextMenuElement)
	{
		getCore().contextMenuElement->drawItself(renderer, mat4::identity);
	}

	if (!getCore().menuElementStack.empty())
	{
		getCore().menuElementStack[0]->drawItself(renderer, mat4::identity);
	}
};

/// Destroys a surface from its children
void UICanvas::destroySurface(UIWindow* surface)
{
	if(m_surfaceContainerLock > 0)
	{
		PendingChange op;
		op.surface = surface;
		op.type = Remove;
		m_pendingChanges.push_back(op);
	}
	else
	{
		m_surfaces.erase(std::find(m_surfaces.begin(), m_surfaces.end(), surface));
	}
}

/// Update the state of the ui
void UICanvas::update(float elapsedTime)
{	
	m_surfaceContainerLock++;
	for(std::vector<UIWindow*>::reverse_iterator it = m_surfaces.rbegin(); it != m_surfaces.rend(); it++)
	{
		(*it)->update(elapsedTime);
	}
	m_surfaceContainerLock--;

	applyPendingChanges();
}

UIEventResult UICanvas::pushEvent(const Event& event)
{
	Event processedEvent = event;
	
	UIEventResult eventUsage;

	// -- Raw event delivery system
	m_surfaceContainerLock++;
	for(std::vector<UIWindow*>::reverse_iterator it = m_surfaces.rbegin(); it != m_surfaces.rend(); it++)
	{
		if((*it)->getChildCount() > 0)
		{
			// deliver the event
			(*it)->dispatchEvent(processedEvent);

			if((*it)->isModal())
			{
				eventUsage.clickPassedThrough = false;
				break;
			}
		}
	}
	m_surfaceContainerLock--;

	// -- Built-in event handling
	switch(event.type)
	{
		case Event::MouseMoved:
			{
				processMouseMove(processedEvent.mouseMove.x, processedEvent.mouseMove.y);
			}
		break;

		case Event::TouchMoved:
			{
				processTouchMove(processedEvent.touch.x, processedEvent.touch.y);
			}
			break;

		case Event::MouseButtonPressed:
			{
				bool result = processMouseButtonPressed(processedEvent.mouseButton.x, processedEvent.mouseButton.y, processedEvent.mouseButton.button);
				eventUsage.hitControls = false;
			}
		break;

		case Event::TouchPressed:
			{
				bool result = processMouseButtonPressed(processedEvent.touch.x, processedEvent.touch.y, Mouse::Left);
				eventUsage.hitControls = false;
			}
			break;

		case Event::MouseButtonReleased:
			{				
				processMouseButtonReleased(processedEvent.mouseButton.x, processedEvent.mouseButton.y, processedEvent.mouseButton.button, eventUsage);
			}
			break;
		case Event::TouchReleased:
			{				
				processMouseButtonReleased(processedEvent.touch.x, processedEvent.touch.y, Mouse::Left, eventUsage);
			}
			break;

		case Event::TextEntered:
			{
				// Deliver input to the focused control
				if(m_state.m_focusControl)
				{
					UxKeyEvent keyEvent;
					keyEvent.type = UxKeyEvent::KeyPress;
					keyEvent.unicode = processedEvent.text.unicode;
					if (keyEvent.unicode >= 32)
						m_state.m_focusControl->keyPressEvent(&keyEvent);

					//m_state.m_focusControl->onTextEvent(processedEvent.text.unicode);
				}
			}
			break;

		case Event::KeyPressed:
		{
				// Deliver input to the focused control
				if (m_state.m_focusControl)
				{
					   UxKeyEvent keyEvent;
					   keyEvent.type = UxKeyEvent::KeyPress;
					   keyEvent.key = processedEvent.key.code;
					   m_state.m_focusControl->keyPressEvent(&keyEvent);
				}
		}break;
	}

	// now that surfaces were processed, apply changes to surfaces container
	// the updates in the container are only considered in the next event, so it is not wrongly consumed
	applyPendingChanges();

	return eventUsage;
};

int UICanvas::getModalSurfaceCount()
{
	int count = 0;

	// Check the established list
	for(std::vector<UIWindow*>::const_iterator it = m_surfaces.begin(); it != m_surfaces.end(); ++it)
	{
		if((*it)->isModal())
			count++;
	}

	for(std::size_t i = 0; i < m_pendingChanges.size(); ++i)
	{
		if(m_pendingChanges[i].type == Add && m_pendingChanges[i].surface->isModal())
		{
			count++;
		}
	}

	return count;
}

/// Set the current language of the ui system
void UICanvas::setLanguage(const String& shortLanguageName)
{
	/*m_state.m_activeLanguage = shortLanguageName;
	m_state.m_localization.m_currentLanguage = shortLanguageName;
	for(std::vector<UILayerView*>::const_iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++)
	{
		(*it)->switchLanguage();
	}*/
}

/// Process a mouse press event
bool UICanvas::processMouseButtonPressed(int x, int y, Mouse::Button button)
{
	m_surfaceContainerLock++;
	bool canContinue = true;
	for(std::vector<UIWindow*>::reverse_iterator it = m_surfaces.rbegin(); it != m_surfaces.rend() && canContinue; it++)
	{
		(*it)->processMouseButtonPressed(x,y,button);

		if((*it)->isModal())
		{
			//eventUsage.clickPassedThrough = false;
			canContinue = false;
		}
	}
	m_surfaceContainerLock--;

	return false;
}

void UICanvas::processMouseButtonReleased(int x, int y, Mouse::Button button, UIEventResult& info)
{
	m_surfaceContainerLock++;
	bool canContinue = true;
	for(std::vector<UIWindow*>::reverse_iterator it = m_surfaces.rbegin(); it != m_surfaces.rend(); ++it)
	{
		if(canContinue)
		{
			(*it)->processMouseButtonReleased(x, y, button, info);

			if((*it)->isModal())
			{
				canContinue = false;
			}
		}
	}
	m_surfaceContainerLock --;

	applyPendingChanges();
}


/// Process a mouve movement event
bool UICanvas::processMouseMove(int x, int y)
{
	m_surfaceContainerLock++;
	bool canContinue = true;
	for(std::vector<UIWindow*>::reverse_iterator it = m_surfaces.rbegin(); it != m_surfaces.rend() && canContinue; it++){
		(*it)->processMouseMove(x,y);

		if((*it)->isModal())
		{
			canContinue = false;
		}
	}
	m_surfaceContainerLock--;
	return false;
}

void UICanvas::processTouchMove(int x, int y)
{
	m_surfaceContainerLock++;
	bool canContinue = true;
	for(std::vector<UIWindow*>::reverse_iterator it = m_surfaces.rbegin(); it != m_surfaces.rend() && canContinue; it++){
		(*it)->processTouchMove(x,y);

		if((*it)->isModal())
		{
			canContinue = false;
		}
	}
	m_surfaceContainerLock--;
}


void UICanvas::applyPendingChanges()
{
	if(m_surfaceContainerLock > 0)
		return;

	for(unsigned int i = 0; i < m_pendingChanges.size(); i++)
	{
		switch(m_pendingChanges[i].type)
		{
			case Add:
				m_surfaces.push_back(m_pendingChanges[i].surface);
			break;

			case Remove:
				m_surfaces.erase(std::find(m_surfaces.begin(), m_surfaces.end(), m_pendingChanges[i].surface));
			break;
		}
	}
	m_pendingChanges.clear();
}

NEPHILIM_NS_END