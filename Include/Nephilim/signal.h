#ifndef signal_h__
#define signal_h__

template<typename T_ret, typename arg0T=void, typename arg1T=void, typename arg2T=void, typename arg3T=void>
class signal
{
public:
	
};

typedef signal<void> signal0;

class sig
{
public:

	void operator+=( void (*fn)(void))
	{
		funcs.push_back(fn);
	}

	void operator()()
	{
		for(auto it = funcs.begin(); it != funcs.end(); it++)
		{
			(*it)();
		}
	}

	typedef void (*fn)(void);

	std::vector<fn> funcs;
};

#endif // signal_h__
