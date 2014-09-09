#ifndef NephilimUISurface_h__
#define NephilimUISurface_h__

#include <Nephilim/Platform.h>
#include "UIControl.h"

NEPHILIM_NS_BEGIN

class Renderer;
class UIDocument;

/**
	\ingroup UserInterface
	\class UISurface
	\brief A layer of controls to be used by a UIWindow

	Note: In a proper hierarchy, only UISurface objects will have a NULL parent
*/
class NEPHILIM_API UISurface : public UIControl
{
public:
	/// Construct the surface
	UISurface();

	/// Destroy the surface
	void destroy();

	/// Draw the surface
	virtual void draw(Renderer* renderer);

	/// Callback when a child of the control is removed
	virtual void onChildRemoved(UIControl* control);

	/// Check if the surface is modal
	bool isModal();

	/// When a surface is modal it will stop propagation of events to lower surfaces
	/// Also, when the last control in the surface is destroyed, the surface is destroyed automatically.
	void setModal(bool enable);

	/// Get the parent document of the surface
	UIDocument* getParentDocument();

private:
	friend class UIDocument;

	/// Is the surface modal or not?
	bool m_modal;

	UIDocument* m_parentDocument;
};

NEPHILIM_NS_END
#endif // NephilimUISurface_h__
