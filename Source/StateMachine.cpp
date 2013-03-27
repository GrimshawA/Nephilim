#include "Nephilim/StateMachine.h"

#include <iostream>

PARABOLA_NAMESPACE_BEGIN
	StateMachine::StateMachine(){

	};

	StateMachine::~StateMachine(){
		//destroy states? need reference counting.
		for(std::map<int, StateMachineNode*>::iterator it = nodes.begin(); it != nodes.end(); it++){
			(*it).second->removeReference();
		}

	};

	StateMachineNode* StateMachine::getState(int stateID){
		StateMachineNode *node = nodes[stateID];
		node->RefCount++;
		return node;
	};

	void StateMachine::setState(int stateID, StateMachineNode* node){
		nodes[stateID] = node;
		node->Parent = this;
		node->RefCount++;
	};

	void StateMachine::removeState(int stateID){
		nodes[stateID]->removeReference();
		nodes[stateID] = NULL;
	};

	/// Replaces the top of the stack with the new state
	void StateMachine::swapState(int stateID){
		popState();
		pushState(stateID);
	};

	/// Pushes a state into the stack
	void StateMachine::pushState(int stateID){
		StateMachineNode *node = nodes[stateID];
		if(node){
			nodeStack.push_back(node);
			node->onActivate();
			
		}
		else{
			std::cout<<"You tried to push a node that doesnt exist."<<std::endl;
		}
		
	};

	/// Pops the top of the stack
	void StateMachine::popState(){
		if(nodeStack.size() != 0){					
			nodeStack[nodeStack.size()-1]->onDeactivate();
			nodeStack.pop_back();		
		}
		else{
			
		}
	};


	void StateMachine::propagateEvent(Event &event){
		if(nodeStack.size() == 0){
			return;
		}

		int index = nodeStack.size()-1;
		bool stop = false;

		while(index != -1 && stop == false){
			stop = !nodeStack[index]->onEvent(event);
			index--;
		}
	};

	bool StateMachine::handleSignal(int stateID, bool toReplace){
		if(nodes[stateID] != NULL){
			if(toReplace){
				swapState(stateID);
			}
			else{
				pushState(stateID);
			}
			return true;
		}
		else
			return false;
	};

	bool StateMachine::deliverMessage(int stateID, String message){
		if(nodes[stateID] != NULL){
			nodes[stateID]->onMessageReceived(message);
			return true;
		}
		else
			return false;
	};

	bool StateMachine::deliverData(int stateID, String dataID, void* data){
		if(nodes[stateID] != NULL){
			nodes[stateID]->onDataReceived(dataID, data);
			return true;
		}
		else
			return false;
	};

void StateMachine::drawStates(Renderer *renderer){
	if(nodeStack.size() == 0){
		return;
	}

	int index = 0;
	bool stop = false;

	while(index < nodeStack.size() && stop == false){
		stop = !nodeStack[index]->onDraw(renderer);
		index++;
	}
};

	void StateMachine::updateStates(Time &time){
		if(nodeStack.size() == 0){
			return;
		}
		// older states draw first
		int index = nodeStack.size()-1;
		bool stop = false;

		while(index != -1 && stop == false){
			stop = !nodeStack[index]->onUpdate(time);
			index--;
		}
	};

PARABOLA_NAMESPACE_END
