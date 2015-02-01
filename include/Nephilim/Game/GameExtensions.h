#ifndef NephilimGameExtensions_h__
#define NephilimGameExtensions_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Extensions/ExtensionManager.h>

#include <vector>

NEPHILIM_NS_BEGIN

/**
	\class GameExtensions
	\brief Part of the game that deals with engine extensions
*/
class NEPHILIM_API GameExtensions
{
public:

	/// Our extension manager
	ExtensionManager extensions;
};

NEPHILIM_NS_END
#endif //NephilimGameExtensions_h__