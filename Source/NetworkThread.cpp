#ifndef MINIMAL_BUILD

#include "Nephilim/NetworkThread.h"
#include "Nephilim/NetworkSocket.h"

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN
/// Creates an empty network thread, but it is sleeping until sockets are added
NetworkThread::NetworkThread(){
	mySleeping = true;
	myCanLaunch = true;
	myThread = NULL;

	
};

/// Adds a socket for updating
void NetworkThread::add(NetworkSocket *socket){
	sf::Lock lock(myMutex);
	mySockets.push_back(socket);
	if(mySleeping && myCanLaunch){
		// Should launch thread
		myThread = new sf::Thread(&NetworkThread::threadFunc, this);
		myThread->launch();
	}
};

/// The thread function
void NetworkThread::threadFunc(){
	while(1){
		sf::Lock lock(myMutex);
		for(unsigned int i = 0; i < mySockets.size(); i++){
			if(! mySockets[i]->isBlocked())
				mySockets[i]->update(0);
		}
	}

	if(myThread){
		delete myThread;
	}
};

PARABOLA_NAMESPACE_END

#endif