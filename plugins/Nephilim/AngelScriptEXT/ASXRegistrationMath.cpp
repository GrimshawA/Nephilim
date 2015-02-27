#include <Nephilim/AngelScriptEXT/ASXRegistrationMath.h>
#include <Nephilim/AngelScriptEXT/ASXEngine.h>
#include <Nephilim/Foundation/Quat.h>

#include <angelscript.h>

NEPHILIM_NS_BEGIN
	
void QuaternionDefaultConstructor(void* memory)
{
	new(memory) Quat();
}

void QuaternionConstructorParams(float x, float y, float z, float w, void* memory)
{
	new(memory) Quat(x, y, z, w);
}

void QuaternionCopyConstructor(const Quat &in, void* memory)
{
	new(memory) Quat(in);
}

void QuaternionDestructor(void* memory)
{
	((Quat*)memory)->~Quat();
}

Quat QuaternionFromAxisAngle(float angle, float ax, float ay, float az)
{
	Quat qr;
	Quat::fromAxisAngle(qr, vec3(ax, ay, az), angle);
	return qr;
}

void registerMathASX(ASXEngine& engine)
{
	engine.get()->RegisterObjectType("Quaternion", sizeof(Quat), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK);

	engine.get()->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(QuaternionDefaultConstructor), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float x, float y, float z, float w)", asFUNCTION(QuaternionConstructorParams), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectBehaviour("Quaternion", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(QuaternionDestructor), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Quaternion &in)", asFUNCTION(QuaternionCopyConstructor), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectMethod("Quaternion", "Quaternion &opAssign(const Quaternion &in)", asMETHODPR(Quat, operator=, (const Quat &), Quat&), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("Quaternion", "Quaternion opMul(const Quaternion &in)", asMETHODPR(Quat, operator*, (const Quat &), Quat), asCALL_THISCALL);
	
	// member access
	engine.get()->RegisterObjectProperty("Quaternion", "float x", asOFFSET(Quat, x));
	engine.get()->RegisterObjectProperty("Quaternion", "float y", asOFFSET(Quat, y));
	engine.get()->RegisterObjectProperty("Quaternion", "float z", asOFFSET(Quat, z));
	engine.get()->RegisterObjectProperty("Quaternion", "float w", asOFFSET(Quat, w));

	// Utility quaternion functions
	engine.get()->RegisterGlobalFunction("Quaternion QuaternionFromAxisAngle(float,float,float,float)", asFUNCTION(QuaternionFromAxisAngle), asCALL_CDECL );
}
NEPHILIM_NS_END