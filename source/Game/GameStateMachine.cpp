#include <Nephilim/Game/GameStateMachine.h>

#include <Nephilim/Strings.h>
#include <Nephilim/StateTransition.h>
#include <Nephilim/Game/GameState.h>
#include <Nephilim/Time.h>

#include <Nephilim/Logger.h>

#include <algorithm>

NEPHILIM_NS_BEGIN

GameStateMachine::GameStateMachine() 
: mAnimation(NULL)
, batchPending(false)
{
}

GameStateMachine::~GameStateMachine()
{
}

/// Push a state batch down the stack
void GameStateMachine::triggerBatch(const GameStateBatch& batch)
{
	nextBatch = batch;
	batchPending = true;
}

/// Automaticaly change the state machine status
/// This uses a data-oriented FSM definition of the game screens
/// with well defined transitions and connections between nodes
/// for example, if all states in the FSM associate the BACK signal
/// with going to the previous state. its easy to go backwards without knowing what states to go to.
void GameStateMachine::triggerSignal(const String& sig)
{

}

void GameStateMachine::clear()
{

}

void GameStateMachine::drawCurrentList(GraphicsDevice* renderer)
{
	int index = 0;
	while(index < mCurrentList.size() && !mCurrentList.empty())
	{
		mCurrentList[index]->onRender(renderer);
		//Log("Rendering state: %s", mCurrentList[index]->mName.c_str());
		++index;
	}
}

void GameStateMachine::drawList(std::vector<GameState*>& list, GraphicsDevice* renderer)
{
	std::size_t index = 0;
	while(index < list.size() && !list.empty())
	{
		list[index]->onRender(renderer);
	//	Log("Rendering state: %s", list[index]->mName.c_str());
		++index;
	}
}

/// Check if a given state is currently being executed
bool GameStateMachine::isActive(const String& name)
{
	GameState* state = getBinding(name);
	if(state)
	{
		return isActive(state);
	}
	else
	{
		return false; // state doesn't exist
	}
}

/// Check if a given state is currently being executed
bool GameStateMachine::isActive(GameState* state)
{
	// Check the currently active queue for the state
	for (std::vector<GameState*>::iterator it = mCurrentList.begin(); it != mCurrentList.end(); ++it)
	{
		if((*it) == state)
		{
			return true; // the state is currently in the execution list
		}
	}

	if(mAnimation)
	{
		for (std::vector<GameState*>::iterator it = mFutureList.begin(); it != mFutureList.end(); ++it)
		{
			if((*it) == state)
			{
				return true; // the state is currently in the list about to be used after transition
			}
		}
	}

	return false; // not found anywhere
}

/// Get a state or NULL
GameState* GameStateMachine::getBinding(const String& name)
{
	std::map<String, GameState*>::iterator it = mBindingTable.find(name);
	if(it != mBindingTable.end())
	{
		return it->second;
	}
	else return NULL;
};

/// Get the parent game, if any
GameCore* GameStateMachine::getParentGame()
{
	return mGame;
}

/// Bind a new state to the list
bool GameStateMachine::bind(const String& name, GameState* state)
{
	if(mBindingTable.find(name) != mBindingTable.end())
	{
		return false;
	}
	else
	{
		state->m_parent = this;
		state->onAttach();
		state->mGame = mGame;
		mBindingTable[name] = state;
	}

	return true;
};

int GameStateMachine::getActiveStateCount()
{
	return static_cast<int>(mCurrentList.size());
}

	
void GameStateMachine::pushEvent(const Event &event)
{
	if(mAnimation)
	{
		return;
	}
	else
	{
		if(mCurrentList.size() == 0){
			return;
		}

		int index = mCurrentList.size()-1;
		bool stop = false;

		while(index != -1 && stop == false){
			mCurrentList[index]->PrimaryEventHandler(event);
			stop = !mCurrentList[index]->m_letEventsThrough;
			index--;
		}
	}	
};


void GameStateMachine::drawStates(GraphicsDevice *renderer)
{

	if(mAnimation)
	{
		mAnimation->draw(renderer);
		return;
	}
	else
	{
		drawCurrentList(renderer);
		return;
	}
};

// Entry point of Updates
void GameStateMachine::update(Time &time)
{		
	// Handle the pending batch, by building a new list
	if (batchPending)
	{
		GameStateList list;
		for (auto i = 0; i < nextBatch.orderedGameStates.size(); ++i)
		{
			if (nextBatch.orderedGameStates[i].nameBased)
			{
				list.push_back(getBinding(nextBatch.orderedGameStates[i].name));
			}
		}

		// Set our newly built list as the current one (needs work to support transitions)
	
		if (nextBatch.animation)
		{
			// There is an animation, the batch is on future list waiting to be pushed into the current one
			// mCurrentList stays the same and the animation is being processed now
			mFutureList = list;

			mAnimation = nextBatch.animation;
			mAnimation->m_stack = this;
			mAnimation->activate();
		}
		else
		{
			for (auto& gs : mCurrentList)
			{
				gs->onDeactivate();
			}

			mCurrentList = list;
			for (auto& gs : mCurrentList)
			{
				if (!gs->_activated)
				{
					gs->onActivate();
					gs->_activated = true;
				}
			}
		}

		batchPending = false;
	}

	// Wrap up the animation if it says it is finished
	if(mAnimation && mAnimation->m_finished)
	{
		delete mAnimation;
		
		Log("Passing future list with %d current %d", mCurrentList.size(),  mFutureList.size());

		mCurrentList = mFutureList;
		mFutureList.clear();		

		for (auto& gs : mCurrentList)
		{
			gs->onActivate();
		}

		mAnimation = nullptr;
	}

	if(mAnimation)
	{
		mAnimation->m_stack = this;
		mAnimation->update(time);
		return;
	}
	else
	{
		if(mCurrentList.size() == 0){
			return;
		}
		// older states draw first
		int index = mCurrentList.size()-1;
		bool stop = false;

		while(index != -1 && stop == false){
			/*stop = !*/mCurrentList[index]->onUpdate(time);
			index--;
		}
	}

};

void GameStateMachine::updateList(GameStateList& list, const Time& time)
{
	if(list.size() == 0)
	{
		return;
	}

	// older states draw first
	int index = list.size()-1;
	bool stop = false;

	while(index != -1 && stop == false){
		/*stop = !*/list[index]->onUpdate(time);
		index--;
	}
}

NEPHILIM_NS_END
