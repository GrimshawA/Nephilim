#include <Nephilim/UI/UIWindow.h>
#include <Nephilim/UI/UICanvas.h>
#include <Nephilim/Graphics/GraphicsDevice.h>
#include <Nephilim/Foundation/Logging.h>
#include <Nephilim/World/Camera.h>

NEPHILIM_NS_BEGIN

UIWindow::UIWindow()
: UIView()
, m_modal(false)
, m_parentDocument(NULL)
, mCoordinateSpace(UI::LocalSpace)
, _3d(false)
{

}

void UIWindow::setCoordinateSpace(UI::CoordinateSpaces coordinateSpace)
{
	mCoordinateSpace = coordinateSpace;
}

void UIWindow::destroy()
{
	if(getParentDocument())
	{
		getParentDocument()->destroySurface(this);
	}
}

void UIWindow::draw(GraphicsDevice* graphicsDevice)
{
	if (mCoordinateSpace == UI::WorldSpace)
	{
		// Set camera matrices
		graphicsDevice->setProjectionMatrix(projectionMatrix);
		graphicsDevice->setViewMatrix(viewMatrix);
	}
	
	// If this is a 3D layer, we need to set a proper camera for it
	if (_3d)
	{
		graphicsDevice->setProjectionMatrix(mat4::perspective(_fov, _aspectRatio, 1.f, 5000.f));
		graphicsDevice->setViewMatrix(mat4::lookAt(_cameraPosition, _cameraTarget, Vector3D(0.f, -1.f, 0.f)));
	}
	else
	{
		graphicsDevice->setProjectionMatrix(mat4::ortho(0.f, width(), height(), 0.f, 1.f, 1000.f));
		graphicsDevice->setViewMatrix(mat4::identity);
	}

	for(std::vector<UIView*>::const_iterator it = m_children.begin(); it != m_children.end(); it++)
	{
		(*it)->drawItself(graphicsDevice);
	}
};

/// Get the parent document of the surface
UICanvas* UIWindow::getParentDocument()
{
	return m_parentDocument;
}

/// Get the mouse ray in the coordinate system of this window
/// This is extremely helpful to convert window-space mouse coordinates into a 3D picking ray to use on this window
Ray UIWindow::getMouseRay(int x, int y)
{
	Ray r; r.origin.x = 0;
//	CCameraLens::
	return r;
}

/// Callback when a child of the control is removed
void UIWindow::onChildRemoved(UIView* control)
{
	Log("Surface detected child removal %d %d %s", m_children.size(), m_modal, m_name.c_str());

	if(m_children.empty() && m_modal)
	{
		Log("Destroying surface");
		destroy();
	}
}

/// Check if the surface is modal
bool UIWindow::isModal()
{
	return m_modal;
}

/// When a surface is modal it will stop propagation of events to lower surfaces
/// Also, when the last control in the surface is destroyed, the surface is destroyed automatically.
void UIWindow::setModal(bool enable)
{
	m_modal = enable;
}

NEPHILIM_NS_END