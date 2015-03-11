#ifndef NephilimUIDockPanel_h__
#define NephilimUIDockPanel_h__

#include <Nephilim/UI/Widget.h>

NEPHILIM_NS_BEGIN

/**
	\class UIDockPanel
	\brief Layouting widget that orders its children after each other, horizontally or vertically

	This panel does not touch the sizes of the controls, it only keeps them relative to each other
*/
class NEPHILIM_API UIListPanel : public Widget
{
public:

	/// Initial setup
	virtual void onSetup();

	/// Called on the subclass when a new child is added
	virtual void onChildAdded(Widget* widget);

	/// Intercept the events to handle them
	virtual void dispatch(const UxEvent& event);

	void refresh();
};

NEPHILIM_NS_END
#endif // NephilimUIDockPanel_h__