#include <Nephilim/ASX/ASXRegistrationRazer.h>
#include <Nephilim/ASXEngine.h>

#include <Nephilim/Tilemap.h>


#include <Nephilim/Razer/ComponentMesh.h>

#include <angelscript.h>

namespace
{
	void dummy()
	{		
	}
};

NEPHILIM_NS_BEGIN

using namespace rzr;

void registerRazerComponentsASX(ASXEngine& engine)
{
	// Register the mesh component
	engine.get()->RegisterObjectType("Mesh", sizeof(ComponentMesh), asOBJ_REF);

	engine.get()->RegisterObjectBehaviour("Mesh", asBEHAVE_ADDREF, "void f()", asFUNCTION(dummy), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectBehaviour("Mesh", asBEHAVE_RELEASE, "void f()", asFUNCTION(dummy), asCALL_CDECL_OBJLAST);

	engine.get()->RegisterObjectMethod("Mesh", "bool loadCubes(Tilemap@)", asMETHOD(ComponentMesh, loadCubesFromTilemap), asCALL_THISCALL);

}

NEPHILIM_NS_END