#ifndef NephilimUI_ViewController_h__
#define NephilimUI_ViewController_h__

#include <Nephilim/UI/UIController.h>

NEPHILIM_NS_BEGIN

/**
	\class UIViewController
	\brief Base class for view controllers

	UIViewController subclasses are exact matches to C# controllers
	bound to widget hierarchies.

	An hard rule of UIViewController is that is follows the lifetime
	of its root level controlled UIView, and vice versa.
	Whenever the controller class deallocates, its widget dies
	and when the widget is killed, its controller goes away too.
*/	
class NEPHILIM_API UIViewController : public UIController
{
public:

	/// The view we are controlling
	Widget* RootView = nullptr;

public:

	/// The view controller is built from a root view and attached to it immediately
	UIViewController(Widget* rootView);

	/// Ensure the controlled view is destroyed along
	virtual ~UIViewController();
};

NEPHILIM_NS_END
#endif // NephilimUI_ViewController_h__
