#ifndef NephilimUI_Console_h__
#define NephilimUI_Console_h__

#include <Nephilim/UI/UIView.h>

NEPHILIM_NS_BEGIN

class UILineEdit;

/**
	\class UIConsole
	\brief A Console window to input commands
*/
class NEPHILIM_API UIConsole : public UIView
{
public:
	String m_input;

	sigc::signal<void, String> onCommandSubmitted;

	UILineEdit* InputLineEdit;

public:

	bool onEventNotification(Event& event);

	void draw(GraphicsDevice* renderer);
};

NEPHILIM_NS_END
#endif // NephilimUI_Console_h__
