#ifndef UISlider_h__
#define UISlider_h__

#include <Nephilim/Platform.h>
#include "UIView.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup UserInterface
	\class UISlider
	\brief A common horizontal slider control.
*/
class NEPHILIM_API UISlider : public UIView{
public:
	/// Constructs the slider with default values
	UISlider();

	/// Sets the value of the slider knob
	void setValue(int value);

	/// Callback to render itself
	virtual void draw(GraphicsDevice* renderer);

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

NEPHILIM_NS_END
#endif // UISlider_h__
