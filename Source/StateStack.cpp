#include "Nephilim/StateStack.h"
#include "Nephilim/ASEngine.h"
#include "AS/aswrappedcall.h"

#include <iostream>
#include <algorithm>
using namespace std;

PARABOLA_NAMESPACE_BEGIN

/// Register the state stack into engine
bool registerStateStack(ASEngine* engine)
{
	engine->exportReferenceDataType("StateStack");
	engine->exportReferenceDataType("State");

	if(engine->getPortableMode())
	{
		engine->getASEngine()->RegisterObjectMethod("StateStack", "void add(State@)", WRAP_MFN(StateStack, add), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectMethod("StateStack", "void addWaiting(State@)", WRAP_MFN(StateStack, addWaiting), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectMethod("StateStack", "bool bind(const string& in, State@)", WRAP_MFN(StateStack, bind), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectMethod("StateStack", "int getActiveStateCount()", WRAP_MFN(StateStack, getActiveStateCount), asCALL_GENERIC);

	}
	else
	{
		engine->getASEngine()->RegisterObjectMethod("StateStack", "void add(State@)", asMETHOD(StateStack, add), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectMethod("StateStack", "void addWaiting(State@)", asMETHOD(StateStack, addWaiting), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectMethod("StateStack", "bool bind(const string& in, State@)", asMETHOD(StateStack, bind), asCALL_THISCALL);	
		engine->getASEngine()->RegisterObjectMethod("StateStack", "int getActiveStateCount()", asMETHOD(StateStack, getActiveStateCount), asCALL_THISCALL);
	}

	return true;
};


StateStack::StateStack() 
: m_stackLock(false)
{
};

StateStack::~StateStack()
{
};

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

	if(m_stackLock)
	{
		// schedule
		StateStackOperation sso;
		sso.type = StateStackOperation::Add;
		sso.obj = state;
		m_pendingOperations.push_back(sso);
	}
	else
	{
		// do
		state->onActivate();
		m_activeList.push_back(state);
	}
};

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

	cout<<"[StateStack] State added to waiting list"<<endl;
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
				cout<<"Trying to erase: "<< m_pendingOperations.front().obj<<endl;
				m_pendingOperations.front().obj->m_scheduledRemoval = false;
				m_activeList.erase(std::find(m_activeList.begin(), m_activeList.end(), m_pendingOperations.front().obj));
				break;

			case StateStackOperation::Add:
				if(std::find(m_activeList.begin(), m_activeList.end(), m_pendingOperations.front().obj) == m_activeList.end())
				{
					m_pendingOperations.front().obj->onActivate();
					//m_pendingOperations.front().obj->addReference();
					cout<<"adding: "<<m_pendingOperations.front().obj<<endl;
					m_activeList.push_back(m_pendingOperations.front().obj);		
				}
				else
				{
					cout<<"Tried to add a state that was already there.."<<endl;
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
		cout<<"Trying to erase a state that is not in the stack. No consequences."<<endl;
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
		cout<<"[StateStack] Erased"<<endl;

		processWaitList();
	} 
};

int StateStack::getActiveStateCount()
{


	return static_cast<int>(m_activeList.size());
}

	
void StateStack::propagateEvent(Event &event){
		if(m_activeList.size() == 0){
			return;
		}

		int index = m_activeList.size()-1;
		bool stop = false;

		m_stackLock = true;
		while(index != -1 && stop == false){
			stop = !m_activeList[index]->onEvent(event);
			index--;
		}
		m_stackLock = false;

		applyChanges();
};


void StateStack::drawStates(Renderer *renderer){
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

void StateStack::updateStates(Time &time){
		
		if(m_activeList.size() == 0){
			return;
		}
		// older states draw first
		int index = m_activeList.size()-1;
		bool stop = false;

		m_stackLock = true;
		while(index != -1 && stop == false){
			stop = !m_activeList[index]->onUpdate(time);
			index--;
		}
		m_stackLock = false;

		applyChanges();
};

PARABOLA_NAMESPACE_END
