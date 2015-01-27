#ifndef NephilimFoundationProvider_h__
#define NephilimFoundationProvider_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>

#include <vector>

NEPHILIM_NS_BEGIN

/**
	\class FeatureProvider
	\brief Interface for implementing different services to the engine

	Basically, providers are self-contained services that enable a feature in the engine.
	This is mainly used by plugins to implement multiple kinds of things from scripting to
	audio, networking, physics etc. 

	All kinds of things that aren't a core part of the engine are plugged in through providers.
	For example, we may instance in our game a provider implementation directly and it will work just fine,
	but usually we will get them by bringing in a plugin into the project, and as it loads, a single root provider
	is instanced per plugin.

	This helps provide a base class for every feature implementation, so whether the plugin implements a physics system,
	a rendering library, a networking solution or whatever, we always know it generates a Provider.
*/
class NEPHILIM_API FeatureProvider
{
public:

};

NEPHILIM_NS_END
#endif // NephilimFoundationProvider_h__