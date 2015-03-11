#ifndef NephilimUI_Button_h__
#define NephilimUI_Button_h__

#include <Nephilim/UI/Widget.h>

#include <Nephilim/Graphics/Text.h>

NEPHILIM_NS_BEGIN

/**
	\class UIButton
	\brief A simple button control
*/
class NEPHILIM_API UIButton : public Widget
{
public:
	/// Constructs the button
	UIButton();

	/// Constructs the button from a label text
	UIButton(const String& title);

	/// Constructs a button with a given text directly at a given position
	UIButton(const String& content, const FloatRect& rect);

	~UIButton();
	
	/// Sets the label of the button
	void setLabel(const String& text);

	/// Get the label of the button
	String getLabel();

	void setNormalTexture(const String& filename);
	void setHoverTexture(const String& filename);


	/// Called on the subclass to have it paint its contents
	virtual void onPaint(UIPainter& painter);

	enum UIButtonState
	{
		Regular,
		Hovered,
		Pressed,
		Selected
	};

	struct TextureInfo
	{
		Texture2D* texture;
		FloatRect rect;
	}; 

	std::map<UIButtonState, TextureInfo> stateTextures;

	TextureInfo& getStateTextureInfo(UIButtonState state);

	FloatRect normal_texture_rect;
	FloatRect hover_texture_rect;

	Color m_color;

	Texture2D* m_normalTexture; ///< Either NULL or a valid texture to display

	RectangleShape backgroundShape;
	Text buttonLabel;

private:
	String m_label;
	String m_baseLabel;
};

REGISTER_FACTORY_TYPENAME(UIButton);

NEPHILIM_NS_END
#endif // NephilimUI_Button_h__
