#include <Nephilim/ASX/ASXRegistrationRazer.h>
#include <Nephilim/ASXEngine.h>

#include <Nephilim/Tilemap.h>


#include <Nephilim/Razer/ComponentMesh.h>
#include <Nephilim/Razer/ComponentTilemap2D.h>
#include <Nephilim/Razer/ComponentTransform.h>
#include <Nephilim/Razer/ComponentSprite.h>

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


	// Register the level 2D component
	engine.get()->RegisterObjectType("Tilemap2D", sizeof(ComponentTilemap2D), asOBJ_REF);

	engine.get()->RegisterObjectBehaviour("Tilemap2D", asBEHAVE_ADDREF, "void f()", asFUNCTION(dummy), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectBehaviour("Tilemap2D", asBEHAVE_RELEASE, "void f()", asFUNCTION(dummy), asCALL_CDECL_OBJLAST);

	engine.get()->RegisterObjectMethod("Tilemap2D", "bool load(const string& in)", asMETHOD(ComponentTilemap2D, load), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("Tilemap2D", "void useCubes(bool)", asMETHOD(ComponentTilemap2D, useCubes), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("Tilemap2D", "void setSideView(bool)", asMETHOD(ComponentTilemap2D, setSideView), asCALL_THISCALL);
	//engine.get()->RegisterObjectMethod("Tilemap2D", "void getTileShape(int, float& out, float& out, float& out, float& out)", asMETHOD(ComponentTilemap2D, getTileShape), asCALL_THISCALL);

	//////////////////////////////////////////////////////////////////////////

	engine.get()->RegisterObjectType("Transform", sizeof(ComponentTransform), asOBJ_REF);

	engine.get()->RegisterObjectBehaviour("Transform", asBEHAVE_ADDREF, "void f()", asFUNCTION(dummy), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectBehaviour("Transform", asBEHAVE_RELEASE, "void f()", asFUNCTION(dummy), asCALL_CDECL_OBJLAST);

	engine.get()->RegisterObjectProperty("Transform", "float x", asOFFSET(ComponentTransform, position.x));
	engine.get()->RegisterObjectProperty("Transform", "float y", asOFFSET(ComponentTransform, position.y));
	engine.get()->RegisterObjectProperty("Transform", "float z", asOFFSET(ComponentTransform, position.z));
	engine.get()->RegisterObjectProperty("Transform", "Quaternion q", asOFFSET(ComponentTransform, rotation));

	// Basic transform functions
	engine.get()->RegisterObjectMethod("Transform", "void setPosition(const vec3& in)", asMETHODPR(ComponentTransform, setPosition, (const vec3&), void), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("Transform", "void setPosition(const vec2& in)", asMETHODPR(ComponentTransform, setPosition, (const vec2&), void), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("Transform", "void setPosition(float,float,float)", asMETHODPR(ComponentTransform, setPosition, (float,float,float), void), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("Transform", "void setPosition(float,float)", asMETHODPR(ComponentTransform, setPosition, (float,float), void), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("Transform", "vec3 getPosition()", asMETHOD(ComponentTransform, getPosition), asCALL_THISCALL);
	
	engine.get()->RegisterObjectMethod("Transform", "void rotate(float,float,float)", asMETHOD(ComponentTransform, rotateByEulerAngles), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("Transform", "void rotateAxisAngle(float,float,float, float)", asMETHOD(ComponentTransform, rotateByAxisAngle), asCALL_THISCALL);

	engine.get()->RegisterObjectMethod("Transform", "vec3 getForwardVector()", asMETHOD(ComponentTransform, getForwardVector), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("Transform", "vec3 getRightVector()", asMETHOD(ComponentTransform, getRightVector), asCALL_THISCALL);


	////////////////////////////////////////////////////////////////////////// Sprite


	engine.get()->RegisterObjectType("Sprite", sizeof(ComponentSprite), asOBJ_REF);

	engine.get()->RegisterObjectBehaviour("Sprite", asBEHAVE_ADDREF, "void f()", asFUNCTION(dummy), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectBehaviour("Sprite", asBEHAVE_RELEASE, "void f()", asFUNCTION(dummy), asCALL_CDECL_OBJLAST);

	engine.get()->RegisterObjectMethod("Sprite", "void setSize(const vec2& in)", asMETHODPR(ComponentSprite, setSize, (const vec2&), void), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("Sprite", "void setSize(float, float)", asMETHODPR(ComponentSprite, setSize, (float,float), void), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("Sprite", "vec2 getSize()", asMETHOD(ComponentSprite, getSize), asCALL_THISCALL);

	engine.get()->RegisterObjectProperty("Sprite", "float width", asOFFSET(ComponentSprite, width));
	engine.get()->RegisterObjectProperty("Sprite", "float height", asOFFSET(ComponentSprite, height));
	engine.get()->RegisterObjectProperty("Sprite", "string texture", asOFFSET(ComponentSprite, tex));
	engine.get()->RegisterObjectProperty("Sprite", "vec2 texRectPos", asOFFSET(ComponentSprite, tex_rect_pos));
	engine.get()->RegisterObjectProperty("Sprite", "vec2 texRectSize", asOFFSET(ComponentSprite, tex_rect_size));
	engine.get()->RegisterObjectProperty("Sprite", "vec2 scale", asOFFSET(ComponentSprite, scale));

}

NEPHILIM_NS_END