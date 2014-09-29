#ifndef ConnectionENET_h__
#define ConnectionENET_h__

#include <Nephilim/Network/Connection.h>

#include <enet/enet.h>

NEPHILIM_NS_BEGIN

class NEPHILIM_API ConnectionENET : public Connection
{
public:
	virtual void send(const Packet& pck);
	virtual void connect(const String& address, int port);
	virtual void update();

	ENetHost* host = nullptr;
	ENetPeer* peer = nullptr;
};

NEPHILIM_NS_END
#endif // ConnectionENET_h__

