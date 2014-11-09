#include <Nephilim/Razer/ComponentScript.h>
/*
#include <Nephilim/ASXFunction.h>
#include <Nephilim/Logger.h>


NEPHILIM_NS_BEGIN
namespace rzr
{
	
bool ComponentScript::load(const String& className)
{
	mClassName = className;
	return false;
}

void ComponentScript::update()
{
	if(mModule)
	{
		asIObjectType* BehaviorClassType = mModule.get()->GetObjectTypeByName(mClassName);

		ASXFunction UpdateFunction;
		UpdateFunction.mRuntime = mRuntime;
		UpdateFunction.mFunction = BehaviorClassType->GetMethodByDecl("void Update()");
		UpdateFunction.callOnObject(mScriptInstance);

		//Log("Script function is being called");
	}
}

};


NEPHILIM_NS_END

*/