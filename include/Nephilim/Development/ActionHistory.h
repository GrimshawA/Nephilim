#ifndef NephilimEditorActionHistory_h__
#define NephilimEditorActionHistory_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Development/Action.h>

#include <vector>

NEPHILIM_NS_BEGIN

/**
	\class ActionHistory
	\brief [Editor] Holds a list of previous actions for undo/redo features

	Generic utility class for the editors to use, in order to store actions
	for undoing later if needed. Also provides some basic helpers for transmitting over
	network in order to sync work.
*/
class NEPHILIM_API ActionHistory
{
public:
	/// Default initialization
	ActionHistory();


	std::vector<Action> mActions; ///< List of previous actions
	int                 mNumTrackedActions; ///< Number of actions being tracked in the history
};

NEPHILIM_NS_END
#endif // NephilimEditorActionHistory_h__
