#include <Nephilim/Foundation/Extension.h>
using namespace nx;

#include "FbxPlugin.h"

extern "C"
{
	Object __declspec(dllexport) *CreateInstance()
	{
		return new NephilimFbxPlugin();
	}

};