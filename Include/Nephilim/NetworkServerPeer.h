#ifndef PARABOLA_NETWORKSERVERPEER_H
#define PARABOLA_NETWORKSERVERPEER_H

#include "Platform.h"
#include "Strings.h"
#include "Signals.h"
#include "NetworkPacket.h"
#include <enet/enet.h>

//#include <SFML/Network/Packet.hpp>

PARABOLA_NAMESPACE_BEGIN

class NetworkServer;
class NetworkPacket;
/**
	\ingroup Network
	\class NetworkServerPeer
	\brief Represents a client peer, in a NetworkServer

	The NetworkServer class holds references to all
	peers connected to it.
*/
class NetworkServerPeer{
public:
	/// Creates a server peer
	NetworkServerPeer();

	/// Peer initialization, check if the peer connection is authorized
	bool authorized();

	/// Disconnects the client
	void disconnect();

	/// Get the ip from the incoming connection
	String getAddress();

	/// Forces the client to disconnect
	void forceDisconnect();

	/// Sends a String to the peer
	/// If reliable is true, the packet will be delivered safely
	/// Otherwise, it may be lost.
	bool send(const String &message, bool reliable = true);

	/// Sends an SFML Packet to the peer
	/// If reliable is true, the packet will be delivered safely
	/// Otherwise, it may be lost.
	bool send(const Packet &packet, bool reliable = true);

	/// Sends a ENET packet to the peer
	/// If reliable is true, the packet will be delivered safely
	/// Otherwise, it may be lost.
	bool send(ENetPacket &packet);

	/// Sends raw data to the peer
	/// If reliable is true, the packet will be delivered safely
	/// Otherwise, it may be lost.
	bool send(void * data, Uint32 dataSize, bool reliable = true);

	/// Get the user data on this peer
	/// NULL if not defined yet
	void* getUserData();

	/// Sets the user data on this peer
	void setUserData(void* data_ptr);

	/// Called when data is received for this peer
	sigc::signal<void, NetworkPacket*> onDataReceived;


private:
	friend class NetworkServer;
	bool myAuthorized;
	void* myUserData;
	ENetPeer *myPeer;
};

PARABOLA_NAMESPACE_END
#endif