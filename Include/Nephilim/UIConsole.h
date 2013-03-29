#ifndef UIConsole_h__
#define UIConsole_h__

#include "Platform.h"
#include "UIControl.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup UserInterface
	\class UIConsole
	\brief A Console window to input commands
*/
class NEPHILIM_API UIConsole : public UIControl{
public:
	bool onEventNotification(Event& event);
	void draw(Renderer* renderer);

	String m_input;

	sigc::signal<void, String> onCommandSubmitted;
};

NEPHILIM_NS_END
#endif // UIConsole_h__
