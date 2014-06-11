#include <Nephilim/ASX/ASXRegistrationCollision.h>
#include <Nephilim/ASXEngine.h>
#include <Nephilim/Logger.h>
#include <Nephilim/CollisionData.h>

#include <angelscript.h>

NEPHILIM_NS_BEGIN

class CollisionDataScript : public CollisionData
{
public:
	int mReferences;
};

CollisionDataScript* CollisionDataInstancer()
{
	CollisionDataScript* cdata = new CollisionDataScript();
	cdata->mReferences = 1;
	return cdata;
}

void CollisionDataAddRef(CollisionDataScript* obj)
{
	obj->mReferences ++;
}

void CollisionDataReleaseRef(CollisionDataScript* obj)
{
	obj->mReferences --;
	if(obj->mReferences == 0)
	{
		delete obj;
	}
}

void registerCollisionASX(ASXEngine& engine)
{
	engine.get()->RegisterObjectType("CollisionData", sizeof(CollisionDataScript), asOBJ_REF);

	engine.get()->RegisterObjectBehaviour("CollisionData", asBEHAVE_FACTORY, "CollisionData@ f()", asFUNCTION(CollisionDataInstancer), asCALL_CDECL);
	engine.get()->RegisterObjectBehaviour("CollisionData", asBEHAVE_ADDREF, "void f()", asFUNCTION(CollisionDataAddRef), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectBehaviour("CollisionData", asBEHAVE_RELEASE, "void f()", asFUNCTION(CollisionDataReleaseRef), asCALL_CDECL_OBJLAST);

	//engine.get()->RegisterObjectMethod("CollisionData", "bool open(const string& in)", asMETHODPR(ScriptFile, open, (const String&), bool), asCALL_THISCALL);
}

NEPHILIM_NS_END