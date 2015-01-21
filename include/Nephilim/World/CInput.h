#ifndef NephilimRazerCInput_h__
#define NephilimRazerCInput_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>
#include <Nephilim/World/Component.h>

#include <sigc++/sigc++.h>

#include <functional>

NEPHILIM_NS_BEGIN

template<typename T>
class MethodDelegate
{
	typedef void(T::*FMethodPtr)(float);
	typedef void(T::*FMethodPtr2)(void);
};



class CInput : public Component
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
void CInput::bindAxis(const String& axisName, Class* object, typename MethodDelegate<Class>::FMethodPtr func)
{
	// Binds to the handler if it exists, or creates new and binds
	axisMappings[axisName].binding.connect(sigc::mem_fun(object, func));
}

template<typename Class>
void CInput::bindAction(const String& actionName, ActionModes mode, Class* object, typename MethodDelegate<Class>::FMethodPtr2 func)
{
	actionBindings[actionName].mode = mode;
	actionBindings[actionName].binding.connect(sigc::mem_fun(object, func));
}

NEPHILIM_NS_END
#endif // NephilimRazerCInput_h__
