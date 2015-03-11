#ifndef NephilimUIComponentListView_h__
#define NephilimUIComponentListView_h__

#include <Nephilim/UI/Widget.h>

NEPHILIM_NS_BEGIN

/**
	\class UIListView
	\brief Control that displays a list of items
*/
class NEPHILIM_API UIListView : public Widget
{
public:
	
	void onRender(GraphicsDevice* renderer, Widget* view);
};

NEPHILIM_NS_END
#endif // NephilimUIComponentImage_h__
