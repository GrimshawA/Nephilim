#ifndef NephilimRazerCInput_h__
#define NephilimRazerCInput_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>
#include <Nephilim/World/Component.h>

#include <sigc++/sigc++.h>

#include <functional>

NEPHILIM_NS_BEGIN

typedef void(*FunctorDelegate)(float);

typedef void(*FPAXISDELEGATE)(float);

template<typename T>
class MethodDelegate
{
	typedef void(T::*FMethodPtr)(float);
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

	std::map<String, AxisMapping> axisMappings;

public:

	template<typename Class>
	void bindAxis(const String& axisName, Class* object, typename MethodDelegate<Class>::FMethodPtr func);

	void bindAction(const String& actionName, int mode, void* object, void* functor);

	/// Emit signals for the given axis
	void fireAxis(const String& axisName);
};


template<typename Class>
void CInput::bindAxis(const String& axisName, Class* object, typename MethodDelegate<Class>::FMethodPtr func)
{
	/*std::function<void(float)> lf = [=](float val) {
		std::function<void(float)> func = std::bind(f, object);

		func(val);
	};*/

	//std::function<void(float)> func = f;

	// Binds to the handler if it exists, or creates new and binds
	axisMappings[axisName].binding.connect(sigc::mem_fun(object, func));
}

NEPHILIM_NS_END
#endif // NephilimRazerCInput_h__
