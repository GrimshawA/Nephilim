#include <Nephilim/UI/UIViewController.h>
#include <Nephilim/UI/Widget.h>

NEPHILIM_NS_BEGIN

/// The view controller is built from a root view and attached to it immediately
UIViewController::UIViewController(Widget* rootView)
{
	rootView->addController(this);
}

/// Ensure the controlled view is destroyed along
UIViewController::~UIViewController()
{
	if (RootView)
	{
		RootView->destroy();
	}
}

NEPHILIM_NS_END