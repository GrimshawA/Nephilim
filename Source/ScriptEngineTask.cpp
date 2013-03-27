#ifndef MINIMAL_BUILD
#include "Nephilim/ScriptEngineTask.h"

PARABOLA_NAMESPACE_BEGIN
/// Creates a new task instance with reference count 0, meaning not inserted yet
ScriptEngineTask::ScriptEngineTask(){
	refCount = 0;
	enabled = true;
	myParent = NULL;
};

/// Removes a reference and destroys if reaches 0
void ScriptEngineTask::removeReference(){
	refCount --;
	if(refCount <= 0){
		delete this;
	}
};

/************************************************************************/
/*                                                                      */
/************************************************************************/
/// Run the task
void ScriptEngineTaskGeneric::run(const String &calledAs, String arguments){
	onCall.emit(calledAs, arguments);
}

PARABOLA_NAMESPACE_END
#endif