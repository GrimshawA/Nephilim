#ifndef NephilimGameNetwork_h__
#define NephilimGameNetwork_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

/**
	\class GameNetwork
	\brief Central hub for a game to do networking with remote peers

	This class acts as a coordinator between all activity that is going on in
	both user code and built-in network activity. Basically, each World
	will handle itself, but its networking systems will directly connected here,
	for higher level monitoring.

	For example, nothing stops us from having our World be a server and a client at the same time,
	we could be a client to a MMO, but at the same time be a local server to our tablet, which lets us
	do inventory management there. This class will track that but not necessarily interfere.

	When running on dedicated server mode, the entire game has no graphics at all, only simulation is being run,
	which is the perfect opportunity to let things run at full speed to ensure a quality simulation for all clients.

	All NetworkSystems will have knowledge of this state and can adapt to the global settings in it as well.

	Extensions:
	The game's networking can be extended by plugins or not, using ExtensionNetwork as a base,
	then registered in here too, to be used by the network systems.
*/
class NEPHILIM_API GameNetwork
{
public:

	// todo: put the network extensions in here

	/// This is the global GameCore switch for the networking in the engine
	bool allowNetworking = true;

	bool isDedicatedServer = false;

public:

	/// Global switch for the game's networking
	/// This will either enable or stop the entire networking system on the owning GameCore
	void setEnabled(bool _enabled);
};

NEPHILIM_NS_END
#endif // NephilimGameNetwork_h__