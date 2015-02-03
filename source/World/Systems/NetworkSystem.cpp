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
	if (conn.connect(IpAddress("127.0.0.1"), 5000, Time::fromSeconds(3.f)) == TcpSocket::Done)
	{
		Log("Connection is established");
		conn.setBlocking(false);
	}
}

void NetworkSystemClient::update(const Time& deltaTime)
{
	Packet pck;
	if (conn.receive(pck) == TcpSocket::Done)
	{
		Uint32 count;
		pck >> count;

		for (int i = 0; i < count; ++i)
		{
			Uint32 UUID;
			Vector3D location;

			pck >> UUID >> location.x >> location.y >> location.z;

			Log("Unpacking actor %d to %f %f %f", UUID, location.x, location.y, location.z);

			Actor* actor = getWorld()->getActorByUUID(UUID);
			if (actor)
			{
				actor->setActorLocation(location);
			}
		}
	}
}



NetworkSystemServer::NetworkSystemServer()
{
	listener.listen(5000);
	listener.setBlocking(false);

	next = new TcpSocket();
}

void NetworkSystemServer::update(const Time& deltaTime)
{
	if (listener.accept(*next) == TcpListener::Done)
	{
		Log("Found our client");
		next->setBlocking(false);
	}

	Packet p;
	if (next->receive(p) == TcpSocket::Done)
	{
		String s;
		p >> s;

		Log("MESSAGE FROM CLIENT: %s", s.c_str());
	}

	// Let's send the actor positions
	static float timeUntil = 0.1f;
	timeUntil -= deltaTime.seconds();
	if (timeUntil <= 0.f)
	{
		Packet pck;
		pck << (Uint32)getWorld()->mPersistentLevel->actors.size();

		for (auto actor : getWorld()->mPersistentLevel->actors)
		{
			Vector3D location = actor->getActorLocation();

			pck << (Uint32)actor->uuid;
			pck << location.x;
			pck << location.y;
			pck << location.z;
		}
		next->send(pck);

		//Log("Just sent all the actor data");
		timeUntil = 0.1f;
	}	

	//Log("Server is on");
}

NEPHILIM_NS_END