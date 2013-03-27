#ifndef UILayout_h__
#define UILayout_h__

#include "Platform.h"

PARABOLA_NAMESPACE_BEGIN

class UIControl;
/**
	\ingroup UserInterface
	\class UILayout
	\brief 
*/
class PARABOLA_API UILayout{
public:

	enum Orientation
	{
		Vertical = 0,
		Horizontal
	};

	virtual void doLayout(UIControl* parent) = 0;
};

PARABOLA_NAMESPACE_END
#endif // UILayout_h__
