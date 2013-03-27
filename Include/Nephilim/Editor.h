#ifndef PARABOLA_EDITOR_H
#define PARABOLA_EDITOR_H

#include "Platform.h"
#include "GameCore.h"
#include "Graphics.h"
#include "Network.h"

#include <iostream>

using namespace std;

PARABOLA_NAMESPACE_BEGIN

class EditorInterface;

class PARABOLA_API EditorServer{
public:
	EditorServer(){

	}

	NetworkServer myServerSocket;
};

/// Either has a local editor server, or talks to an exterior one
class PARABOLA_API EditorNetworkInterface{
public:
	EditorNetworkInterface(){
		networkThread = new NetworkThread();
		clientSocket.registerSocket(networkThread);
	}

	void createLocalServer(){
		myServer = new EditorServer();
		myServer->myServerSocket.registerSocket(networkThread);

		if(myServer->myServerSocket.start(8600)){
			cout<<"Editor server started"<<endl;
		}
		else cout<<"Editor server failed"<<endl;

		clientSocket.connect("127.0.0.1", 8600, 4000);
		// should be ready., 8005
	}


	// The interface with a remote server (or local if its the case)
	NetworkClient clientSocket;
	NetworkThread *networkThread;

	/// True if the server is local
	bool myLocalMode;

	/// NULL unless a local server is running
	EditorServer *myServer;
};

/**
	\ingroup Core
	\class Editor
	\brief The graphical editor of levels and other content.

	The editor is just a package that you plug into the executable directory.
	It allows to create rich levels, full of content, and then play within them.

	Editor is extensible through scripting, and EditorInterface can be made at taste, for extending the
	main abilities.
*/
class PARABOLA_API Editor : public GameCore{
public:
	/// Creates the editor
	Editor();

	/// When the editor is created
	void onCreate();

	/// When an event is polled
	void onEvent(const Event &event);

	/// When the editor is updated
	void onUpdate(float elapsedTime);

	/// When the editor is rendered
	void onRender();

	/// When a rocket inline event happens
	void onRocketEvent(String event);

	void consoleThread();

	void createWorldScript(String command, String slist);

	void debugBroadcast(String command, String slist){
		myInterface.myServer->myServerSocket.send(slist);
	}

protected:
	/// Called when the 'Run' button is clicked.
	/// It will make a callback in EditorInterface.
	void runSimulation();

private:
	EditorInterface *myEditorInterface;	

	SceneRenderer *renderer;
	RocketContext *uiContext;

	NetworkClient client;
	NetworkServer server;

	NetworkThread *network;

	EditorNetworkInterface myInterface;
};

/**
	\ingroup Core
	\class EditorInterface
	\brief The interface for extending the editor functionality.

	Here's a detailed list of things you can and should do with this:

	Run simulation:

*/
class PARABOLA_API EditorInterface{
public:
	/// Callback for running the simulation.
	virtual void runSimulation() = 0;
};

PARABOLA_NAMESPACE_END
#endif