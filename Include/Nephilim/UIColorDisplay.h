#ifndef UIColorDisplay_h__
#define UIColorDisplay_h__

#include "Platform.h"
#include "UIControl.h"
#include "Color.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup UserInterface
	\class UIColorDisplay
	\brief .
*/
class PARABOLA_API UIColorDisplay : public UIControl{
public:


	/// Set the color displayed in the control
	void setColor(Color color);

private:
	/// The color of this control
	Color m_color;
};

PARABOLA_NAMESPACE_END
#endif // UIColorDisplay_h__
