#ifndef UIProgressBar_h__
#define UIProgressBar_h__

#include <Nephilim/Platform.h>
#include <Nephilim/UI/UIView.h>
#include <Nephilim/Strings.h>

NEPHILIM_NS_BEGIN

/**
	\ingroup UserInterface
	\class UIProgressBar
	\brief A simple progress bar control
*/
class UIProgressBar : public UIView{
public:
	/// Constructs the progress bar with default values
	UIProgressBar();

	/// Constructs the progress bar with defined values
	UIProgressBar(int maxValue, const String& message);

	/// Callback to render itself
	virtual void draw(Renderer* renderer);

	bool onEventNotification(Event& event);

private:
	/// The current value of the progress bar
	int m_currentValue;

	/// The rect of the progress bar
	Rect<float> m_rect;
};


NEPHILIM_NS_END
#endif // UIProgressBar_h__
