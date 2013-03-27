#ifndef PARABOLA_AS_SCRIPT_H
#define PARABOLA_AS_SCRIPT_H

#include "Platform.h"
#include "angelscript.h"
#include "FileStream.h"
#include "StringID.h"

#include <map>

PARABOLA_NAMESPACE_BEGIN
class ASEngine;

namespace ScriptArgumentTypes{
	enum ArgTypes{
		None = 0,
		Float,
		Double,
		Ptr,
		Object,
		Byte,
		DWord,
		QWord,
		Word
	};
}

/**
	\ingroup Scripting
	\class ASScript
	\brief Represents one script in a ASEngine.

	This is an utility class to provide really efficient access to script functions.

	You can even have a rendering function, calling every frame, fast enough to work well in a game.
	
*/
class PARABOLA_API ASScript{
public:
	/// Creates a yet empty script, not meant to be instantiated by other than the AS Engine
	ASScript();
	/// Safely destruct the script
	virtual ~ASScript();

	/// Prepare the context to call the function with the selected id
	bool prepareMethod(int funcid);

	/// Prepare the context to call 
	bool prepareMethod(const String &funcName);

	/// Pass an argument to the function
	/// \param index must be filled with the argument index in the remote function
	/// \param data must point to the address of the argument to be passed
	/// \param argumentType must be a valid exportable argument type.
	/// Use with care, incorrect use may lead to crashes.
	void prepareMethodArgument(int index, void* data, ScriptArgumentTypes::ArgTypes argumentType);

	/// Give a limited time to the function execution.
	void prepareMethodTimeout(float timeoutSeconds);

	/// Get function id by its name
	//int getFunctionIdByName(const String &name);

	/// Call an already prepared context
	/// Returns whether the execution was successful.
	/// If you want the return value, pass your object address and specify the type you want to get.
	/// Be careful when using the return values, incorrect use may cause crashes.
	bool call(void *data = NULL, ScriptArgumentTypes::ArgTypes returnType = ScriptArgumentTypes::None);

	/// Call immediately the selected function
	bool call(const String &funcName);

	/// Call the selected function right away
	bool call(int funcid);

	template<typename Ret>
	Ret fastCall(const String& funcName);

	/// Get the last return value, if the context is still alive
	/// Otherwise it returns NULL.
	/// Once again, be careful when casting the void* to the right object.
	void* getReturnValue(ScriptArgumentTypes::ArgTypes returnType);

	/// Request the context to be created, if not already created
	void requestContext();

	/// Enable/Disable the destruction of the script context.
	/// When disabled, the script state is preserved between calls, like global variables.
	/// Otherwise, you will be always calling a fresh script
	void enableContextDestruction(bool enabled);

	/// Destroy the context.
	void releaseContext();

	/// Clears the function cache (optimization, internal use)
	void clearCache();

	/// Compile additional code to this script
	void compileCode(const char* code, const String &sectionName);

	/// Get the module of this script
	asIScriptModule* getModule();

private:
	friend class ASEngine;

	ASEngine *myParent;
	asIScriptModule *myModule;
	asIScriptContext *myExecutionContext;
	bool myEnableContextDestruction;
	std::map<StringID, int> myFunctionCache;
	String myScriptName;
	String myPath;
	// Preparation
	bool myCallPending;
	int myPreparedMethod;
	bool myPreserveGlobals;
};

template<typename Ret>
Ret ASScript::fastCall(const String& funcName)
{
	Ret val;
	if(call(funcName))
	{
		void* ret = getReturnValue(ScriptArgumentTypes::Object);
		if(ret)
		{
			Ret* retTypePtr = (Ret*)ret;
			val = *retTypePtr;
		}
		
	}
	return val;
}

/**
	\ingroup Scripting
	\class ASBinaryStream
	\brief Implementation of the AngelScript binary stream.

	Used to read/write byte code to files.
*//*
class PARABOLA_API ASBinaryStream : public asIBinaryStream{
public:
	/// Initializes the stream on the desired script
	ASBinaryStream(const String &fileName, IODevice::OpenModes openMode);

	/// Writes data to the stream
	void Write(const void *ptr, asUINT size);

	/// Reads data from the stream
	void Read(void *ptr, asUINT size);

private:
	FileStream stream;
};
*/
PARABOLA_NAMESPACE_END
#endif