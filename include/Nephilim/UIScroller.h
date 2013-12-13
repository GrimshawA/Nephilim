#ifndef NephilimUIScroller_h__
#define NephilimUIScroller_h__

#include "Platform.h"
#include "UIView.h"
#include "Vectors.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup UserInterface
	\class UIScroller
	\brief A control that works as a scrollable page
*/
class NEPHILIM_API UIScroller : public UIView
{
public:
	UIScroller();

	bool onEventNotification(Event& event);

	void offsetChildren(vec2 offset);

	bool m_scrollsHorizontally;
	bool m_holdingDown;
	vec2 m_lastPosition;

	float m_lowerLimitV;
	float m_currentOffsetV;

};

NEPHILIM_NS_END

#endif // NephilimUIScroller_h__
