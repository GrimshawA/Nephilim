#include <Nephilim/UI/UIWindow.h>
#include <Nephilim/UI/UICanvas.h>
#include <Nephilim/Graphics/GraphicsDevice.h>
#include <Nephilim/Foundation/Logging.h>

NEPHILIM_NS_BEGIN

UIWindow::UIWindow()
: UIView()
, m_modal(false)
, m_parentDocument(NULL)
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
	

	for(std::vector<UIView*>::const_iterator it = m_children.begin(); it != m_children.end(); it++){
		(*it)->drawItself(graphicsDevice);
	}
};

/// Get the parent document of the surface
UICanvas* UIWindow::getParentDocument()
{
	return m_parentDocument;
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