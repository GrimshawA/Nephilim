#ifndef UIButton_h__
#define UIButton_h__

#include "Platform.h"
#include "UIControl.h"
#include "Strings.h"

PARABOLA_NAMESPACE_BEGIN

class ASSlot;
/**
	\ingroup UserInterface
	\class UIButton
	\brief A simple button control
*/
class PARABOLA_API UIButton : public UIControl{
public:
	/// Constructs the button
	UIButton();

	/// Constructs the button from a label text
	UIButton(const String& title);

	~UIButton();


	/// Sets the label of the button
	void setLabel(const String& text);

	void bindSignal(const String &signalName, ASSlot* slot );

	/// Callback to handle an event
	bool onEventNotification(Event& event);

	void innerLanguageSwitch();

	template<typename T>
	void setProperty(const String& propertyName, const T& propertyValue);

	/// Callback to render itself, renders children
	virtual void draw(Renderer* renderer);

	virtual UIControl* clone();

	/// Signal is emitted when the button is clicked
	
	void setRawProperty(const String& name, const String& val);

	bool hover;

	Color m_color;

private:
	String m_label;
	String m_baseLabel;
};

template<typename T>
void UIButton::setProperty(const String& propertyName, const T& propertyValue)
{
	// Give precedence to parent
	UIControl::setProperty<T>(propertyName, propertyValue);

	if(propertyName == "color")
	{
		m_color = propertyValue;
	}
}

class ASEngine;
bool registerUIButton(ASEngine* engine);

PARABOLA_NAMESPACE_END
#endif // UIButton_h__
