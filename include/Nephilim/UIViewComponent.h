#ifndef NephilimUIViewComponent_h__
#define NephilimUIViewComponent_h__

#include "Platform.h"
#include "Event.h"
#include "Time.h"

NEPHILIM_NS_BEGIN

class UIView;
class Renderer;

/**
	\ingroup UI
	\class UIViewComponent
	\brief Base class for all UI components
*/
class NEPHILIM_API UIViewComponent 
{
public:
	Int32 component_id; ///< Identify the type of the component

	/// Called when the component is attached to a view
	/// view is guaranteed to be valid until onRelease is called
	virtual void onAttach(UIView* view) = 0;

	/// Called when the parent view is being destroyed or the component is about to be removed
	virtual void onRelease(UIView* view){}

	virtual void onResize(UIView* view){}

	virtual void onEvent(Event event, UIView* view){}

	virtual void onUpdate(const Time& time, UIView* view){}

	virtual void onRender(Renderer* renderer, UIView* view){}

	enum Type
	{
		ButtonComponent,
		ReloadComponent,
		ScrollComponent,
		TextComponent
	};
};

NEPHILIM_NS_END
#endif // NephilimUIViewComponent_h__
