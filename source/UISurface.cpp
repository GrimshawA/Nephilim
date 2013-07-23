#include <Nephilim/UISurface.h>
#include <Nephilim/UIDocument.h>
#include <Nephilim/Renderer.h>
#include <Nephilim/Logger.h>

NEPHILIM_NS_BEGIN

UISurface::UISurface()
: UIControl()
, m_modal(false)
, m_parentDocument(NULL)
{

}

void UISurface::destroy()
{
	if(getParentDocument())
	{
		getParentDocument()->destroySurface(this);
	}
}

void UISurface::draw(Renderer* renderer)
{
	for(std::vector<UIControl*>::const_iterator it = m_children.begin(); it != m_children.end(); it++){
		(*it)->innerDraw(renderer);
	}
};

/// Get the parent document of the surface
UIDocument* UISurface::getParentDocument()
{
	return m_parentDocument;
}

/// Callback when a child of the control is removed
void UISurface::onChildRemoved(UIControl* control)
{
	Log("Surface detected child removal %d %d %s", m_children.size(), m_modal, m_name.c_str());

	if(m_children.empty() && m_modal)
	{
		Log("Destroying surface");
		destroy();
	}
}

/// Check if the surface is modal
bool UISurface::isModal()
{
	return m_modal;
}

/// When a surface is modal it will stop propagation of events to lower surfaces
/// Also, when the last control in the surface is destroyed, the surface is destroyed automatically.
void UISurface::setModal(bool enable)
{
	m_modal = enable;
}

NEPHILIM_NS_END