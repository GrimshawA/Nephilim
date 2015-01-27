#ifndef NephilimDevRDKHost_h__
#define NephilimDevRDKHost_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

/**
	\class RDKHost
	\brief Host for the remote development kit (RDK) clients

	The RDK module is basically a bridge between an editor,
	remote console or other tools and an host application.
	This communication tunnel between both ends allows to 
	send files both ways to update assets and settings, as 
	well as pass around commands to do multiple useful things.

	This module is _exclusively_ only for development purposes,
	shipped games will never include a working RDK module in them.

	By instancing a RDKHost and connecting it to the running engine,
	it becomes ready to receive connections and operate under the
	rules documented for the RDK.

	So, enable or disable this host for the remote development stuff to work.

	Features:
	- Remote inspecting, can watch what's going on with the game as its being played, live, from another machine.
	  This is really useful is we want for example to test the game in a console, while in a development machine
	  we get profiling data, variables, statistics and other stuff.
	- Sending commands like game restarting, closing and other high level stuff
	- Updating assets in the game and hot reloading them
*/
class NEPHILIM_API RDKHost
{
public:

	/// Initialize basic stuff
	RDKHost();
};

NEPHILIM_NS_END
#endif // NephilimDevRDKHost_h__
