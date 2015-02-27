#include <Nephilim/AngelScriptEXT/ASXRegistrationAI.h>
#include <Nephilim/AngelScriptEXT/ASXEngine.h>
#include <Nephilim/Foundation/Logging.h>


/*
#include <Nephilim/AI/WaypointPath.h>

#include <angelscript.h>

NEPHILIM_NS_BEGIN

void registerAIASX(ASXEngine& engine)
{	
	engine.registerClassRef<WaypointPath>("WaypointPath");

	engine.get()->RegisterObjectMethod("WaypointPath", "void add(vec2)", asMETHODPR(WaypointPath, add, (vec2), void), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("WaypointPath", "void add(vec3)", asMETHODPR(WaypointPath, add, (vec3), void), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("WaypointPath", "void add(float,float)", asMETHODPR(WaypointPath, add, (float,float), void), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("WaypointPath", "void add(float,float,float)", asMETHODPR(WaypointPath, add, (float,float,float), void), asCALL_THISCALL);
	
	engine.get()->RegisterObjectMethod("WaypointPath", "vec3 getWaypoint(int)", asMETHOD(WaypointPath, getWaypoint), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("WaypointPath", "uint size()", asMETHOD(WaypointPath, size), asCALL_THISCALL);
}

NEPHILIM_NS_END*/