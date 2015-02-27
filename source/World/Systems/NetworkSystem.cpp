#include <Nephilim/World/Systems/NetworkSystem.h>
#include <Nephilim/World/World.h>

#include <Nephilim/Foundation/Logging.h>

NEPHILIM_NS_BEGIN

NetworkSystem::NetworkSystem()
{
	Log("NETWORKING STARTING");
}

void NetworkSystem::update(const Time& deltaTime)
{
	//Log("NETWORKING UPDATING");
}

// PROTOTYPES


NetworkSystemClient::NetworkSystemClient()
{
	
}

void NetworkSystemClient::update(const Time& deltaTime)
{
	
}



NetworkSystemServer::NetworkSystemServer()
{
	
}

void NetworkSystemServer::update(const Time& deltaTime)
{
	
}

NEPHILIM_NS_END