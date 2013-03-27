#ifndef UISlider_h__
#define UISlider_h__

#include "Platform.h"
#include "UIControl.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup UserInterface
	\class UISlider
	\brief A common horizontal slider control.
*/
class PARABOLA_API UISlider : public UIControl{
public:
	/// Constructs the slider with default values
	UISlider();

	/// Sets the value of the slider knob
	void setValue(int value);

	/// Callback to render itself
	virtual void draw(Renderer* renderer);

	/// Callback to handle an event
	bool onEventNotification(Event& event);

	/// Callback when the position of the control changed, for updating nested objects
	virtual void onPositionChanged();

private:

	/// Adjust the internal positions of objects according to bounds
	void adjustPositions();

	Rect<float> m_draggableArea;
	Rect<float> m_sliderRect;

	int m_maxValue;

	bool dragging;
};

PARABOLA_NAMESPACE_END
#endif // UISlider_h__
