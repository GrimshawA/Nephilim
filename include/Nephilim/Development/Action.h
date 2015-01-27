#ifndef NephilimEditorAction_h__
#define NephilimEditorAction_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

/**
	\class Action
	\brief [Editor] An action information from an editor

	This class is a very abstract concept. It aims to handle
	any action from any editor of the toolset in a generic way.

	The goal is to contain information about a given editor action,
	so it can be done/undone at later stages. 

	Example, you add an entity or paint some terrain, and then are able
	to reverse those actions with the help of the action history system.
	Each of those actions would have to be represented as a Action.
*/
class NEPHILIM_API Action
{
public:

};

NEPHILIM_NS_END
#endif // NephilimEditorAction_h__
