#ifndef NephilimUILabel_h__
#define NephilimUILabel_h__

#include <Nephilim/Platform.h>
#include <Nephilim/UI/UIView.h>
#include <Nephilim/Strings.h>

NEPHILIM_NS_BEGIN

/**
	\ingroup UserInterface
	\class UILabel
	\brief A simple label control
*/
class NEPHILIM_API UILabel : public UIView{
public:
	/// Constructs the button
	UILabel();

	/// Constructs the button from a label text
	UILabel(const String& title);

	/// Set the contents of the label
	void setText(const String& text);

	/// Callback to handle an event
	bool onEventNotification(Event& event);

	/// Callback to render itself, renders children
	virtual void draw(Renderer* renderer);

	/// Signal is emitted when the button is clicked
	sigc::signal<void> onClick;

	bool hover;

	Color m_color;

private:
	String m_label;
};

NEPHILIM_NS_END
#endif // NephilimUILabel_h__
