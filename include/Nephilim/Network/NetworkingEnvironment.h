#ifndef NephilimNetworkingEnvironment_h__
#define NephilimNetworkingEnvironment_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/FeatureProvider.h>

NEPHILIM_NS_BEGIN

/**
	\class NetworkingEnvironment
	\brief Base class for managing classes of networking systems

	Each specialization of a networking environment defines a 
	way to transfer data with remote hosts. How that is done is entirely
	defined by the implementation so it can be any kind of transport protocol.

	Creating a game protocol is out of the scope of this class
*/
class NEPHILIM_API NetworkingEnvironment : public FeatureProvider
{
public:

public:
	/// Prepare the networking stuff
	NetworkingEnvironment();

	/// Ensure everything gets destructed
	virtual ~NetworkingEnvironment();
};

NEPHILIM_NS_END
#endif // NephilimNetworkingEnvironment_h__
