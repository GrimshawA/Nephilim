#ifndef UILayout_h__
#define UILayout_h__

#include "Platform.h"

NEPHILIM_NS_BEGIN

class UIView;
/**
	\ingroup UserInterface
	\class UILayout
	\brief 
*/
class NEPHILIM_API UILayout{
public:

	enum Orientation
	{
		Vertical = 0,
		Horizontal
	};

	virtual void doLayout(UIView* parent) = 0;
};

NEPHILIM_NS_END
#endif // UILayout_h__
