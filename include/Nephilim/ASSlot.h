#ifndef ASSlot_h__
#define ASSlot_h__

#include <Nephilim/Platform.h>
#include "Signals.h"
#include "ASEngine.h"

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN
	
class ASSlot : public sigc::trackable
{
public:
	void trigger()
	{
		//cout<<"Button clicked"<<endl;
		
		if(!script->call("void " + functionName + "()"))
		{
			cout<<"Failed"<<endl<<endl<<endl;
		}
	}

	String functionName;
	ASScript* script;
};


NEPHILIM_NS_END
#endif // ASSlot_h__
