#ifndef UISurface_h__
#define UISurface_h__

#include "Platform.h"
#include "Renderer.h"

#include "UIControl.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup UserInterface
	\class UISurface
	\brief A layer of controls to be used by a UIWindow

	Note: In a proper hierarchy, only UISurface objects will have a NULL parent
*/
class PARABOLA_API UISurface : public UIControl{
public:
	/// Construct the surface
	UISurface();

	/// Returns a control in the hierarchy with the name, or NULL if not found
	UIControl* getControlByName(const String& name);

	/// Callback to handle an event
	bool onEventNotification(Event& event);

	virtual void draw(Renderer* renderer);

	/// Set the unique name of this surface
	void setName(const String& name);

	/// Get the unique name of this surface
	String getName();

private:
	/// The unique name of this surface
	String m_name;

	/// Is the surface modal or not?
	bool m_modal;
};

PARABOLA_NAMESPACE_END
#endif // UISurface_h__
