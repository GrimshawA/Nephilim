#include <Nephilim/StateStack.h>
#include <Nephilim/StateTransition.h>
#include <Nephilim/State.h>
#include <Nephilim/Time.h>
#include <Nephilim/Strings.h>
#include <Nephilim/Logger.h>

#include <algorithm>

NEPHILIM_NS_BEGIN

StateStack::StateStack() 
: m_stackLock(false)
, m_transition(NULL)
{
}

StateStack::~StateStack()
{
}

void StateStack::process()
{
	if(m_stackLock)
	{
		Log("[StateStack] error: process() called while the stack was working.");
		return;
	}

	applyChanges();
}

void StateStack::drawCurrentList(Renderer* renderer)
{
	int index = m_activeList.size() - 1;
	while(index >= 0 && !m_activeList.empty())
	{
		m_activeList[index]->onRender(renderer);
		index--;
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
		}
	}
}


void StateStack::performTransition(StateTransition* transition)
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

	// A new transition kicked in, lets build the future stack for it
	std::vector<State*> futureList = m_activeList;
	applyChangesTo(futureList);
	m_transition->m_futureList.insert(m_transition->m_futureList.end(), futureList.rbegin(), futureList.rend());

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
};

/// Push a binded state for execution by its name
void StateStack::add(const String& name)
{
	if(m_bindList.find(name) != m_bindList.end())
	{
		StateStackOperation sso;
		sso.type = StateStackOperation::Add;
		sso.obj = m_bindList[name];
		m_pendingOperations.push_back(sso);
	}
}

/// Checks if the stack is empty and if so adds a state from the wait list
void StateStack::processWaitList()
{
	// erased, if reaches 0, add to stack from waiting list
	if(m_activeList.empty() && !m_waitList.empty())
	{
		add(m_waitList.front());
		m_waitList.front()->removeReference(); // remove waiting list reference
		m_waitList.erase(m_waitList.begin());
	}
}

/// Adds a state to the waiting list
void StateStack::addWaiting(State* state)
{
	state->addReference(); // reference just for the waiting list
	m_waitList.push_back(state);

	//cout<<"[StateStack] State added to waiting list"<<endl;
};


/// Processes the list of changes to the stack
void StateStack::applyChanges()
{
	while(!m_pendingOperations.empty())
	{
		switch(m_pendingOperations.front().type)
		{
			case StateStackOperation::Erase:
				//erase(m_pendingOperations.front().obj);
				//cout<<"Trying to erase: "<< m_pendingOperations.front().obj<<endl;
				m_pendingOperations.front().obj->m_scheduledRemoval = false;
				m_activeList.erase(std::find(m_activeList.begin(), m_activeList.end(), m_pendingOperations.front().obj));
				break;

			case StateStackOperation::Add:
				if(std::find(m_activeList.begin(), m_activeList.end(), m_pendingOperations.front().obj) == m_activeList.end())
				{
					m_pendingOperations.front().obj->onActivate();
					//m_pendingOperations.front().obj->addReference();
					//cout<<"adding: "<<m_pendingOperations.front().obj<<endl;
					m_activeList.push_back(m_pendingOperations.front().obj);		
				}
				else
				{
					//cout<<"Tried to add a state that was already there.."<<endl;
				}
					
				break;
		}

		m_pendingOperations.erase(m_pendingOperations.begin());
	}

	// There is a chance of already having more states - stack overflow if there is a loophole within state logic
	if(!m_pendingOperations.empty())
	{
		applyChanges();
	}
};

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

/// Erase a state
void StateStack::erase(State* state)
{
	if(std::find(m_activeList.begin(), m_activeList.end(), state) == m_activeList.end())
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
		std::vector<State*>::iterator it = std::find(m_activeList.begin(), m_activeList.end(), state);
		if(it != m_activeList.end())
		{
			m_activeList.erase(it);
		}		
		//cout<<"[StateStack] Erased"<<endl;

		processWaitList();
	} 
};

int StateStack::getActiveStateCount()
{


	return static_cast<int>(m_activeList.size());
}

	
void StateStack::pushEvent(Event &event){
	if(m_transition)
	{
		return;
	}
	else
	{
		if(m_activeList.size() == 0){
			return;
		}

		int index = m_activeList.size()-1;
		bool stop = false;

		m_stackLock = true;
		while(index != -1 && stop == false){
			/*stop = !*/m_activeList[index]->onEvent(event);
			index--;
		}
		m_stackLock = false;
	}

	if(!m_transition)
		applyChanges();	
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

	if(m_activeList.size() == 0){
		return;
	}

	int index = 0;
	bool stop = false;

	while(index < m_activeList.size()){
		m_activeList[index]->onDraw(renderer);
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
		applyChanges();
	}

	if(m_transition)
	{
		m_transition->update(time);
		return;
	}
	else
	{
		if(m_activeList.size() == 0){
			return;
		}
		// older states draw first
		int index = m_activeList.size()-1;
		bool stop = false;

		m_stackLock = true;
		while(index != -1 && stop == false){
			/*stop = !*/m_activeList[index]->onUpdate(time);
			index--;
		}
		m_stackLock = false;

	
		return;
	}

	if(!m_transition)
		applyChanges();
};

void StateStack::updateList(std::vector<State*>& list, const Time& time)
{
	if(list.size() == 0){
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
