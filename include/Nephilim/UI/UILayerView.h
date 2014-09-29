#ifndef NephilimUILayerView_h__
#define NephilimUILayerView_h__

#include <Nephilim/Platform.h>
#include "UIView.h"

NEPHILIM_NS_BEGIN

class GraphicsDevice;
class UICanvas;

/**
	\ingroup UI
	\class UILayerView
	\brief Parent container for UIView controls

	Note: In a proper hierarchy, only UISurface objects will have a NULL parent
*/
class NEPHILIM_API UILayerView : public UIView
{
public:
	/// Construct the surface
	UILayerView();

	/// Destroy the surface
	void destroy();

	/// Draw the surface
	virtual void draw(GraphicsDevice* renderer);

	/// Callback when a child of the control is removed
	virtual void onChildRemoved(UIView* control);

	/// Check if the surface is modal
	bool isModal();

	/// When a surface is modal it will stop propagation of events to lower surfaces
	/// Also, when the last control in the surface is destroyed, the surface is destroyed automatically.
	void setModal(bool enable);

	/// Get the parent document of the surface
	UICanvas* getParentDocument();

private:
	friend class UICanvas;

	/// Is the surface modal or not?
	bool m_modal;

	UICanvas* m_parentDocument;
};

NEPHILIM_NS_END
#endif // NephilimUILayerView_h__
