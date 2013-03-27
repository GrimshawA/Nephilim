#ifndef PARABOLA_NETWORKSOCKET_H
#define PARABOLA_NETWORKSOCKET_H

#include "Platform.h"
//#include <SFML/System/Mutex.hpp>
//
PARABOLA_NAMESPACE_BEGIN

class NetworkThread;
/**
		\ingroup Network
		\class NetworkSocket
		\brief Base class of a network socket - client or server
 
		\see NetworkClient
		and
		\see NetworkServer
*/
class PARABOLA_API NetworkSocket{
public:
	/// Creates a network socket 
	NetworkSocket();

	/// Creates a network socket and registers it in the global thread for auto updating, if you so desire.
	NetworkSocket(NetworkThread &network);
	
	/// Safely destroys the socket, while removing it from the global thread.
	virtual ~NetworkSocket();

	/// Virtual function that all sockets must implement, its the update method to fetch packets and other messages.
	/// \param hangTime defines how much time the thread will stall waiting for messages, 0 means no wait!
	virtual void update(Uint32 hangTime = 0) = 0;

	/// Register the socket
	void registerSocket(NetworkThread *network);

	/// Blocks the socket from receiving or sending anything
	void block();

	/// Unblocks the socket, making it ready for communication.
	void unblock();

	/// Checks whether the socket is blocked.
	bool isBlocked();

	/// The maximum number of connections allowed on this socket at any given time
	int maximumPeerCount();

	/// The number of communication channels this socket is using
	int channelCount();

	/// Get the limit of bandwidth for incoming data.
	/// Bandwidth limit on bytes per second. 0 means that there is no limit.		
	int incomingBandwidthLimit();
	
	/// Get the limit of bandwidth for outgoing data.
	/// Bandwidth limit on bytes per second. 0 means that there is no limit.		
	int outgoingBandwidthLimit();

	
	/// Set the maximum allowed peer connections for this socket.
	/// This value is 10 by default. You cannot change this value while the socket is connected. You must change it before a connection starts.
	void setMaximumPeerCount(int peer_count);

		
	/// Set the number of channels for communication between the socket and its connected peers.
	/// By default, there are 2 channels. You should change this value before the socket is working, or the change doesn't happen.
	void setChannelCount(int channel_count);

		
	/// Set the bandwidth limit for incoming data.
	/// By default, there is no bandwidth limit, this is equivalent to SetIncomingBandwidthLimit(0).
	/// You should change these values while the socket is not working, or it won't have effect.	
	void setIncomingBandwidthLimit(int bandwidth_limit);

	
	/// Set the bandwidth limit for outgoing data.
	/// By default, there is no bandwidth limit, this is equivalent to SetOutgoingBandwidthLimit(0).
	///	You should change these values while the socket is not working, or it won't have effect.	
	void setOutgoingBandwidthLimit(int bandwidth_limit);

protected:
	/// Locked when this socket is protected from access
	//sf::Mutex myMutex;

private:
	friend class NetworkThread;

	/// Blocking state of socket
	bool myBlocked;

	/// Is it registered in a thread?
	bool myRegistered;

	int myMaximumPeerCount;
	int myChannelCount;
	int myIncomingBandwidth;
	int myOutgoingBandwidth;
};



PARABOLA_NAMESPACE_END
#endif