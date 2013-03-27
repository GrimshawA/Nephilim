#ifndef UIProgressBar_h__
#define UIProgressBar_h__

#include "Platform.h"
#include "UIControl.h"
#include "Strings.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup UserInterface
	\class UIProgressBar
	\brief A simple progress bar control
*/
class UIProgressBar : public UIControl{
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


PARABOLA_NAMESPACE_END
#endif // UIProgressBar_h__
