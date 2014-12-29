#ifndef NephilimUIComponentListView_h__
#define NephilimUIComponentListView_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>
#include <Nephilim/UI/UIComponent.h>
#include <Nephilim/Graphics/Text.h>


NEPHILIM_NS_BEGIN

class NEPHILIM_API UIComponentListView : public UIComponent
{
public:
	void onAttach(UIView* view);

	void onRender(GraphicsDevice* renderer, UIView* view);
};

NEPHILIM_NS_END
#endif // NephilimUIComponentImage_h__
