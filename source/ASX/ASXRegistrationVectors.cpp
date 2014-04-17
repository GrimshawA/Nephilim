#include <Nephilim/ASX/ASXRegistrationVectors.h>
#include <Nephilim/ASXEngine.h>
#include <Nephilim/Vectors.h>

#include <angelscript.h>

NEPHILIM_NS_BEGIN

void Vec2fCTOR(void* memory){
		new(memory) Vec2f();
}
void Vec2fCTOR2(float x, float y, void* memory){
	new(memory) Vec2f(x,y);
}
void Vec2fCCTOR(const Vec2f &in, void* memory){
	new(memory) Vec2f(in);
}
void Vec2fDTOR(void* memory){
	((Vec2f*)memory)->~Vec2f();
}

void registerVectorsASX(ASXEngine& engine)
{
	engine.get()->RegisterObjectType("vec2", sizeof(Vec2f), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK);

	engine.get()->RegisterObjectBehaviour("vec2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Vec2fCTOR), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectBehaviour("vec2", asBEHAVE_CONSTRUCT, "void f(float x, float y)", asFUNCTION(Vec2fCTOR2), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectBehaviour("vec2", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Vec2fDTOR), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectBehaviour("vec2", asBEHAVE_CONSTRUCT, "void f(const vec2 &in)", asFUNCTION(Vec2fCCTOR), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectMethod("vec2", "vec2 &opAssign(const vec2 &in)", asMETHODPR(Vec2f, operator=, (const Vec2f &), Vec2f&), asCALL_THISCALL);

	engine.get()->RegisterObjectProperty("vec2", "float x", asOFFSET(Vec2f, x));
	engine.get()->RegisterObjectProperty("vec2", "float y", asOFFSET(Vec2f, y));
}

NEPHILIM_NS_END