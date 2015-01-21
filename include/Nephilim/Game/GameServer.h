#ifndef NephilimGameServer_h__
#define NephilimGameServer_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

/**
	\class GameServer
	\brief Embedded server to be used in any game

	This is coupled to the game instance itself, and supports
	world synchronization, in order to make a game multiplayer.

	Most games will have a game server running in single player
	and when playing multiplayer as the host. However, when
	connected to an external server (joining other player session
	or a dedicated server), we don't need a server.
*/
class NEPHILIM_API GameServer
{
public:

};

NEPHILIM_NS_END
#endif // NephilimGameServer_h__
