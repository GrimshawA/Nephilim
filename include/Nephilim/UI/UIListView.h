#ifndef NephilimUIComponentListView_h__
#define NephilimUIComponentListView_h__

#include <Nephilim/UI/UIView.h>

NEPHILIM_NS_BEGIN

/**
	\class UIListView
	\brief Control that displays a list of items
*/
class NEPHILIM_API UIListView : public UIView
{
public:
	
	void onRender(GraphicsDevice* renderer, UIView* view);
};

NEPHILIM_NS_END
#endif // NephilimUIComponentImage_h__
