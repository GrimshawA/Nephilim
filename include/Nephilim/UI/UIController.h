#ifndef NephilimUIComponent_h__
#define NephilimUIComponent_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Matrix.h>
#include <Nephilim/Foundation/Event.h>
#include <Nephilim/Foundation/Time.h>

NEPHILIM_NS_BEGIN

class Widget;
class GraphicsDevice;
class StringList;
class String;

/**
	\class UIController
	\brief Controllers allow to give dynamic behaviors to views
*/
class NEPHILIM_API UIController 
{
public:
	UIController()
	{
		mParent = NULL;
	}

	Int32 component_id; ///< Identify the type of the component

	Widget* mParent;

	/// Called when the component is attached to a view
	/// view is guaranteed to be valid until onRelease is called
	virtual void onAttach(Widget* view);

	/// Called when the parent view is being destroyed or the component is about to be removed
	virtual void onRelease(Widget* view);

	/// Called to refresh the component
	virtual void updateStyles(){}

	/// Called on the component when the UIView it is attached to has a new child
	virtual void onChildAttached(Widget* child){};

	virtual void onResize(Widget* view){}

	virtual void onEvent(Event event, Widget* view){}

	virtual void onUpdate(const Time& time, Widget* view){}

	/// Render the component to the screen, giving it its view transform to know where to render
	virtual void onRender(GraphicsDevice* renderer, Widget* view, const mat4& parentTransform){}

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
