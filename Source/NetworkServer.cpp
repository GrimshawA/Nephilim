#include "Nephilim/NetworkServer.h"
#include "Nephilim/NetworkThread.h"

#include <algorithm>
#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

/// Creates a network server
NetworkServer::NetworkServer() : NetworkSocket(){
	myHost = NULL;
	myListeningState = true;
	myClientCount = 0;
	myMaxClientCount = 100;

	enet_initialize();
};

/// Creates a network server and registers it
/*NetworkServer::NetworkServer(NetworkThread &network) : NetworkSocket(network){
	myHost = NULL;
	myListeningState = true;
	myClientCount = 0;
	myMaxClientCount = 100;
};*/

/// Starts listening for connections
bool NetworkServer::start(const String &address, int port){
	ENetAddress Address;
	if(address == "0.0.0.0"){
		Address.host = ENET_HOST_ANY;	
	}
	else{
		enet_address_set_host(&Address,address.c_str());
	}
	
	Address.port = port;

	myHost = enet_host_create(&Address, maximumPeerCount(), 6, 0, 0);
	if(myHost){	
		unblock();
		return true;
	}
	else
		return false;
};

/// Starts listening for connections
/// Listens for connections at the selected port
/// Accepts clients from any network interface \see start(const String&, int)
bool NetworkServer::start(int port){
	ENetAddress Address;
	Address.host = ENET_HOST_ANY;	
	Address.port = port;

	myHost = enet_host_create(&Address, maximumPeerCount(), 6, 0, 0);
	if(myHost){	
		unblock();
		return true;
	}
	else
		return false;
};

/// Get the number of connected clients
int NetworkServer::getPeerCount(){
	return myPeers.size();
};

/// Updates the state of the socket
void NetworkServer::update(Uint32 hangTime){
	if(!myHost)return ;

	ENetEvent ev;
	//Check pending events
	while(enet_host_check_events(myHost, &ev) > 0){
		handleEvent(&ev);
	};
	//Check if there is a new event
	if(enet_host_service(myHost, &ev, hangTime) > 0)
	{
		handleEvent(&ev);
	}
};


/// Sets if the server will accept connections
void NetworkServer::setListening(bool enable){
	myListeningState = enable;
};

/// Broadcasts a String to all clients connected
/// If reliable is true, the packet will be delivered safely
/// Otherwise, it may be lost.
bool NetworkServer::send(const String &message, bool reliable){
	if(!myHost) return false;
	ENetPacket* packet;

	if(reliable)
		packet = enet_packet_create(message.c_str(), message.size(), ENET_PACKET_FLAG_RELIABLE);
	/*else
		packet = enet_packet_create(message.c_str(), message.size(), ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);*/

	enet_host_broadcast(myHost, 0, packet);
	return true;
};

/// Broadcasts a SFML Packet to all clients connected
/// If reliable is true, the packet will be delivered safely
/// Otherwise, it may be lost.
bool NetworkServer::send(const Packet &packet, bool reliable){
	if(!myHost) return false;

	ENetPacket* epacket;

	if(reliable)
		epacket = enet_packet_create(packet.getData(), packet.getDataSize(), ENET_PACKET_FLAG_RELIABLE);
	else
		epacket = enet_packet_create(packet.getData(), packet.getDataSize(), ENET_PACKET_FLAG_UNSEQUENCED);

	enet_host_broadcast(myHost, 0, epacket);
	return true;
};

/// Broadcasts raw data
/// If reliable is true, the packet will be delivered safely
/// Otherwise, it may be lost.
bool NetworkServer::send(void * data, Uint32 dataSize, bool reliable){
	if(!myHost) return false;
	ENetPacket* packet;

	if(reliable)
		packet = enet_packet_create(data, dataSize, ENET_PACKET_FLAG_RELIABLE);
/*	else
		packet = enet_packet_create(data, dataSize, ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);*/

	enet_host_broadcast(myHost, 0, packet);
	return true;
};

/// Broadcasts a ENET packet to all clients connected
/// If reliable is true, the packet will be delivered safely
/// Otherwise, it may be lost.
bool NetworkServer::send(ENetPacket &packet){
	if(!myHost) return false;
	enet_host_broadcast(myHost, 0, &packet);

	return true;
};

/// Handles an event received in the update()
void NetworkServer::handleEvent(ENetEvent *event){
	switch(event->type){
		case ENET_EVENT_TYPE_CONNECT:
			{
				if(myListeningState && myClientCount <= myMaxClientCount){
					// able to accept the connection
					NetworkServerPeer *peer = new NetworkServerPeer();
					peer->myPeer = event->peer; //associate peer
					event->peer->data = peer; //set enet user data
					//cout<<"CLIENT"<<endl;
					onClientConnect.emit(peer);

					if(peer->authorized()){
						myClientCount++;
						myPeers.push_back(peer);
					}
					else{
						enet_peer_reset(event->peer);
						delete peer;
					}				
				}
				else{
					cout<<"[NetworkServer] Client rejected."<<endl;
				}

			}break;
		case ENET_EVENT_TYPE_DISCONNECT:
			{
				if(event->peer->data){
					// its a known peer
					//onClientDisconnect((NetworkServerPeer*)event->peer->data);
					myPeers.erase(std::find(myPeers.begin(), myPeers.end(), (NetworkServerPeer*)event->peer->data ));
					myClientCount --;
				}
				
			}break;
		case ENET_EVENT_TYPE_RECEIVE: 
			{
				if(event->peer->data){
					NetworkPacket pack(event);
					//event->packet->data
					String ss((const char*)event->packet->data, event->packet->dataLength);

					//cout<<"Packet: "<<ss<<endl;
					//// its a known peer
					onDataReceived((NetworkServerPeer*)event->peer->data, &pack);

					((NetworkServerPeer*)event->peer->data)->onDataReceived(&pack);
				}

			}break;
	};
};

NEPHILIM_NS_END