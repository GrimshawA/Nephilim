#ifndef PARABOLA_NETWORKTHREAD_H
#define PARABOLA_NETWORKTHREAD_H

#include <Nephilim/Platform.h>
#include <SFML/System/Thread.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Lock.hpp>
#include <vector>

NEPHILIM_NS_BEGIN

class NetworkSocket;
/**
	\ingroup Network
	\class NetworkThread
	\brief Global network thread

	It will create a parallel thread to handle networking more fluidly as soon
	as a socket is created.

	When the last socket is destroyed, the thread goes back to sleep.

	When creating a socket, notice that you will be able to choose if it belongs to the 
	NetworkThread for auto updating.

	\todo Later i will implement a feature to be able to group sockets, in order to block them while the game loses focus.

*/
class NEPHILIM_API NetworkThread{
public:
	/// Creates an empty network thread, but it is sleeping until sockets are added
	NetworkThread();

	/// Adds a socket for updating
	void add(NetworkSocket *socket);

protected:
	/// The thread function
	void threadFunc();

private:
	friend class NetworkSocket;
	std::vector<NetworkSocket*> mySockets;
	bool mySleeping;
	bool myCanLaunch;

	sf::Thread *myThread;
	sf::Mutex myMutex;
};



NEPHILIM_NS_END
#endif