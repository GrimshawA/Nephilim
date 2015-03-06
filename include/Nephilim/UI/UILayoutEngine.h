#ifndef NephilimUI_LayoutEngine_h__
#define NephilimUI_LayoutEngine_h__

#include <Nephilim/Foundation/Object.h>

NEPHILIM_NS_BEGIN

/**
	\class UILayoutEngine
	\brief Native layouting engine for the UI hierarchies

	This layout engine is plugged by default to the UI system
	and it enforces layout on the hierarchy.

	However, it is possible to customize the layout engine to behave differently,
	or just opt out layouting on a given panel.
*/
class NEPHILIM_API UILayoutEngine : public ReferencedObject
{
public:

	/// Destructor
	virtual ~UILayoutEngine();
};

NEPHILIM_NS_END
#endif // NephilimUI_LayoutEngine_h__
