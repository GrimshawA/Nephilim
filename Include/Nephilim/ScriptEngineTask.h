#ifndef PARABOLA_SCRIPTENGINETASK_H
#define PARABOLA_SCRIPTENGINETASK_H

#include "Platform.h"
#include "Strings.h"
#include "Signals.h"

PARABOLA_NAMESPACE_BEGIN

class ScriptEngine;

/**
	\ingroup Scripting
	\class ScriptEngineTask
	\brief Represents a command that can be executed by the ScriptEngine
*/
class PARABOLA_API ScriptEngineTask{
public:
	/// Creates a new task instance with reference count 0, meaning not inserted yet
	ScriptEngineTask();

	/// Removes a reference and destroys if reaches 0
	void removeReference();

	/// Implemented by all tasks, run when the task is called
	virtual void run(const String &calledAs, String arguments) = 0;

protected:
	ScriptEngine *myParent;

private:
	friend class ScriptEngine;	

	int refCount;
	bool enabled;
};

/**
	\ingroup Scripting
	\class ScriptEngineTaskGeneric
	\brief A task that can point to any function

	You can easily create tasks without the harassment of inheriting ScriptEngineTask.

	Just do something like this from within your game:
	\code
		ScriptEngineTaskGeneric *task = new ScriptEngineTaskGeneric();
		task->onCall.connect(...);
		this->scriptEngine().registerTask(String("my_task_name"), task);
	\endcode

	Please notice where i put the '...' , there you make a slot to your function,
	as you can guide yourself from libsigc++ documentation or the Signals documentation
	of the engine for a small overview.

	\warning Important: The functions you connect to this signal must be in the way of 
	\warning void myFunc(String, String)

	And you can immediately call your new task, and the function you specified is called.
*/
class PARABOLA_API ScriptEngineTaskGeneric : public ScriptEngineTask{
public:
	/// The signal to be fired when the command is called
	sigc::signal<void, String, String> onCall;

	/// Run the task
	void run(const String &calledAs, String arguments);
};

PARABOLA_NAMESPACE_END
#endif