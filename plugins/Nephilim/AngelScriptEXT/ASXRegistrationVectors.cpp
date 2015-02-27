#include <Nephilim/Extensions/PluginSDK.h>
#include <Nephilim/AngelScriptEXT/ASXRegistrationVectors.h>
#include <Nephilim/AngelScriptEXT/ASXEngine.h>
#include <Nephilim/Foundation/Vector.h>

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

//////////////////////////////////////////////////////////////////////////

void Vec3fCTOR(void* memory)
{
	new(memory) vec3();
}
void Vec3fCTOR2(float x, float y, float z, void* memory)
{
	new(memory) vec3(x, y, z);
}
void Vec3fCCTOR(const vec3 &in, void* memory)
{
	new(memory) vec3(in);
}
void Vec3fDTOR(void* memory)
{
	((vec3*)memory)->~vec3();
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

	//////////////////////////////////////////////////////////////////////////
	/// Vec3<float> as vec3
	///
	engine.get()->RegisterObjectType("vec3", sizeof(vec3), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK);

	engine.get()->RegisterObjectBehaviour("vec3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Vec3fCTOR), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectBehaviour("vec3", asBEHAVE_CONSTRUCT, "void f(float x, float y, float z)", asFUNCTION(Vec3fCTOR2), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectBehaviour("vec3", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Vec3fDTOR), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectBehaviour("vec3", asBEHAVE_CONSTRUCT, "void f(const vec3 &in)", asFUNCTION(Vec3fCCTOR), asCALL_CDECL_OBJLAST);
	

	engine.get()->RegisterObjectMethod("vec3", "vec3 opAdd(const vec3 &in)", asMETHODPR(vec3, operator+, (const vec3 &), vec3), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("vec3", "vec3 &opAddAssign(const vec3 &in)", asMETHODPR(vec3, operator+=, (const vec3 &), vec3&), asCALL_THISCALL);
	
	engine.get()->RegisterObjectMethod("vec3", "vec3 &opAssign(const vec3 &in)", asMETHODPR(vec3, operator=, (const vec3 &), vec3&), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("vec3", "vec3 opMul(const float& in)", asMETHODPR(vec3, operator*, (const float& in), vec3), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("vec3", "vec3 opSub(const vec3& in)", asMETHODPR(vec3, operator-, (const vec3& in), vec3), asCALL_THISCALL);
	
	engine.get()->RegisterObjectMethod("vec3", "float length()", asMETHOD(vec3, length), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("vec3", "float normalize()", asMETHOD(vec3, normalize), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("vec3", "float distance(const vec3& in)", asMETHOD(vec3, distance), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("vec3", "float squaredDistance(const vec3& in)", asMETHOD(vec3, squaredDistance), asCALL_THISCALL);

	engine.get()->RegisterObjectProperty("vec3", "float x", asOFFSET(vec3, x));
	engine.get()->RegisterObjectProperty("vec3", "float y", asOFFSET(vec3, y));
	engine.get()->RegisterObjectProperty("vec3", "float z", asOFFSET(vec3, z));
}

NEPHILIM_NS_END