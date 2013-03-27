#ifndef MINIMAL_BUILD
#include "Nephilim/EntityComponent.h"

PARABOLA_NAMESPACE_BEGIN

/// Creates an empty component - abstract
EntityComponent::EntityComponent(const String &name){
	myName = name;
	myParent = NULL;
}

/// Destructor
EntityComponent::~EntityComponent(){

}

/// Get the component name - the name registered in the factory
String EntityComponent::getName(){
	return myName;
};

/// Get the parent entity, NULL if the component is not attached yet
Entity* EntityComponent::getParentEntity(){
	return myParent;
};

PARABOLA_NAMESPACE_END

#endif