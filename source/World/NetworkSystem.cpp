#include <Nephilim/World/NetworkSystem.h>

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
	}
}

void NetworkSystemClient::update(const Time& deltaTime)
{
	pingTimer -= deltaTime.seconds();
	if (pingTimer <= 0.f)
	{
		pingTimer = 1.f;

		Packet p;
		p << "Hi";
		conn.send(p);
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

	//Log("Server is on");
}

NEPHILIM_NS_END