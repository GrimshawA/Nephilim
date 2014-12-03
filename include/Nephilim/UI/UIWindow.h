#ifndef NephilimUIWindow_h__
#define NephilimUIWindow_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Matrix.h>
#include <Nephilim/UI/UIView.h>

NEPHILIM_NS_BEGIN

class GraphicsDevice;
class UICanvas;

namespace UI
{
	enum CoordinateSpaces
	{
		WorldSpace,
		LocalSpace
	};
}

/**
	\class UIWindow
	\brief Root element of a UI hierarchy

	UIWindow objects have no root, as they are the top of the hierarchy.
	UICanvas effectively owns N UIWindows inside it, either full screen to always fit or as modal dialogs.
*/
class NEPHILIM_API UIWindow : public UIView
{
private:
	/// Coordinate space of the controls in this hierarchy
	UI::CoordinateSpaces mCoordinateSpace = UI::LocalSpace;

public:
	mat4 projectionMatrix = mat4::identity;
	mat4 viewMatrix = mat4::identity;

public:
	/// Construct the surface
	UIWindow();

	/// Set the coordinate space for this layer
	/// Each layer can have an arbitrary way to render itself, from full 3D to regular 2D
	/// as well as blending with the game world seamlessly. This mode requires the camera matrices to be set correctly.
	/// In world space, the coordinates then match 1:1 with the world entities for convenience.
	void setCoordinateSpace(UI::CoordinateSpaces coordinateSpace);

	/// Destroy the surface
	void destroy();

	/// Draw the surface
	virtual void draw(GraphicsDevice* graphicsDevice);

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
#endif // NephilimUIWindow_h__
