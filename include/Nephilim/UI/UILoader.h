#ifndef NephilimUILoader_h__
#define NephilimUILoader_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>

NEPHILIM_NS_BEGIN

class UIView;

/**
	\class UILoader
	\brief Interface for UI loaders. Each loader implements its own serialization of UI layouts and settings to files
*/
class NEPHILIM_API UILoader
{
public:
	virtual bool loadFromFile(const String& filename, UIView* root_view)
	{
		return false;
	}
};


NEPHILIM_NS_END
#endif // NephilimUILoader_h__
