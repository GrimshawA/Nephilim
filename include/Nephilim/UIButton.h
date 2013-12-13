#ifndef NephilimUIButton_h__
#define NephilimUIButton_h__

#include "Platform.h"
#include "UIView.h"
#include "Strings.h"
#include "Text.h"

NEPHILIM_NS_BEGIN

class ASSlot;
/**
	\ingroup UserInterface
	\class UIButton
	\brief A simple button control
*/
class NEPHILIM_API UIButton : public UIView
{
public:
	/// Constructs the button
	UIButton();

	/// Constructs the button from a label text
	UIButton(const String& title);

	~UIButton();
	
	/// Sets the label of the button
	void setLabel(const String& text);

	/// Get the label of the button
	String getLabel();

	void bindSignal(const String &signalName, ASSlot* slot );

	/// Callback to handle an event
	bool onEventNotification(Event& event);

	void setNormalTexture(const String& filename);
	void setHoverTexture(const String& filename);

	void innerLanguageSwitch();

	template<typename T>
	void setProperty(const String& propertyName, const T& propertyValue);

	/// Callback to render itself, renders children
	virtual void draw(Renderer* renderer);

	virtual UIView* clone();

	enum UIButtonState
	{
		Regular,
		Hovered,
		Pressed,
		Selected
	};

	struct TextureInfo
	{
		Texture* texture;
		FloatRect rect;
	};

	std::map<UIButtonState, TextureInfo> stateTextures;

	TextureInfo& getStateTextureInfo(UIButtonState state);

	/// Signal is emitted when the button is clicked
	
	void setRawProperty(const String& name, const String& val);

	bool hover;

	FloatRect normal_texture_rect;
	FloatRect hover_texture_rect;

	Color m_color;

	Texture* m_normalTexture; ///< Either NULL or a valid texture to display

	RectangleShape backgroundShape;
	Text buttonLabel;

private:
	String m_label;
	String m_baseLabel;
};

template<typename T>
void UIButton::setProperty(const String& propertyName, const T& propertyValue)
{
	// Give precedence to parent
	UIView::setProperty<T>(propertyName, propertyValue);

	if(propertyName == "color")
	{
		m_color = propertyValue;
	}
}

class ASEngine;
bool registerUIButton(ASEngine* engine);

NEPHILIM_NS_END
#endif // NephilimUIButton_h__
