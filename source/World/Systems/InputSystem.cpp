#include <Nephilim/World/Systems/InputSystem.h>

#include <Nephilim/World/ComponentManager.h>
#include <Nephilim/World/World.h>
#include <Nephilim/World/Components/AInputComponent.h>

#include <Nephilim/Foundation/Logging.h>

NEPHILIM_NS_BEGIN

/// Check if any given keyboard key is pressed
bool InputSystem::isKeyPressed(Keyboard::Key key)
{
	return keyboardState[key];
}

/// Update the continuous input detection
void InputSystem::update(const Time& time)
{
	for (auto it = bindings.axisMappings.begin(); it != bindings.axisMappings.end(); ++it)
	{
		if (isKeyPressed(it->second.key))
		{
			emitAxisAction(it->first, 1.f);
		}
	}
}

/// Emit an axis action into the world
void InputSystem::emitAxisAction(const String& name, float scale)
{
	Log("Emitting axis %s", name.c_str());

	// Actors
	for (std::size_t i = 0; i < _World->mPersistentLevel->actors.size(); ++i)
	{
		Actor* actor = _World->mPersistentLevel->actors[i];
		for (std::size_t j = 0; j < actor->components.size(); ++j)
		{
			if (dynamic_cast<AInputComponent*>(actor->components[j]))
			{
				AInputComponent* inputComponent = dynamic_cast<AInputComponent*>(actor->components[j]);
				inputComponent->fireAxis(name);
			}
		}
	}
}

/// Push an event into the input system
void InputSystem::updateWithEvent(const Event& event)
{
	// A key was pressed, let's check if it casts an action
	if (event.type == Event::KeyPressed)
	{
		keyboardState[event.key.code] = true;

		for (std::size_t i = 0; i < bindings.actionMappings.size(); ++i)
		{
			if (bindings.actionMappings[i].isTriggeredBy(event.key.code))
			{
				emitAction(bindings.actionMappings[i].actionName, AInputComponent::Pressed);
			}
		}
	}
	else if (event.type == Event::KeyReleased)
	{
		keyboardState[event.key.code] = false;
	}
}

/// Emit an action into the world
void InputSystem::emitAction(const String& name, AInputComponent::ActionModes mode)
{
	Log("Action: %s", name.c_str());

	ComponentManager* inputManager = _World->getComponentManager<AInputComponent>();

	// ECS
	for (std::size_t i = 0; i < inputManager->size(); ++i)
	{
		AInputComponent* inputComponent = (AInputComponent*)inputManager->getInstance(i);
		inputComponent->fireAction(name);
	}

	// Actors
	for (std::size_t i = 0; i < _World->mPersistentLevel->actors.size(); ++i)
	{
		Actor* actor = _World->mPersistentLevel->actors[i];
		for (std::size_t j = 0; j < actor->components.size(); ++j)
		{
			if (dynamic_cast<AInputComponent*>(actor->components[j]))
			{
				AInputComponent* inputComponent = dynamic_cast<AInputComponent*>(actor->components[j]);
				inputComponent->fireAction(name);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////

/// Add a new action name to the list
void InputBindingSheet::addAction(const String& actionName)
{
	ActionMapping newAction;
	newAction.actionName = actionName;
	actionMappings.push_back(newAction);
}

/// Bind a new key to a given action
void InputBindingSheet::addTriggerKey(const String& action, Keyboard::Key k)
{
	for (std::size_t i = 0; i < actionMappings.size(); ++i)
	{
		if (actionMappings[i].actionName == action)
		{
			ActionTrigger trigger;
			trigger.key = k;

			actionMappings[i].triggers.push_back(trigger);
		}
	}
}

NEPHILIM_NS_END