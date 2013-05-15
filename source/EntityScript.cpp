#ifndef MINIMAL_BUILD

#include "Nephilim/EntityScript.h"
#include "Nephilim/ASEngine.h"

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

/// Creates the entity script
EntityScript::EntityScript(EntityManager *parent) : Entity(parent){
	myScriptEngine = NULL;
};

/// Called when the entity is attached
void EntityScript::onAttach(){	
	Entity::onAttach();
	if(myScriptEngine){
		cout<<"Calling attach function on: "<<name()<<endl;
		//myScriptEngine->ExecuteScriptFunction(name() + ".as" , "void onAttach()");
	}

	asDWORD a;
	
};


NEPHILIM_NS_END

#endif