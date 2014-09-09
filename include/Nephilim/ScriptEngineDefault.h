#ifndef SCRIPTENGINENATIVECOMMANDS_H
#define SCRIPTENGINENATIVECOMMANDS_H

#include <Nephilim/Platform.h>
#include "ScriptEngineTask.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup Scripting
	\class EchoTask
	\brief Just prints the arguments to the console

	\todo Move to Sources, not useful in here
*/
class NEPHILIM_API EchoTask : public ScriptEngineTask{
public:
	/// Run the task
	void run(const String &calledAs, String arguments);
};

class NEPHILIM_API GetHttpTask : public ScriptEngineTask{
public:
	/// Run the task
	void run(const String &calledAs, String arguments);
};

class NEPHILIM_API ParseTask : public ScriptEngineTask{
public:
	/// Run the task
	void run(const String &calledAs, String arguments);
};

NEPHILIM_NS_END
#endif