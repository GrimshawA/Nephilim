#ifndef MINIMAL_BUILD

#include "Nephilim/NetworkSocket.h"
#include <enet/enet.h>

NEPHILIM_NS_BEGIN

/// Creates a network socket and registers it in the global thread for auto updating, if you so desire.
NetworkSocket::NetworkSocket(){
	myRegistered = false;
	myBlocked = true;
	myMaximumPeerCount = 400;
	
};

/// Creates a network socket and registers it in the global thread for auto updating, if you so desire.
NetworkSocket::NetworkSocket(NetworkThread &network){

	if(&network != NULL){
		//network.add(this);
		myRegistered = true;
	}
	else{
		myRegistered = false;
	}

	myBlocked = true;
	myMaximumPeerCount = 10;
	
};

/// Safely destroys the socket, while removing it from the global thread.
NetworkSocket::~NetworkSocket(){

};

/// Register the socket
void NetworkSocket::registerSocket(NetworkThread *network){
	if(network != NULL){
		//network->add(this);
		myRegistered = true;
	}
	else{
		myRegistered = false;
	}
};

/// Blocks the socket from receiving or sending anything
void NetworkSocket::block(){
	myBlocked = true;
};

/// Unblocks the socket, making it ready for communication.
void NetworkSocket::unblock(){
	myBlocked = false;
};

/// Checks whether the socket is blocked.
bool NetworkSocket::isBlocked(){
	return myBlocked;
};

/// The maximum number of connections allowed on this socket at any given time
int NetworkSocket::maximumPeerCount(){
	return myMaximumPeerCount;
};

/// The number of communication channels this socket is using
int NetworkSocket::channelCount(){
	return myChannelCount;
};

/// Get the limit of bandwidth for incoming data.
/// Bandwidth limit on bytes per second. 0 means that there is no limit.		
int NetworkSocket::incomingBandwidthLimit(){
	return myIncomingBandwidth;
};

/// Get the limit of bandwidth for outgoing data.
/// Bandwidth limit on bytes per second. 0 means that there is no limit.		
int NetworkSocket::outgoingBandwidthLimit(){
	return myOutgoingBandwidth;
};


/// Set the maximum allowed peer connections for this socket.
/// This value is 10 by default. You cannot change this value while the socket is connected. You must change it before a connection starts.
void NetworkSocket::setMaximumPeerCount(int peer_count){

};


/// Set the number of channels for communication between the socket and its connected peers.
/// By default, there are 2 channels. You should change this value before the socket is working, or the change doesn't happen.
void NetworkSocket::setChannelCount(int channel_count){

};


/// Set the bandwidth limit for incoming data.
/// By default, there is no bandwidth limit, this is equivalent to SetIncomingBandwidthLimit(0).
/// You should change these values while the socket is not working, or it won't have effect.	
void NetworkSocket::setIncomingBandwidthLimit(int bandwidth_limit){

};


/// Set the bandwidth limit for outgoing data.
/// By default, there is no bandwidth limit, this is equivalent to SetOutgoingBandwidthLimit(0).
///	You should change these values while the socket is not working, or it won't have effect.	
void NetworkSocket::setOutgoingBandwidthLimit(int bandwidth_limit){

};


NEPHILIM_NS_END
#endif