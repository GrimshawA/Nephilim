#ifndef NephilimUIController_h__
#define NephilimUIController_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

class UIView;

/**
	\class UIController
	\brief For managing a view in a MVC pattern

	Model view controller patterns are quite effective for programming
	user interfaces.

	The model works as the data source that populates the view with content,
	while the controller maintains the logic for that view. This way, a plug
	and play design is kept, while increasing modularity and code reusability.

	The approach is not enforced though, there are multiple ways to work with the UI systems.
*/
class NEPHILIM_API UIController
{
public:

	/// The view we are linked to and we control directly
	UIView* _view = nullptr;
};

NEPHILIM_NS_END
#endif // NephilimUIController_h__
