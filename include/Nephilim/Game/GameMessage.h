#ifndef NephilimGameMessage_h__
#define NephilimGameMessage_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

/**
	\class GameMessage
	\brief Structure that holds a generic message (event) that can be dispatched

	This is an essential part of the Game module. GameMessage can hold a set of parameters
	to describe a given event, and this data can be dispatched into multiple parts of the game.

	For example, it can be used to communicate from C++ to a scripting language and the opposite.

	Possible use cases:
	- An unit is destroyed and a GameMessage is generated to tell the scripts, which can then act upon it.

*/
class NEPHILIM_API GameMessage
{
public:
	
};

NEPHILIM_NS_END
#endif // NephilimBaseGame_h__
