#ifndef Callback_h__
#define Callback_h__

#include "Platform.h"

#include <vector>

NEPHILIM_NS_BEGIN

struct nil;

class NEPHILIM_API base_slot
{

};

class NEPHILIM_API base_signal
{
public:
	std::vector<base_slot*> m_slots;
};

template<typename R, typename T1=nil, typename T2=nil, typename T3=nil>
class NEPHILIM_API signal
{
public:

	R operator()(T1 arg0)
	{
		R ret = 0;
		return ret;
	}

	R operator()(T1 arg0, T2 arg1)
	{
		R ret = 0;
		return ret;
	}

	R operator()(T1 arg0, T2 arg1, T3 arg2)
	{
		R ret = 0;
		return ret;
	}

};

template<typename T1, typename T2, typename T3>
class NEPHILIM_API signal<void, T1,T2,T3>
{
public:

	void operator()(T1 arg0)
	{
	
	}

	void operator()(T1 arg0, T2 arg1)
	{
		
	}

	void operator()(T1 arg0, T2 arg1, T3 arg2)
	{
		
	}

	typedef void (*fnptr)(T1);
	void connect(fnptr ptr)
	{
		ptr(4);
	}
};

NEPHILIM_NS_END

#endif // Callback_h__
