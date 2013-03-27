#include "Nephilim/StateMachineNode.h"
#include "Nephilim/StateMachine.h"
#include "Nephilim/Events.h"

#include <iostream>

PARABOLA_NAMESPACE_BEGIN
	StateMachineNode::StateMachineNode(){
		Parent = NULL;
		RefCount = 0;
	};

	void StateMachineNode::onActivate(){
		
	};

	void StateMachineNode::onDeactivate(){

	};

	void StateMachineNode::onMessageReceived(String message){

	};

	void StateMachineNode::onDataReceived(String dataID, void* data){

	};

	void StateMachineNode::removeReference(){
		RefCount--;
		if(RefCount == 0){
			delete this;
		}
	};	
	void StateMachineNode::addReference(){
		RefCount++;
	};


	StateMachine* StateMachineNode::parentMachine(){
		return Parent;
	};

	/// Emits a signal to the parent machine
	/// If the machine decides to change into another state, it returns true.
	bool StateMachineNode::emit(int stateID, bool replaces){
		if(Parent){
			return Parent->handleSignal(stateID, replaces);
		}else{
			std::cout<<"You can't be using a state without a machine."<<std::endl;
			return false;
		}
	};


	/// Delivers an event to the state
	/// If returns true, it will be propagated to the rest of the stack
	/// Otherwise it will remain under this.
	bool StateMachineNode::onEvent(Event &event){
		return true;
	};

	bool StateMachineNode::onUpdate(Time &time){
		return true;
	};

	/// Draws the state with the current renderer
	/// If returns true, other states in the stack will be rendered
	/// Otherwise this state has exclusivity over drawing
	bool StateMachineNode::onDraw(Renderer *renderer){
		return true;
	};

PARABOLA_NAMESPACE_END