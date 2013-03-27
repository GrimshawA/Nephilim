#ifndef SCRIPTENGINENATIVECOMMANDS_H
#define SCRIPTENGINENATIVECOMMANDS_H

#include "Platform.h"
#include "ScriptEngineTask.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Scripting
	\class EchoTask
	\brief Just prints the arguments to the console

	\todo Move to Sources, not useful in here
*/
class PARABOLA_API EchoTask : public ScriptEngineTask{
public:
	/// Run the task
	void run(const String &calledAs, String arguments);
};

class PARABOLA_API GetHttpTask : public ScriptEngineTask{
public:
	/// Run the task
	void run(const String &calledAs, String arguments);
};

class PARABOLA_API ParseTask : public ScriptEngineTask{
public:
	/// Run the task
	void run(const String &calledAs, String arguments);
};

PARABOLA_NAMESPACE_END
#endif