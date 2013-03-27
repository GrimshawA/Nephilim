#ifndef PARABOLA_NETWORKSERVER_H
#define PARABOLA_NETWORKSERVER_H

#include "Platform.h"
#include "NetworkSocket.h"
#include <vector>
#include "Signals.h"
#include "Strings.h"
#include "NetworkServerPeer.h"
#include "NetworkPacket.h"

//#include <SFML/Network/Packet.hpp>

#include <enet/enet.h>

PARABOLA_NAMESPACE_BEGIN

class NetworkThread;

/**
	\ingroup Network
	\class NetworkServer
	\brief Represents a server socket, capable of handling multiple clients.

	Normally, a server will try to insert itself in the owner GameCore socket update list, to be updated automatically.
	The auto-update is made from a exclusive network thread, if allowed.

	Handles the basic features of a game server, like a maximum number of connections.
*/
class NetworkServer : public NetworkSocket{
public:
	/// Creates a network server
	NetworkServer();

	/// Creates a network server and registers it
	//NetworkServer(NetworkThread &network);

	/// Starts listening for connections
	/// \param address will be in which network interface to listen,
	/// could be localhost only, "127.0.0.1"
	/// could be lan only, "192.168.1.30"
	/// could be an external ip, "85.89.45.65"
	/// The special case when address is "0.0.0.0"
	/// the server will listen on any interface.
	/// \param port defines in which port to listen for connections
	bool start(const String &address, int port);

	/// Starts listening for connections
	/// Listens for connections at the selected port
	/// Accepts clients from any network interface \see start(const String&, int)
	bool start(int port);

	/// Updates the state of the socket
	void update(Uint32 hangTime);

	/// Sets if the server will accept connections
	void setListening(bool enable);


	/// Get the number of connected clients
	int getPeerCount();

	/// Broadcasts a String to all clients connected
	/// If reliable is true, the packet will be delivered safely
	/// Otherwise, it may be lost.
	bool send(const String &message, bool reliable = true);

	/// Broadcasts a SFML Packet to all clients connected
	/// If reliable is true, the packet will be delivered safely
	/// Otherwise, it may be lost.
	bool send(const Packet &packet, bool reliable = true);

	/// Broadcasts a ENET packet to all clients connected
	/// If reliable is true, the packet will be delivered safely
	/// Otherwise, it may be lost.
	bool send(ENetPacket &packet);

	/// Broadcasts raw data
	/// If reliable is true, the packet will be delivered safely
	/// Otherwise, it may be lost.
	bool send(void * data, Uint32 dataSize, bool reliable = true);

	////////////////////////////////////////////////////////////////////////// Signals

	/// Fired when a new client attempts to connect
	/// The connected function prototype must be like void f(NetworkServerPeer*)
	/// If a registered callback does not want this client to be accepted,
	/// it can call setAuthorized(false) in the peer.
	sigc::signal<void, NetworkServerPeer*> onClientConnect;

	/// Fired when a client disconnects
	//sigc::signal<void, NetworkServerPeer*> onClientDisconnect;

	/// Fired when data is received from a client
	sigc::signal<void, NetworkServerPeer*, NetworkPacket*> onDataReceived;

protected:
	/// Handles an event received in the update()
	void handleEvent(ENetEvent *event);

private:
	ENetHost *myHost;
	std::vector<NetworkServerPeer*> myPeers;
	int myClientCount;
	int myMaxClientCount;
	bool myListeningState;
};

PARABOLA_NAMESPACE_END
#endif