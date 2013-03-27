#ifndef PARABOLA_NETWORKCLIENT_H
#define PARABOLA_NETWORKCLIENT_H

#include "Platform.h"
#include "Strings.h"
#include "NetworkSocket.h"
#include "Signals.h"
#include "NetworkPacket.h"

#include <enet/enet.h>

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Network
	\class NetworkClient
	\brief Represents a socket capable of connecting to a remote server.

	It makes it possible to build a ENET based client,
	that can connect to an ENET based server.

*/
class NetworkClient : public NetworkSocket{
public:
	/// Creates a network client
	NetworkClient();

	/// Creates a network client and registers it
	//NetworkClient(NetworkThread &network);

	/// Safely disconnects the socket
	virtual ~NetworkClient(){
		if(myHost && myPeer){
			enet_peer_disconnect_now(myPeer, 0);
		}
	}

	/// Attempts a connection on a remote server
	/// \param address the hostname or ip to connect to.
	/// \param port the port number for the connection
	/// \param timeout amount of miliseconds to block the thread, waiting for the connection to succeed.
	/// You may select a timeout of 0, it will return true and the program continues, and the update() method
	/// will still be able to make the connection succeed.
	/// \return false only if something went wrong with creating the network socket, disallowing connections.
	bool connect(const String &address, int port, int timeout = 3000);

	/// Attempts to disconnect the connection
	bool disconnect();

	/// Sends a string to the remote server
	/// If reliable is true, the packet will be delivered safely
	/// Otherwise, it may be lost.
	bool send(const String &message, bool reliable = true);

	/// Sends a sfml packet to the remote server
	/// If reliable is true, the packet will be delivered safely
	/// Otherwise, it may be lost.
	bool send(const Packet &packet, bool reliable = true);

	/// Sends a ENET packet to the remote host
	/// If reliable is true, the packet will be delivered safely
	/// Otherwise, it may be lost.
	bool send(ENetPacket &packet);

	/// Sends raw data to the remote server
	/// If reliable is true, the packet will be delivered safely
	/// Otherwise, it may be lost.
	bool send(void * data, Uint32 dataSize, bool reliable = true);

	/// Updates the state of the socket
	void update(Uint32 hangTime);

	////////////////////////////////////////////////////////////////////////// Signals

	/// Fired when the client was accepted by a server
	sigc::signal<void, NetworkClient*> onConnected;
	/// Fired when the client is disconnected from a server
	//sigc::signal<void, NetworkClient*> onDisconnected;
	/// Fired when a packet was received from the server
	sigc::signal<void, NetworkClient*, NetworkPacket*> onDataReceived;

protected:
	/// Handles the events
	void handleEvent(ENetEvent *event);

private:
	ENetHost *myHost;
	ENetPeer *myPeer;
};

PARABOLA_NAMESPACE_END
#endif