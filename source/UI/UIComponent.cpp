#include <Nephilim/UI/UIComponent.h>

NEPHILIM_NS_BEGIN

/// Called when the component is attached to a view
/// view is guaranteed to be valid until onRelease is called
void UIComponent::onAttach(UIView* view){}

/// Called when the parent view is being destroyed or the component is about to be removed
void UIComponent::onRelease(UIView* view){}

NEPHILIM_NS_END
