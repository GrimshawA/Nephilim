#ifndef NephilimUI_LineEdit_h__
#define NephilimUI_LineEdit_h__

#include <Nephilim/Platform.h>
#include <Nephilim/UI/Widget.h>
#include <Nephilim/Graphics/Text.h>

NEPHILIM_NS_BEGIN

class NEPHILIM_API UILineEdit : public Widget
{
public:

	String StringBuffer; ///< Current contents of the buffer


	enum UILineEditTypes
	{
		Regular,
		Password
	};

	Text t;
	Color m_textColor;

	int m_pipeIndex;

	UILineEditTypes m_type;

	std::size_t m_charLimit;

public:
	
	/// Constructs the uninitialized line edit (needs a parent to function properly)
	UILineEdit();

	/// Constructs directly into a parent container
	UILineEdit(Widget* ParentView);

	/// Clear the contents
	void clear();

	/// Called on the subclass to have it paint its contents
	virtual void onPaint(UIPainter& painter);

	/// Called when an event arrives at this widget
	virtual void event(UxEvent* event);

	/// Called to handle a key press event
	virtual void keyPressEvent(UxKeyEvent* key);


	bool isFocusable(){return true;}
	virtual bool onKeyPressed(Keyboard::Key key);
	virtual bool onTextEvent(Uint32 code);

	void addCharacter(Uint32 charCode);
	void eraseCharacter();

	void setText(const String& text);

	void setTextColor(const Color& color);	

	void setType(UILineEditTypes type);

	void setCharacterLimit(std::size_t limit);
};

NEPHILIM_NS_END
#endif // NephilimUI_LineEdit_h__
