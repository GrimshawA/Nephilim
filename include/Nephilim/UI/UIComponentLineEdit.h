#ifndef NephilimUIComponentLineEdit_h__
#define NephilimUIComponentLineEdit_h__

#include <Nephilim/Platform.h>
#include <Nephilim/UIComponent.h>
#include <Nephilim/Text.h>
#include <Nephilim/Signals.h>

NEPHILIM_NS_BEGIN

class NEPHILIM_API UIComponentLineEdit : public UIComponent
{
public:
	UIComponentLineEdit();

	void onEvent(Event event, UIView* view);

	virtual bool onKeyPressed(Keyboard::Key key);
	virtual bool onTextEvent(Uint32 code);

	void addCharacter(Uint32 charCode);
	void eraseCharacter();

	void onRender(Renderer* renderer, UIView* view);

	enum UILineEditTypes
	{
		Regular,
		Password
	};

	void setType(UILineEditTypes type);

	void setCharacterLimit(std::size_t limit);

	Text t;
	String s;
	Color m_textColor;

	int m_pipeIndex;

	UILineEditTypes m_type;

	std::size_t m_charLimit;

	sigc::signal<void, String> onReturnPressed;
};

NEPHILIM_NS_END
#endif // NephilimUIComponentLineEdit_h__
