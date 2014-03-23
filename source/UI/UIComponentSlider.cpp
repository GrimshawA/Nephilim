#ifndef NephilimUIComponentListView_h__
#define NephilimUIComponentListView_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>
#include <Nephilim/UIViewComponent.h>
#include <Nephilim/Text.h>


NEPHILIM_NS_BEGIN

class NEPHILIM_API UIComponentListView : public UIViewComponent
{
public:
	void onAttach(UIView* view);

	void onRender(Renderer* renderer, UIView* view);
};

NEPHILIM_NS_END
#endif // NephilimUIComponentImage_h__
