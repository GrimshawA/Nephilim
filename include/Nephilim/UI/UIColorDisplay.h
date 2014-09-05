#ifndef UIColorDisplay_h__
#define UIColorDisplay_h__

#include "Platform.h"
#include "UIView.h"
#include "Color.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup UserInterface
	\class UIColorDisplay
	\brief .
*/
class NEPHILIM_API UIColorDisplay : public UIView{
public:


	/// Set the color displayed in the control
	void setColor(Color color);

private:
	/// The color of this control
	Color m_color;
};

NEPHILIM_NS_END
#endif // UIColorDisplay_h__
