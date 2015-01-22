#ifndef NephilimUIWindow_h__
#define NephilimUIWindow_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Math/Matrix.h>
#include <Nephilim/Math/Ray.h>
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

	These are top of hierarchy objects and they have no parent.
	A window acts as a individual layer with content in a canvas.

	The window can be 3D or fully orthogonal and its possible
	to combine multiple windows in one canvas, to composite
	complex stacks of UI.

	For example, the canvas can have
	[0] Background window (orthogonal, used for some noise clouds moving around)
	[1] Effects window (orthogonal, some particle systems and fancy animations to give mood)
	[2] Content window (3d, the menus and information)
	[3] General controls window (orthogonal, some fancy buttons that we want to be flat)
	[4] Modal window (orthogonal, just a typical widget like a message box here)
*/
class NEPHILIM_API UIWindow : public UIView
{
private:
	/// Coordinate space of the controls in this hierarchy
	UI::CoordinateSpaces mCoordinateSpace = UI::LocalSpace;

public:
	mat4 projectionMatrix = mat4::identity;
	mat4 viewMatrix = mat4::identity;

	bool _3d = false;

	/// The FoV (Field of view) of the camera on this window layer (if its 3d)
	float _fov = 60.f;

	/// The aspect ratio of the screen (width / height)
	float _aspectRatio = 0.8f;

	Vector3D _cameraPosition;
	Vector3D _cameraTarget;

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

	/// Get the mouse ray in the coordinate system of this window
	/// This is extremely helpful to convert window-space mouse coordinates into a 3D picking ray to use on this window
	Ray getMouseRay(int x, int y);

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
