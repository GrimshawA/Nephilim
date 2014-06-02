#include <Nephilim/ASX/ASXRegistrationMath.h>
#include <Nephilim/ASXEngine.h>
#include <Nephilim/Quaternion.h>

#include <angelscript.h>

NEPHILIM_NS_BEGIN
	
void QuaternionDefaultConstructor(void* memory)
{
	new(memory) Quaternion();
}

void QuaternionConstructorParams(float x, float y, float z, float w, void* memory)
{
	new(memory) Quaternion(x,y,z,w);
}

void QuaternionCopyConstructor(const Quaternion &in, void* memory)
{
	new(memory) Quaternion(in);
}

void QuaternionDestructor(void* memory)
{
	((Quaternion*)memory)->~Quaternion();
}

Quaternion QuaternionFromAxisAngle(float angle, float ax, float ay, float az)
{
	Quaternion qr;
	Quaternion::fromAxisAngle(qr, vec3(ax, ay, az), angle);
	return qr;
}

void registerMathASX(ASXEngine& engine)
{
	engine.get()->RegisterObjectType("Quaternion", sizeof(Quaternion), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK);

	engine.get()->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(QuaternionDefaultConstructor), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float x, float y, float z, float w)", asFUNCTION(QuaternionConstructorParams), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectBehaviour("Quaternion", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(QuaternionDestructor), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Quaternion &in)", asFUNCTION(QuaternionCopyConstructor), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectMethod("Quaternion", "Quaternion &opAssign(const Quaternion &in)", asMETHODPR(Quaternion, operator=, (const Quaternion &), Quaternion&), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("Quaternion", "Quaternion opMul(const Quaternion &in)", asMETHODPR(Quaternion, operator*, (const Quaternion &), Quaternion), asCALL_THISCALL);
	
	// member access
	engine.get()->RegisterObjectProperty("Quaternion", "float x", asOFFSET(Quaternion, x));
	engine.get()->RegisterObjectProperty("Quaternion", "float y", asOFFSET(Quaternion, y));
	engine.get()->RegisterObjectProperty("Quaternion", "float z", asOFFSET(Quaternion, z));
	engine.get()->RegisterObjectProperty("Quaternion", "float w", asOFFSET(Quaternion, w));

	// Utility quaternion functions
	engine.get()->RegisterGlobalFunction("Quaternion QuaternionFromAxisAngle(float,float,float,float)", asFUNCTION(QuaternionFromAxisAngle), asCALL_CDECL );
}
NEPHILIM_NS_END