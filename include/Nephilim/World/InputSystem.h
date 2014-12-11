#ifndef NephilimInputSystem_h__
#define NephilimInputSystem_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>
#include <Nephilim/Event.h>
#include <Nephilim/World/System.h>
#include <Nephilim/World/CInput.h>

NEPHILIM_NS_BEGIN

/**
\class InputBindingSheet
\brief This structure maps keys to actions, so they are dispatched through the input system
*/
class NEPHILIM_API InputBindingSheet
{
public:

	/// One action trigger is a key or other type of input button that will
	/// trigger an action
	struct ActionTrigger
	{
		Keyboard::Key key;
	};

	/// A named action with multiple possible triggers
	struct ActionMapping
	{
		String actionName;
		std::vector<ActionTrigger> triggers;

		bool isTriggeredBy(Keyboard::Key key)
		{
			for (auto i = 0; i < triggers.size(); ++i)
			{
				if (triggers[i].key == key)
					return true;
			}
			return false;
		}
	};

	struct AxisMapping
	{

	};

	std::vector<ActionMapping> actionMappings;

public:

	/// Add a new action name to the list
	void addAction(const String& actionName);

	/// Bind a new key to a given action
	void addTriggerKey(const String& action, Keyboard::Key k);

};

/**
	\class InputSystem
	\brief 
*/
class NEPHILIM_API InputSystem : public System
{
public:

	/// Emit an action into the world
	void emitAction(const String& name, CInput::ActionModes mode);

	/// Push an event into the input system
	void updateWithEvent(const Event& event);

	/// Our key binding sheet to translate real input into action based input
	InputBindingSheet bindings;
};

NEPHILIM_NS_END
#endif // NephilimInputSystem_h__
