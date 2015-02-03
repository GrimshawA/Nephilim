#include <Nephilim/Game/GameNetwork.h>

NEPHILIM_NS_BEGIN

/// Global switch for the game's networking
/// This will either enable or stop the entire networking system on the owning GameCore
void GameNetwork::setEnabled(bool _enabled)
{
	allowNetworking = _enabled;
}

NEPHILIM_NS_END