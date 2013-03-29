#include <Nephilim/UISurface.h>

NEPHILIM_NS_BEGIN

/// Construct the surface
UISurface::UISurface() :
	UIControl(),
	m_modal(false)
{

};

void UISurface::draw(Renderer* renderer){
	for(std::vector<UIControl*>::const_iterator it = m_children.begin(); it != m_children.end(); it++){
		(*it)->innerDraw(renderer);
	}
};

/// Returns a control in the hierarchy with the name, or NULL if not found - TODO: recursive iterative
UIControl* UISurface::getControlByName(const String& name){
	UIControl* control = NULL;
	for(std::vector<UIControl*>::const_iterator it = m_children.begin(); it != m_children.end(); it++){
		if((*it)->getName() == name) return (*it); // the surface returned something
	}

	return NULL; // Nothing found.
};

/// Callback to handle an event
bool UISurface::onEventNotification(Event& event){
	for(std::vector<UIControl*>::const_iterator it = m_children.begin(); it != m_children.end(); it++){
		(*it)->onEventNotification(event);
	}

	return true;
};

/// Set the unique name of this surface
void UISurface::setName(const String& name){
	m_name = name;
};

/// Get the unique name of this surface
String UISurface::getName(){
	return m_name;
};

NEPHILIM_NS_END