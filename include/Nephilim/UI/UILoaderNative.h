#ifndef NephilimUILoaderNativeFormat_h__
#define NephilimUILoaderNativeFormat_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>
#include <Nephilim/UI/UILoader.h>

NEPHILIM_NS_BEGIN

class UIView;

/**
	\class UILoaderNative
	\brief Loads and saves UI from the native data serialization format
*/
class NEPHILIM_API UILoaderNative : public UILoader
{
public:
	virtual bool loadFromFile(const String& filename)
	{
		return true;
	}
};

NEPHILIM_NS_END
#endif // NephilimUILoaderNativeFormat_h__
