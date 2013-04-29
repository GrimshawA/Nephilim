#include "Nephilim/ASEngine.h"
#include "Nephilim/Kinesis.h"
#include "AS/aswrappedcall.h"

#include <stdio.h>
#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

KxScene* KWFactory()
{
	// Initialize the pre-allocated memory by calling the
	// object constructor with the placement-new operator
	return new KxScene();
}

void KWAddRef(void *memory)
{

}

void KWRelease(void* memory){

}

/// Exports physics functionality
bool ASEngine::exportKinesis(){
	int r;
	exportReferenceDataType("KinesisBodyActor");
	asEngine->RegisterObjectType("KinesisWorld", sizeof(KxScene), asOBJ_REF);

	/*asEngine->RegisterObjectMethod("KinesisBodyActor", "Vec2f getPosition()", asMETHOD(KinesisBodyActor, getPosition), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("KinesisBodyActor", "void setVelocity(Vec2f)", asMETHOD(KinesisBodyActor, setVelocity), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("KinesisBodyActor", "Vec2f getVelocity()", asMETHOD(KinesisBodyActor, getVelocity), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("KinesisBodyActor", "void setAngle(float)", asMETHOD(KinesisBodyActor, setAngle), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("KinesisBodyActor", "void setFixedRotation(bool)", asMETHOD(KinesisBodyActor, setFixedRotation), asCALL_THISCALL);*/



	exportReferenceDataType("b2PrismaticJointDef");






	// Registering the factory behaviour
	if(getPortableMode()){
		r = asEngine->RegisterObjectBehaviour("KinesisWorld", asBEHAVE_FACTORY, "KinesisWorld@ f()", WRAP_FN(KWFactory), asCALL_GENERIC); if(r < 0)printf("r %d", r);
		r = asEngine->RegisterObjectBehaviour("KinesisWorld", asBEHAVE_ADDREF, "void f()", WRAP_FN(KWAddRef), asCALL_GENERIC); if(r < 0)printf("r %d", r);
		r = asEngine->RegisterObjectBehaviour("KinesisWorld", asBEHAVE_RELEASE, "void f()", WRAP_FN(KWRelease), asCALL_GENERIC); if(r < 0)printf("r %d", r);

		r = asEngine->RegisterObjectMethod("KinesisWorld", "void update(float)", WRAP_MFN(KxScene,update), asCALL_GENERIC); if(r < 0)printf("r %d", r);
		r = asEngine->RegisterObjectMethod("KinesisWorld", "void createStaticBox(float, float, float, float)", WRAP_MFN(KxScene,CreateStaticBox), asCALL_GENERIC); if(r < 0)printf("r %d", r);
		r = asEngine->RegisterObjectMethod("KinesisWorld", "KinesisBodyActor@ createDynamicBox(float, float, float, float)", WRAP_MFN(KxScene,CreateQuickBox), asCALL_GENERIC); if(r < 0)printf("r %d", r);
		//r = asEngine->RegisterObjectMethod("KinesisWorld", "void destroyBody(KinesisBodyActor@)", asMETHOD(KinesisWorld,destroyBodyActor), asCALL_GENERIC); if(r < 0)printf("r %d", r);

		/*if(exportedRenderer)
			r = asEngine->RegisterObjectMethod("KinesisWorld", "void draw(Renderer@)", WRAP_MFN(KinesisWorld, drawDebugShapes), asCALL_GENERIC);*/

	}
	else{
		r = asEngine->RegisterObjectBehaviour("KinesisWorld", asBEHAVE_FACTORY, "KinesisWorld@ f()", asFUNCTION(KWFactory), asCALL_CDECL); if(r < 0)printf("r %d", r);
		r = asEngine->RegisterObjectBehaviour("KinesisWorld", asBEHAVE_ADDREF, "void f()", asFUNCTION(KWAddRef), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);
		r = asEngine->RegisterObjectBehaviour("KinesisWorld", asBEHAVE_RELEASE, "void f()", asFUNCTION(KWRelease), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);

		r = asEngine->RegisterObjectMethod("KinesisWorld", "void update(float)", asMETHOD(KxScene,update), asCALL_THISCALL); if(r < 0)printf("r %d", r);
		r = asEngine->RegisterObjectMethod("KinesisWorld", "void createStaticBox(float, float, float, float)", asMETHOD(KxScene,CreateStaticBox), asCALL_THISCALL); if(r < 0)printf("r %d", r);
		r = asEngine->RegisterObjectMethod("KinesisWorld", "KinesisBodyActor@ createDynamicBox(float, float, float, float)", asMETHOD(KxScene,CreateQuickBox), asCALL_THISCALL); if(r < 0)printf("r %d", r);
		//r = asEngine->RegisterObjectMethod("KinesisWorld", "void destroyBody(KinesisBodyActor@)", asMETHOD(KinesisWorld,destroyBodyActor), asCALL_THISCALL); if(r < 0)printf("r %d", r);


		/*if(exportedRenderer)
			r = asEngine->RegisterObjectMethod("KinesisWorld", "void draw(Renderer@)", asMETHOD(KinesisWorld, drawDebugShapes), asCALL_THISCALL);*/
	}


	/*if(exportedRenderer)
		r = asEngine->RegisterObjectMethod("KinesisWorld", "void drawDebug(SceneRenderer& inout)", asMETHOD(KinesisWorld,drawDebug), asCALL_THISCALL); if(r < 0)printf("r %d", r);;
*/
	exportedKinesis = true;
	return true;
}

NEPHILIM_NS_END
