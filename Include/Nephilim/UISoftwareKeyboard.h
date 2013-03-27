#ifndef UISoftwareKeyboard_h__
#define UISoftwareKeyboard_h__

#include "Platform.h"
#include "UIControl.h"
#include "Strings.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup UserInterface
	\class UISoftwareKeyboard
	\brief A simple software keyboard
*/
class PARABOLA_API UISoftwareKeyboard : public UIControl{
public:
	/// Constructs the button
	UISoftwareKeyboard();

	/// Constructs the button from a label text
	UISoftwareKeyboard(const String& title);

	/// Callback to handle an event
	bool onEventNotification(Event& event);

	template<typename T>
	void setProperty(const String& propertyName, const T& propertyValue);

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

template<typename T>
void UISoftwareKeyboard::setProperty(const String& propertyName, const T& propertyValue)
{
	// Give precedence to parent
	UIControl::setProperty<T>(propertyName, propertyValue);

	if(propertyName == "color")
	{
		m_color = propertyValue;
	}
}


PARABOLA_NAMESPACE_END
#endif // UISoftwareKeyboard_h__
