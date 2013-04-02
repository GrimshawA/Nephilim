
#ifndef MINIMAL_BUILD

#ifndef PARABOLA_EXCLUDE_NETWORK
#include "Nephilim/NetworkClient.h"
#include "Nephilim/NetworkThread.h"

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN
	
/// Creates a network client
NetworkClient::NetworkClient() : NetworkSocket(){
	myHost = NULL;
	myPeer = NULL;

	enet_initialize();
};

/// Creates a network client and registers it
/*NetworkClient::NetworkClient(NetworkThread &network) : NetworkSocket(network){
	myHost = NULL;
	myPeer = NULL;
};*/
/*
/// Safely disconnects the socket
NetworkClient::~NetworkClient(){
	if(myHost && myPeer){
		enet_peer_disconnect(myPeer, 0);
	}
};*/

/// Starts listening for connections
bool NetworkClient::connect(const String &address, int port, int timeout){
	
	cout<<"Connecting..."<<endl;
	//sf::Lock lockMutex(myMutex);
	myHost = enet_host_create(NULL, 10, 6, 0, 0);

	if(!myHost)
		cout<<"Host creation failed"<<endl;


	ENetAddress Address;
	enet_address_set_host(&Address, address.c_str());
	Address.port = port;

	myPeer = enet_host_connect(myHost, &Address, 2,0);

	if(!myPeer)
		cout<<"Peer couldnt be allocated"<<endl;

	ENetEvent Event;
	int res;
	
	if((res = enet_host_service(myHost, &Event, timeout)) > 0){
		if(Event.type == ENET_EVENT_TYPE_CONNECT){
			//SetWorking(true);
			//Signal_ConnectedToHost.emit();
			//cout<<"A good connect, signal emited"<<endl;
			onConnected(this);
			unblock();
			update(0);
			return true;
		}

		if(Event.type == ENET_EVENT_TYPE_DISCONNECT)
			cout<<"Timed out"<<endl;

		//cout<<"EVENT TYPE: "<<Event.type<<endl<<endl;
	}

	//cout<<"failed to connect, no service"<<endl;
	unblock();
	return false;
};

/// Updates the state of the socket
void NetworkClient::update(Uint32 hangTime){
	if(!myHost)return;

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

/// Broadcasts a String to all clients connected
/// If reliable is true, the packet will be delivered safely
/// Otherwise, it may be lost.
bool NetworkClient::send(const String &message, bool reliable){
	if(!myPeer) return false;
	ENetPacket* packet;

	if(reliable)
		packet = enet_packet_create(message.c_str(), message.size(), ENET_PACKET_FLAG_RELIABLE);
	else
		packet = enet_packet_create(message.c_str(), message.size(), ENET_PACKET_FLAG_UNSEQUENCED);

	enet_peer_send(myPeer, 0, packet);
	return true;
};

/// Broadcasts a SFML Packet to all clients connected
/// If reliable is true, the packet will be delivered safely
/// Otherwise, it may be lost.
bool NetworkClient::send(const Packet &packet, bool reliable){
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
bool NetworkClient::send(void * data, Uint32 dataSize, bool reliable){
	if(!myPeer) return false;

	ENetPacket* packet;

	if(reliable)
		packet = enet_packet_create(data, dataSize, ENET_PACKET_FLAG_RELIABLE);
	else
		packet = enet_packet_create(data, dataSize, ENET_PACKET_FLAG_UNSEQUENCED);

	enet_peer_send(myPeer, 0, packet);
	return true;
};

/// Broadcasts a ENET packet to all clients connected
/// If reliable is true, the packet will be delivered safely
/// Otherwise, it may be lost.
bool NetworkClient::send(ENetPacket &packet){
	if(!myPeer) return false;

	enet_peer_send(myPeer, 0, &packet);

	return true;
};

/// Handles the events
void NetworkClient::handleEvent(ENetEvent *event){
	switch(event->type){
	case ENET_EVENT_TYPE_CONNECT:
		{
			onConnected(this);

		}break;
	case ENET_EVENT_TYPE_DISCONNECT:
		{		
			// its a known peer
			//onDisconnected(this);			

		}break;
	case ENET_EVENT_TYPE_RECEIVE: 
		{			
			NetworkPacket readPacket(event);

			onDataReceived(this, &readPacket);

			// its a known peer
			//	onDataReceived((NetworkServerPeer*)event->peer->data);
			//cout<<"Got: "<<String((char*)event->packet->data, event->packet->dataLength)<<endl;			

		}break;
	};
};

NEPHILIM_NS_END
#endif
#endif