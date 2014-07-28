#include <Nephilim/Strings.h>
#include <Nephilim/StateStack.h>
#include <Nephilim/StateTransition.h>
#include <Nephilim/State.h>
#include <Nephilim/Time.h>

#include <Nephilim/Logger.h>

#include <algorithm>

NEPHILIM_NS_BEGIN

StateStack::StateStack() 
: m_stackLock(false)
, m_transition(NULL)
, mLocked(false)
{
}
StateStack::~StateStack()
{
}

/// Lock the stack to prevent further changes
/// It will be automatically unlocked when the next update() ends which has no transition active
void StateStack::lock()
{
	mLocked = true;
}

/// Check if the stack is currently locked
bool StateStack::isLocked()
{
	return mLocked;
}

void StateStack::process()
{
	if(m_stackLock)
	{
		Log("[StateStack] error: process() called while the stack was working.");
		return;
	}

	applyChangesTo(mCurrentList);
	m_pendingOperations.clear();
}

bool StateStack::isTransitionActive()
{
	return (m_transition != NULL);
}

void StateStack::clear()
{
	// If the transition is active, alter the future list instead
	if(isTransitionActive())
	{
		for(std::size_t i = 0; i < mFutureList.size(); ++i)
		{
			mFutureList[i]->finish();
		}
	}
	else
	{
		for(std::size_t i = 0; i < mCurrentList.size(); ++i)
		{
			mCurrentList[i]->finish();
		}
	}
}

/// Remove the top state from the stack
void StateStack::pop()
{
	if(!isLocked())
	{
		StateStackOperation sso;
		sso.type = StateStackOperation::Pop;
		sso.obj = NULL;
		m_pendingOperations.push_back(sso);
		Log("Popping");
	}
	else
	{
		Log("Cannot pop a locked stack");
	}
}

/// Finishes the transition animation, deletes the transition
/// and then commits all needed changes for regular functioning
void StateStack::endTransition()
{

}

void StateStack::drawCurrentList(Renderer* renderer)
{
	/*int index = m_activeList.size() - 1;
	while(index >= 0 && !m_activeList.empty())
	{
		m_activeList[index]->onRender(renderer);
		index--;
	}*/

	int index = 0;
	while(index < mCurrentList.size() && !mCurrentList.empty())
	{
		mCurrentList[index]->onRender(renderer);
		//Log("Rendering state: %s", mCurrentList[index]->mName.c_str());
		++index;
	}
}

