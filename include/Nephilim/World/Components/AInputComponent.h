#ifndef NephilimWorldInputComponent_h__
#define NephilimWorldInputComponent_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>
#include <Nephilim/World/Component.h>

#include <sigc++/sigc++.h>

#include <functional>
#include <map>

NEPHILIM_NS_BEGIN

template<typename T>
class MethodDelegate
{
	typedef void(T::*FMethodPtr)(float);
	typedef void(T::*FMethodPtr2)(void);
};


/**
	\class AInputComponent
	\brief (Actor) Gives the actor the ability to receive input

	Usually, all characters in a game will be instances of the Actor class,
	with a ACharacterComponent as the root component. The physics system will ensure
	validity of this character controller, if there is any.

	It will also conveniently hide networking so the engine takes care of syncing all characters in the simulation.
	Its children components will have their transforms automatically handled to stay relative to the character controller, so
	a character can be easily made to walk around terrain etc, even before we add any final mesh.
*/
class AInputComponent : public Component
{
public:
	/// When not enabled, the component doesn't fire input anymore
	bool enabled;

	struct AxisMapping
	{
		String name;
		sigc::signal<void, float> binding;
	};

	enum ActionModes
	{
		Pressed,
		Released,
		Repeat
	};

	struct ActionBinding
	{
		ActionModes mode;
		sigc::signal<void> binding;
	};

	std::map<String, AxisMapping> axisMappings;

	std::map<String, ActionBinding> actionBindings;

public:


	template<typename Class>
	void bindAxis(const String& axisName, Class* object, typename MethodDelegate<Class>::FMethodPtr func);

	template<typename Class>
	void bindAction(const String& actionName, ActionModes mode, Class* object, typename MethodDelegate<Class>::FMethodPtr2 func);

	/// Emit signals for the given axis
	void fireAxis(const String& axisName);

	void fireAction(const String& actionName);
};


template<typename Class>
void AInputComponent::bindAxis(const String& axisName, Class* object, typename MethodDelegate<Class>::FMethodPtr func)
{
	// Binds to the handler if it exists, or creates new and binds
	axisMappings[axisName].binding.connect(sigc::mem_fun(object, func));
}

template<typename Class>
void AInputComponent::bindAction(const String& actionName, ActionModes mode, Class* object, typename MethodDelegate<Class>::FMethodPtr2 func)
{
	actionBindings[actionName].mode = mode;
	actionBindings[actionName].binding.connect(sigc::mem_fun(object, func));
}

NEPHILIM_NS_END
#endif // NephilimWorldInputComponent_h__
