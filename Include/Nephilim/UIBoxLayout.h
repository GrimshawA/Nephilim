#ifndef UIBoxLayout_h__
#define UIBoxLayout_h__

#include "Platform.h"
#include "UILayout.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup UserInterface
	\class UIBoxLayout
	\brief A layout controller that organizes controls in a vertical or horizontal line
*/
class PARABOLA_API UIBoxLayout : public UILayout{
public:
	/// Default construction
	/// By default the orientation is set as Vertical and no animation
	UIBoxLayout();

	UIBoxLayout(UILayout::Orientation orientation, bool animated);

	void doLayout(UIControl* parent);

	bool m_animated;
	UILayout::Orientation m_orientation;
};

PARABOLA_NAMESPACE_END
#endif // UIBoxLayout_h__
