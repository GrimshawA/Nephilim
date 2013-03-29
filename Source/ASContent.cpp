#ifndef MINIMAL_BUILD

#include "Nephilim/ASEngine.h"
#include "Nephilim/Content.h"

NEPHILIM_NS_BEGIN

ContentBank* CBConstructor()
{
	// Initialize the pre-allocated memory by calling the
	// object constructor with the placement-new operator
	return new ContentBank();
}

void CBDestructor(void *memory)
{
	
}

/// Exports the content banks
bool ASEngine::exportContentBanks(){
	asEngine->RegisterObjectType("ContentBank", sizeof(ContentBank), asOBJ_REF);

	int r;
	// Register the behaviours
	r = asEngine->RegisterObjectBehaviour("ContentBank", asBEHAVE_FACTORY, "ContentBank@ f()", asFUNCTION(CBConstructor), asCALL_CDECL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("ContentBank", asBEHAVE_ADDREF, "void f()", asFUNCTION(CBConstructor), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("ContentBank", asBEHAVE_RELEASE, "void f()", asFUNCTION(CBDestructor), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);

	r = asEngine->RegisterObjectMethod("ContentBank", "Texture@ createTexture(const string &in, const string & in)", asMETHOD(ContentBank,createTexture), asCALL_THISCALL); if(r < 0)printf("r %d", r);;
	r = asEngine->RegisterObjectMethod("ContentBank", "void createSoundBuffer(const string &in)", asMETHOD(ContentBank,createSoundBuffer), asCALL_THISCALL); if(r < 0)printf("r %d", r);;
	
	//r = asEngine->RegisterObjectMethod("KinesisWorld", "void createStaticBox(float, float, float, float)", asMETHOD(KinesisWorld,CreateStaticBox), asCALL_THISCALL); if(r < 0)printf("r %d", r);;
	//r = asEngine->RegisterObjectMethod("KinesisWorld", "void createDynamicBox(float, float, float, float)", asMETHOD(KinesisWorld,CreateQuickBox), asCALL_THISCALL); if(r < 0)printf("r %d", r);;
	
	
	exportedContentBanks = true;

	return true;
};

NEPHILIM_NS_END
#endif