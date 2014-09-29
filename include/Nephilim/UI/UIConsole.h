#ifndef UIConsole_h__
#define UIConsole_h__

#include <Nephilim/Platform.h>
#include "UIView.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup UserInterface
	\class UIConsole
	\brief A Console window to input commands
*/
class NEPHILIM_API UIConsole : public UIView{
public:
	bool onEventNotification(Event& event);
	void draw(GraphicsDevice* renderer);

	String m_input;

	sigc::signal<void, String> onCommandSubmitted;
};

NEPHILIM_NS_END
#endif // UIConsole_h__
