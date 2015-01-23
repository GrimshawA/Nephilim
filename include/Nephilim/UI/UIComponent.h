#ifndef NephilimUIComponent_h__
#define NephilimUIComponent_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Matrix.h>
#include <Nephilim/Foundation/Event.h>
#include <Nephilim/Foundation/Time.h>

NEPHILIM_NS_BEGIN

class UIView;
class GraphicsDevice;
class StringList;
class String;

/**
	\ingroup UI
	\class UIViewComponent
	\brief Base class for all UI components
*/
class NEPHILIM_API UIComponent 
{
public:
	UIComponent()
	{
		mParent = NULL;
	}

	Int32 component_id; ///< Identify the type of the component

	UIView* mParent;

	/// Called when the component is attached to a view
	/// view is guaranteed to be valid until onRelease is called
	virtual void onAttach(UIView* view);

	/// Called when the parent view is being destroyed or the component is about to be removed
	virtual void onRelease(UIView* view);

	/// Called to refresh the component
	virtual void updateStyles(){}

	/// Called on the component when the UIView it is attached to has a new child
	virtual void onChildAttached(UIView* child){};

	virtual void onResize(UIView* view){}

	virtual void onEvent(Event event, UIView* view){}

	virtual void onUpdate(const Time& time, UIView* view){}

	/// Render the component to the screen, giving it its view transform to know where to render
	virtual void onRender(GraphicsDevice* renderer, UIView* view, const mat4& parentTransform){}

	virtual void onPropertySet(const StringList& targetObject, const String& value){}

	enum Type
	{
		ButtonComponent,
		ReloadComponent,
		ScrollComponent,
		TextComponent
	};
};

NEPHILIM_NS_END
#endif // NephilimUIComponent_h__
