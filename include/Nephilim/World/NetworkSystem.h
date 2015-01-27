#ifndef NephilimWorldNetworkSystem_h__
#define NephilimWorldNetworkSystem_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/System.h>

// Prototypes
#include <Nephilim/Network/TcpListener.h>
#include <Nephilim/Network/TcpSocket.h>
#include <Nephilim/Network/IpAddress.h>
#include <Nephilim/Network/Packet.h>

NEPHILIM_NS_BEGIN

/**
	\class NetworkSystem
	\brief Synchronization of the world with remote peers

	This network system is always instanced in the world by default,
	you can add blocks of behavior to it to match your needs, or use
	premade ones that will do proper server/client sync.
*/
class NEPHILIM_API NetworkSystem : public System
{
public:
	
	NetworkSystem();

	virtual void update(const Time& deltaTime);

	NetworkSystem* behavior = nullptr;
};

// Prototypes

class NetworkSystemClient : public NetworkSystem
{
public:

	TcpSocket conn;
	float pingTimer = 1.f;

public:


	NetworkSystemClient();

	void update(const Time& deltaTime);
};

class NetworkSystemServer : public NetworkSystem
{
public:

	TcpListener listener;

	TcpSocket* next = nullptr;

public:
	NetworkSystemServer();

	void update(const Time& deltaTime);
};

NEPHILIM_NS_END
#endif // NephilimWorldNetworkSystem_h__
