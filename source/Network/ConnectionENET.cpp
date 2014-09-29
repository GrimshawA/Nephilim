#include <Nephilim/Network/ConnectionENET.h>
#include <Nephilim/Packet.h>
#include <Nephilim/Logger.h>

#include <stdio.h>

NEPHILIM_NS_BEGIN

void ConnectionENET::send(const Packet& pck)
{
	if (peer)
	{
		ENetPacket* pack_data = enet_packet_create(pck.getData(), pck.getDataSize(), ENET_PACKET_FLAG_RELIABLE);

		if(enet_peer_send(peer, 0, pack_data) > 0)
			Log("Sent data!!");
	}
}

void ConnectionENET::connect(const String& address, int port)
{
	host = enet_host_create(NULL, 1, 2, 0, 0);
	if (host)
	{
		ENetAddress addr_struct;
		enet_address_set_host(&addr_struct, address.c_str());
		addr_struct.port = port;

		peer = enet_host_connect(host, &addr_struct, 2, 0);

		ENetEvent event;
		if (enet_host_service(host, &event, 20) > 0)
		{
			if (event.type == ENET_EVENT_TYPE_CONNECT)
			{
				Log("Connected!!");
			}
		}
		else
		{
			Log("Not connected");
		}
	}
}

void ConnectionENET::update()
{
	if (host)
	{
		ENetEvent event;

		if (enet_host_service(host, &event, 2) > 0)
		{
			if (event.type == ENET_EVENT_TYPE_CONNECT)
			{
				Log("Connected!!");
				peer = event.peer;
			}
			else if (event.type == ENET_EVENT_TYPE_RECEIVE)
			{
				String pck;
				Packet p;
				p.append(event.packet->data, event.packet->dataLength);
	
				p >> pck;

				Log("incoming data: %s", pck.c_str());
			}
		}
	}
}


NEPHILIM_NS_END