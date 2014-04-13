#ifndef NephilimASXFunction_h__
#define NephilimASXFunction_h__

#include "Platform.h"
#include "Strings.h"
#include "ASXRuntime.h"

class asIScriptFunction;

NEPHILIM_NS_BEGIN

class ASXEngine;
class ASXRuntime;
class ASXModule;

class NEPHILIM_API ASXFunction
{
public:
	ASXFunction();

	void prepare();
	void call();
	void callOnObject(void* ptr);

	asIScriptFunction* mFunction;
	ASXRuntime*        mRuntime;
	bool mPrepared;
};

/*
class NEPHILIM_API ASXFunctionBase
{
public:
	ASXFunctionBase();
	ASXFunctionBase(ASXModule& module, ASXRuntime& runtime, const String& function);

	void call();

	

	void prepare();

	float getFloatReturn();
	int getIntReturn();
	void* getObjectReturn();

	void setFloatArgument(int index, float arg);
	void setIntArgument(int index, int arg);

protected:
	asIScriptFunction* m_function;
	ASXRuntime*			m_runtime;
	bool				m_prepared;
};

template<class T>
T fetchReturnValue(ASXFunctionBase* func)
{
	return static_cast<T>(func->getObjectReturn());
}

template<>
float fetchReturnValue<float>(ASXFunctionBase* func)
{
	return func->getFloatReturn();
}

template<>
int fetchReturnValue<int>(ASXFunctionBase* func)
{
	return func->getIntReturn();
}

template<class T>
void setArgument(int index, T arg, ASXFunctionBase* func)
{

}

template<>
void setArgument<float>(int index, float arg, ASXFunctionBase* func)
{
	func->setFloatArgument(index, arg);
}

template<>
void setArgument<int>(int index, int arg, ASXFunctionBase* func)
{
	func->setIntArgument(index, arg);
}

template<class R, class T1=void, class T2=void, class T3=void>
class ASXFunction : public ASXFunctionBase
{
public:
	ASXFunction() : ASXFunctionBase(){}
	ASXFunction(ASXModule& module, ASXRuntime& runtime, const String& function) : ASXFunctionBase(module, runtime, function){}

	R operator()()
	{
		m_runtime->pushState();
		call();
		R ret = static_cast<R>(fetchReturnValue<R>(this));
		m_runtime->popState();
		return ret;
	}

	R operator()(T1 arg0)
	{
		m_runtime->pushState();
		prepare();
		setArgument<T1>(0, arg0, this);
		call();
		R ret = static_cast<R>(fetchReturnValue<R>(this));
		m_runtime->popState();
		return ret;
	}

	R operator()(T1 arg0, T2 arg1)
	{
		m_runtime->pushState();
		prepare();
		setArgument<T1>(0, arg0, this);
		setArgument<T2>(1, arg1, this);
		call();
		R ret = static_cast<R>(fetchReturnValue<R>(this));
		m_runtime->popState();
		return ret;
	}

	R operator()(T1 arg0, T2 arg1, T3 arg2)
	{
		m_runtime->pushState();
		prepare();
		setArgument<T1>(0, arg0, this);
		setArgument<T2>(1, arg1, this);
		setArgument<T3>(2, arg2, this);
		call();
		R ret = static_cast<R>(fetchReturnValue<R>(this));
		m_runtime->popState();
		return ret;
	}
};

template<class T1, class T2, class T3>
class ASXFunction<void, T1, T2, T3> : public ASXFunctionBase
{
public:
	ASXFunction() : ASXFunctionBase(){}
	ASXFunction(ASXModule& module, ASXRuntime& runtime, const String& function) : ASXFunctionBase(module, runtime, function){}

	void operator()()
	{
		//printf("calling a void returner\n");
	}
};
*/
NEPHILIM_NS_END
#endif // NephilimASXFunction_h__
