#ifndef NephilimCommandSystem_h__
#define NephilimCommandSystem_h__

#include <Nephilim/Platform.h>

#include <vector>

NEPHILIM_NS_BEGIN

/**
	\class CommandSystem
	\brief Has the ability to process user commands and operate on the game

	As commands are sent to the command system, it will do things on the BaseGame instance.

	For example, a typical command is to "restart" the game, and once this command is sent,
	the command system will do the necessary steps to put the game starting over from its first state.	

	This system has 3 primary uses:
	1) Act upon commands input in the console
	2) Act upon commands incoming from the remote development bridge (a remote console via TCP)
	3) Act upon programmer's commands from source code
*/
class NEPHILIM_API CommandSystem
{
public:

	struct Command
	{};

	/// In order to support multithreading and commands coming from arbitrary places
	/// while still executing in order of arrival, a queue is used rather than
	/// instant execution of commands
	std::vector<Command> commandQueue;
};

NEPHILIM_NS_END
#endif // NephilimCommandSystem_h__
