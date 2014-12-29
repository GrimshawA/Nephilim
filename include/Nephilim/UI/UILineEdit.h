#ifndef UILineEdit_h__
#define UILineEdit_h__

#include <Nephilim/Platform.h>
#include <Nephilim/UI/UIView.h>
#include <Nephilim/Graphics/Text.h>

NEPHILIM_NS_BEGIN

class NEPHILIM_API UILineEdit : public UIView
{
public:
	UILineEdit();

	bool onEventNotification(Event& event);

	bool isFocusable(){return true;}
	virtual bool onKeyPressed(Keyboard::Key key);
	virtual bool onTextEvent(Uint32 code);

	void addCharacter(Uint32 charCode);
	void eraseCharacter();

	void setText(const String& text);

	void setTextColor(const Color& color);

	enum UILineEditTypes
	{
		Regular,
		Password
	};

	void setType(UILineEditTypes type);

	void setCharacterLimit(std::size_t limit);

	void draw(GraphicsDevice* renderer);

	Text t;
	String s;
	Color m_textColor;

	int m_pipeIndex;

	UILineEditTypes m_type;

	std::size_t m_charLimit;
};

class ASEngine;
bool registerUILineEdit(ASEngine* engine);

NEPHILIM_NS_END
#endif // UILineEdit_h__
