#include "Nephilim/NetworkServerPeer.h"


NEPHILIM_NS_BEGIN

/// Creates a server peer
NetworkServerPeer::NetworkServerPeer() {
	myAuthorized = true;
	myUserData = NULL;
	myPeer = NULL;
}

/// Peer initialization, check if the peer connection is authorized
bool NetworkServerPeer::authorized(){
	return myAuthorized;
}

/// Get the ip from the incoming connection
String NetworkServerPeer::getAddress(){
	char *buffer = new char[20];
	enet_address_get_host_ip(&myPeer->address, buffer, 20);
	String result = buffer;
	delete[] buffer;
	return result;
};

/// Get the user data on this peer
/// NULL if not defined yet
void* NetworkServerPeer::getUserData(){
	return myUserData;
};

/// Sets the user data on this peer
void NetworkServerPeer::setUserData(void* data_ptr){
	myUserData = data_ptr;
};

/// Disconnects the client
void NetworkServerPeer::disconnect(){
	enet_peer_disconnect(myPeer, 0);
};

/// Forces the client to disconnect
void NetworkServerPeer::forceDisconnect(){
	enet_peer_reset(myPeer);
};

/// Broadcasts a String to all clients connected
/// If reliable is true, the packet will be delivered safely
/// Otherwise, it may be lost.
bool NetworkServerPeer::send(const String &message, bool reliable){
	if(!myPeer) return false;
	ENetPacket* packet;

	if(reliable)
		packet = enet_packet_create(message.c_str(), message.size(), ENET_PACKET_FLAG_RELIABLE);
	/*else
		packet = enet_packet_create(message.c_str(), message.size(), ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);*/

	enet_peer_send(myPeer, 0, packet);
	return true;
};

/// Broadcasts a SFML Packet to all clients connected
/// If reliable is true, the packet will be delivered safely
/// Otherwise, it may be lost.
bool NetworkServerPeer::send(const Packet &packet, bool reliable){
	if(!myPeer) return false;

	ENetPacket* epacket;

	if(reliable)
		epacket = enet_packet_create(packet.getData(), packet.getDataSize(), ENET_PACKET_FLAG_RELIABLE);
	else
		epacket = enet_packet_create(packet.getData(), packet.getDataSize(), ENET_PACKET_FLAG_UNSEQUENCED);

	enet_peer_send(myPeer, 0, epacket);
	return true;
};

/// Broadcasts raw data
/// If reliable is true, the packet will be delivered safely
/// Otherwise, it may be lost.
bool NetworkServerPeer::send(void * data, Uint32 dataSize, bool reliable){
	if(!myPeer) return false;

	ENetPacket* packet;

	if(reliable)
		packet = enet_packet_create(data, dataSize, ENET_PACKET_FLAG_RELIABLE);
	/*else
		packet = enet_packet_create(data, dataSize, ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);*/

	enet_peer_send(myPeer, 0, packet);
	return true;
};

/// Broadcasts a ENET packet to all clients connected
/// If reliable is true, the packet will be delivered safely
/// Otherwise, it may be lost.
bool NetworkServerPeer::send(ENetPacket &packet){
	if(!myPeer) return false;

	enet_peer_send(myPeer, 0, &packet);

	return true;
};

NEPHILIM_NS_END
