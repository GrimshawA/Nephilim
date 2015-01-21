#ifndef NephilimNetworkConnection_h__
#define NephilimNetworkConnection_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>

NEPHILIM_NS_BEGIN

class Packet;

/**
	\class Connection
	\brief Interface for different connection methods

	This class is the base for different kinds of communication methods that can be used to
	transfer data over the network.

	This means in essence that a peer in the network will be pushing packets of raw data over
	a Connection at all times. This peer doesn't care how it gets there, it only cares that
	the protocol is being followed.

	This allows that the packets can be sent through TCP, Enet, RakNet, UDP or whatever 
	specialization of Connection is being used by the application.

	This is so different networking systems can be plugged in and out dynamically without having to change any user code.
*/
class NEPHILIM_API Connection
{
public:

	virtual void connect(const String& address, int port) = 0;

	/// Sending a Packet through this connection
	virtual void send(const Packet& pck) = 0;

	virtual void update() = 0;
};

NEPHILIM_NS_END
#endif // NephilimNetworkConnection_h__
