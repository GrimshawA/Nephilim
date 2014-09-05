#ifndef UISoftwareKeyboard_h__
#define UISoftwareKeyboard_h__

#include "Platform.h"
#include "UIView.h"
#include "Strings.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup UserInterface
	\class UISoftwareKeyboard
	\brief A simple software keyboard
*/
class NEPHILIM_API UISoftwareKeyboard : public UIView{
public:
	/// Constructs the button
	UISoftwareKeyboard();

	/// Constructs the button from a label text
	UISoftwareKeyboard(const String& title);

	/// Callback to handle an event
	bool onEventNotification(Event& event);

	/// Callback to render itself, renders children
	virtual void draw(Renderer* renderer);

	void emitErase();

	/// Signal is emitted when the button is clicked
	sigc::signal<void> onClick;

	sigc::signal<void, Uint32> onTextEntered;
	sigc::signal<void> onErase;

	bool hover;

	Color m_color;

private:
	String m_label;
};


NEPHILIM_NS_END
#endif // UISoftwareKeyboard_h__
