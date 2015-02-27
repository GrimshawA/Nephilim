#ifndef NephilimWorldNetworkSystem_h__
#define NephilimWorldNetworkSystem_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/Systems/System.h>

NEPHILIM_NS_BEGIN

class GameNetwork;

/**
	\class NetworkSystem
	\brief Synchronization of World data

	Base class for every World pluggable System
	that handles networking. One World can have
	multiple NetworkSystems in place for flexibility.

	Each of them can be either a raw built-in network handler,
	but a fully extended or customized one.
*/
class NEPHILIM_API NetworkSystem : public System
{
public:

	/// Its imperative that the NetworkSystem is connected to the high-level GameCore network manager
	GameNetwork* gameNetwork = nullptr;

public:
	
	NetworkSystem();

	virtual void update(const Time& deltaTime);

	NetworkSystem* behavior = nullptr;
};

// Prototypes

class NetworkSystemClient : public NetworkSystem
{
public:


public:


	NetworkSystemClient();

	void update(const Time& deltaTime);
};

class NetworkSystemServer : public NetworkSystem
{
public:


public:
	NetworkSystemServer();

	void update(const Time& deltaTime);
};

NEPHILIM_NS_END
#endif // NephilimWorldNetworkSystem_h__
