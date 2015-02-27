#include <Nephilim/AngelScriptEXT/ASXRegistrationResources.h>
#include <Nephilim/AngelScriptEXT/ASXEngine.h>
#include <Nephilim/Foundation/Logging.h>
#include <Nephilim/Graphics/GL/GLTexture.h>

#include <angelscript.h>


NEPHILIM_NS_BEGIN

namespace
{
	void dummy()
	{
	}
};

void registerResourcesASX(ASXEngine& engine)
{
	engine.get()->RegisterObjectType("Texture2D", sizeof(Texture), asOBJ_REF);

	engine.get()->RegisterObjectBehaviour("Texture2D", asBEHAVE_ADDREF, "void f()", asFUNCTION(dummy), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectBehaviour("Texture2D", asBEHAVE_RELEASE, "void f()", asFUNCTION(dummy), asCALL_CDECL_OBJLAST);

	engine.get()->RegisterObjectMethod("Texture2D", "void setRepeated(bool)", asMETHOD(Texture, setRepeated), asCALL_THISCALL);

}

NEPHILIM_NS_END