#include "Nephilim/ASEngine.h"
#include "Nephilim/AnimationFactory.h"
#include "Nephilim/AnimationPosition.h"

#include <AS/aswrappedcall.h>

PARABOLA_NAMESPACE_BEGIN

AnimationFactory& AnimationFactoryFactory(){
	return *new AnimationFactory();
}

AnimationPosition& AnimationPositionFactory(){
	return *new AnimationPosition();
}



/// Exports animation support
bool ASEngine::exportAnimations(){

	asEngine->RegisterObjectType("AnimationFactory", sizeof(AnimationFactory), asOBJ_REF);

	if (strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY")){

		asEngine->RegisterObjectBehaviour("AnimationFactory", asBEHAVE_FACTORY, "AnimationFactory@ f()", WRAP_FN(AnimationFactoryFactory), asCALL_GENERIC);
		asEngine->RegisterObjectBehaviour("AnimationFactory", asBEHAVE_ADDREF, "void f()", WRAP_MFN(RefCountable, addReference), asCALL_GENERIC);
		asEngine->RegisterObjectBehaviour("AnimationFactory", asBEHAVE_RELEASE, "void f()", WRAP_MFN(RefCountable, removeReference), asCALL_GENERIC);


		//asEngine->RegisterObjectMethod("AnimationFactory", "void addAnimation(AnimationPosition& inout)", WRAP_MFN(AnimationFactory, addAnimation), asCALL_GENERIC);
		asEngine->RegisterObjectMethod("AnimationFactory", "void moveElementTo(RocketElement@,float,float,float)", WRAP_MFN(AnimationFactory, moveRocketElementTo), asCALL_GENERIC);
		asEngine->RegisterObjectMethod("AnimationFactory", "void resizeElementTo(RocketElement@,float,float,float)", WRAP_MFN(AnimationFactory, resizeRocketElementTo), asCALL_GENERIC);
		asEngine->RegisterObjectMethod("AnimationFactory", "void addElementContent(RocketElement@,const string &in, float)", WRAP_MFN(AnimationFactory, addRocketElementContent), asCALL_GENERIC);


	}
	else{
		/*asEngine->RegisterObjectType("AnimationPosition", sizeof(AnimationPosition), asOBJ_REF);

		asEngine->RegisterObjectBehaviour("AnimationPosition", asBEHAVE_FACTORY, "AnimationPosition@ f()", asFUNCTION(AnimationPositionFactory), asCALL_CDECL);
		asEngine->RegisterObjectBehaviour("AnimationPosition", asBEHAVE_ADDREF, "void f()", asMETHOD(RefCountable, addReference), asCALL_THISCALL);
		asEngine->RegisterObjectBehaviour("AnimationPosition", asBEHAVE_RELEASE, "void f()", asMETHOD(RefCountable, removeReference), asCALL_THISCALL);

		asEngine->RegisterObjectMethod("AnimationPosition", "void setDestination(float,float)", asMETHOD(AnimationPosition, setDestination), asCALL_THISCALL);
		asEngine->RegisterObjectMethod("AnimationPosition", "void setDuration(float)", asMETHOD(AnimationPosition, setDuration), asCALL_THISCALL);
		*/



		

		asEngine->RegisterObjectBehaviour("AnimationFactory", asBEHAVE_FACTORY, "AnimationFactory@ f()", asFUNCTION(AnimationFactoryFactory), asCALL_CDECL);
		asEngine->RegisterObjectBehaviour("AnimationFactory", asBEHAVE_ADDREF, "void f()", asMETHOD(RefCountable, addReference), asCALL_THISCALL);
		asEngine->RegisterObjectBehaviour("AnimationFactory", asBEHAVE_RELEASE, "void f()", asMETHOD(RefCountable, removeReference), asCALL_THISCALL);

	//	asEngine->RegisterObjectMethod("AnimationFactory", "void addAnimation(AnimationPosition& inout)", asMETHOD(AnimationFactory, addAnimation), asCALL_THISCALL);
		asEngine->RegisterObjectMethod("AnimationFactory", "void moveElementTo(RocketElement@,float,float,float)", asMETHOD(AnimationFactory, moveRocketElementTo), asCALL_THISCALL);
		asEngine->RegisterObjectMethod("AnimationFactory", "void resizeElementTo(RocketElement@,float,float,float)", asMETHOD(AnimationFactory, resizeRocketElementTo), asCALL_THISCALL);
		asEngine->RegisterObjectMethod("AnimationFactory", "void addElementContent(RocketElement@,const string &in, float)", asMETHOD(AnimationFactory, addRocketElementContent), asCALL_THISCALL);

		/*asEngine->RegisterObjectType("AnimationPosition", sizeof(AnimationPosition), asOBJ_REF);

		asEngine->RegisterObjectBehaviour("AnimationPosition", asBEHAVE_FACTORY, "AnimationPosition@ f()", asFUNCTION(AnimationPositionFactory), asCALL_CDECL);
		asEngine->RegisterObjectBehaviour("AnimationPosition", asBEHAVE_ADDREF, "void f()", asMETHOD(RefCountable, addReference), asCALL_THISCALL);
		asEngine->RegisterObjectBehaviour("AnimationPosition", asBEHAVE_RELEASE, "void f()", asMETHOD(RefCountable, removeReference), asCALL_THISCALL);

		asEngine->RegisterObjectMethod("AnimationPosition", "void setDestination(float,float)", asMETHOD(AnimationPosition, setDestination), asCALL_THISCALL);
		asEngine->RegisterObjectMethod("AnimationPosition", "void setDuration(float)", asMETHOD(AnimationPosition, setDuration), asCALL_THISCALL);
	*/}

	return true;
};

PARABOLA_NAMESPACE_END