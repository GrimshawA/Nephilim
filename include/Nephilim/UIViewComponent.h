#ifndef NephilimUIViewComponent_h__
#define NephilimUIViewComponent_h__

#include "Platform.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup UI
	\class UIViewComponent
	\brief Base class for all UI components
*/
class NEPHILIM_API UIViewComponent 
{
public:
	Int32 component_id; ///< Identify the type of the component

	virtual void onCreate() = 0;

	enum Type
	{
		ButtonComponent,
		ReloadComponent
	};
};

NEPHILIM_NS_END
#endif // NephilimUIViewComponent_h__
