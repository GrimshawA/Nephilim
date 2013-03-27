#ifndef MINIMAL_BUILD

#include "Nephilim/Entity.h"
#include "Nephilim/SceneNode.h"
#include "Nephilim/SceneRenderer.h"
#include "Nephilim/EntityManager.h"

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN

/// Privately constructs Entity()
Entity::Entity(EntityManager *parent) : SceneItem(){
	myEntityManager = parent;
};

/// Adds a component to the entity, from the component factory
void Entity::addComponent(const String &componentName){
	EntityComponent* component = myEntityManager->getComponentFactory().spawnComponent(componentName, this);
	if(!component){

		cout<<"Could not find the component: "<<componentName<<endl;
	}
	else{
		attachComponent(component);
	}
};

/// Adds a component to the entity, from the component, and passes some initialization parameters
void Entity::addComponent(const String &componentName, const StringList &params){
	EntityComponent* component = myEntityManager->getComponentFactory().spawnComponent(componentName, params, this);
	if(!component){

		cout<<"Could not find the component: "<<componentName<<endl;
	}
};

/// Called when the entity is attached
void Entity::onAttach(){
	cout<<"Entity attached"<<endl;

	myPosition = getParentSceneNode()->getGlobalPosition();

	// prepare components too
	for(ComponentIterator it = myComponents.begin(); it != myComponents.end(); it++){
		it->second->onAttach();
	}
};

/// Attaching a component to the entity
void Entity::attachComponent(EntityComponent* component){
	myComponents[makeStringID(component->getName(), false)] = component;
	component->myParent = this;
	if(getParentSceneNode()) // only activate if already in the scene
		component->onAttach();
};

/// Called when the scene item is supposed to render
void Entity::onRender(SceneRenderer* renderer){
/*	sf::CircleShape c;
	c.SetFillColor(sf::Color::Blue);
	c.SetRadius(30);
	c.SetPosition(getParentSceneNode()->getGlobalPosition().x, getParentSceneNode()->getGlobalPosition().y);*/
	//renderer->draw(c);
};

/// Get the entity position
/// Entities can have different positions than the parent scene node, because they may be simulated by physics
Vec2f Entity::getPosition(){
	return myPosition;
};

/// Resets the entity position to the parent scene node
void Entity::resetPosition(){
	if(getParentSceneNode())
		myPosition = getParentSceneNode()->getGlobalPosition();
};
PARABOLA_NAMESPACE_END

#endif