void StateStack::drawList(std::vector<State*>& list, Renderer* renderer)
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
bool StateStack::isActive(const String& name)
{
	State* state = getBinding(name);
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
bool StateStack::isActive(State* state)
{
	// Check the pending operation queue
	for(std::vector<StateStackOperation>::iterator it = m_pendingOperations.begin(); it != m_pendingOperations.end(); ++it)
	{
		if((*it).type == StateStackOperation::Add && (*it).obj == state)
		{
			return true; // scheduled for execution, already active
		}
	}

	// Check the currently active queue for the state
	for(std::vector<State*>::iterator it = mCurrentList.begin(); it != mCurrentList.end(); ++it)
	{
		if((*it) == state)
		{
			return true; // the state is currently in the execution list
		}
	}

	if(m_transition)
	{
		for(std::vector<State*>::iterator it = mFutureList.begin(); it != mFutureList.end(); ++it)
		{
			if((*it) == state)
			{
				return true; // the state is currently in the list about to be used after transition
			}
		}
	}

	return false; // not found anywhere
}

void StateStack::performTransition(StateStackTransition* transition)
{
	// There was already a transition, warning.
	if(m_transition)
	{
		delete m_transition;
		m_transition = NULL;
		Log("[StateStack] Warning: A transition was requested when other was in progress.");
	}
	
	m_transition = transition;
	m_transition->m_stack = this;
	m_transition->activate();
}

/// Get a state or NULL
State* StateStack::getBinding(const String& name)
{
	std::map<String, State*>::iterator it = m_bindList.find(name);
	if(it != m_bindList.end())
	{
		return it->second;
	}
	else return NULL;
};

/// Get the parent game, if any
GameCore* StateStack::getParentGame()
{
	return m_parent;
};

/// Adds state to immediate execution
void StateStack::add(State* state)
{
	state->addReference();
	state->m_parent = this;
	state->onAttach();

	StateStackOperation sso;
	sso.type = StateStackOperation::Add;
	sso.obj = state;
	m_pendingOperations.push_back(sso);

	state->onActivate();
};

/// Push a binded state for execution by its name
void StateStack::add(const String& name)
{
	if(m_bindList.find(name) != m_bindList.end())
	{
		// Ensure its only added once
		if(!isActive(name))
		{
			if(m_transition)
			{
				mFutureList.push_back(m_bindList[name]);
				Log("Adding a state as future state");
			}
			else
			{
				StateStackOperation sso;
				sso.type = StateStackOperation::Add;
				sso.obj = m_bindList[name];
				m_pendingOperations.push_back(sso);
			}			

			// Activate the state
			m_bindList[name]->onActivate();
		}
	}
}

void StateStack::applyChangesTo(std::vector<State*>& list)
{
	for(std::vector<StateStackOperation>::iterator it = m_pendingOperations.begin(); it != m_pendingOperations.end(); ++it)
	{
		switch(it->type)
		{
		case StateStackOperation::Erase:

			list.erase(std::find(list.begin(), list.end(), it->obj));
			if(!isActive(it->obj))
			{
				it->obj->onDeactivate();
			}
			Log("Removed state for future list");

			break;

		case StateStackOperation::Add:
			if(std::find(list.begin(), list.end(), it->obj) == list.end())
			{
				list.push_back(it->obj);
				Log("Added state for future list");
			}
			else
			{
				//cout<<"Tried to add a state that was already there.."<<endl;
			}

			break;

		case StateStackOperation::Pop :
			{
				if(list.size() > 0)
				{
					list.erase(list.begin() + list.size() - 1);
				}
			}
			break;
		}
	}
}


/// Bind a new state to the list
bool StateStack::bind(const String& name, State* state)
{
	if(m_bindList.find(name) != m_bindList.end())
	{
		return false;
	}
	else
	{
		state->addReference();
		state->m_parent = this;
		state->onAttach();
		m_bindList[name] = state;
	}

	return true;
};

void StateStack::erase(State* state)
{
	if(std::find(mCurrentList.begin(), mCurrentList.end(), state) == mCurrentList.end())
	{
		//cout<<"Trying to erase a state that is not in the stack. No consequences."<<endl;
		return; 
	}

	if(m_stackLock)
	{
		// schedule
		StateStackOperation sso;
		sso.obj = state;
		sso.type = StateStackOperation::Erase;
		m_pendingOperations.push_back(sso);
	}
	else
	{
		// do
		//state->removeReference();
		std::vector<State*>::iterator it = std::find(mCurrentList.begin(), mCurrentList.end(), state);
		if(it != mCurrentList.end())
		{
			mCurrentList.erase(it);
		}		
	} 
};

int StateStack::getActiveStateCount()
{


	return static_cast<int>(mCurrentList.size());
}

	
void StateStack::pushEvent(Event &event){
	if(m_transition)
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

		m_stackLock = true;
		while(index != -1 && stop == false){
			mCurrentList[index]->onEvent(event);
			stop = !mCurrentList[index]->m_letEventsThrough;
			index--;
		}
		m_stackLock = false;
	}

	//if(!m_transition)
		//applyChanges();	
};


void StateStack::drawStates(Renderer *renderer){

	if(m_transition)
	{
		m_transition->draw(renderer);
		return;
	}
	else
	{
		drawCurrentList(renderer);
		return;
	}

	if(mCurrentList.size() == 0){
		return;
	}

	int index = 0;
	bool stop = false;

	while(index < mCurrentList.size())
	{
		mCurrentList[index]->onDraw(renderer);
		index++;
	}
};

void StateStack::update(Time &time)
{		
	// Did a transition just finish?
	if(m_transition && m_transition->m_finished)
	{
		delete m_transition;
		m_transition = NULL;
//		applyChanges();
	}

	if(m_transition)
	{
		m_transition->m_stack = this;
		m_transition->update(time);
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

		m_stackLock = true;
		while(index != -1 && stop == false){
			/*stop = !*/mCurrentList[index]->onUpdate(time);
			index--;
		}
		m_stackLock = false;
	}

	//if(!m_transition)
	//	applyChanges();

	// Unlock if appropriate
	if(m_pendingOperations.size() == 0 && mLocked && !m_transition)
	{
		mLocked = false;
	}
};

void StateStack::updateList(std::vector<State*>& list, const Time& time)
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
