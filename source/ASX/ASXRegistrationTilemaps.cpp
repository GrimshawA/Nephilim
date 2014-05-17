#include <Nephilim/ASX/ASXRegistrationTilemaps.h>
#include <Nephilim/ASXEngine.h>

#include <Nephilim/Tilemap.h>

#include <angelscript.h>

namespace
{
	void dummy()
	{		
	}
};

NEPHILIM_NS_BEGIN

class ScriptTilemap : public Tilemap
{
public:
	int mReferences;
};


ScriptTilemap* TilemapInstancer()
{
	ScriptTilemap* scriptFile = new ScriptTilemap();
	scriptFile->mReferences = 1;
	return scriptFile;
}

void TilemapAddRef(ScriptTilemap* obj)
{
	obj->mReferences ++;
}

void TilemapReleaseRef(ScriptTilemap* obj)
{
	obj->mReferences --;
	if(obj->mReferences == 0)
	{
		delete obj;
	}
}

void registerTilemapsASX(ASXEngine& engine)
{

	// Layer type enum
	engine.get()->RegisterEnum("TileLayerType");
	engine.get()->RegisterEnumValue("TileLayerType", "Tiles", Tilemap::Layer::Tiles);
	engine.get()->RegisterEnumValue("TileLayerType", "Objects", Tilemap::Layer::Objects);

	// Register TileLayer
	engine.get()->RegisterObjectType("TileLayer", sizeof(Tilemap::Layer), asOBJ_REF);

	engine.get()->RegisterObjectBehaviour("TileLayer", asBEHAVE_ADDREF, "void f()", asFUNCTION(dummy), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectBehaviour("TileLayer", asBEHAVE_RELEASE, "void f()", asFUNCTION(dummy), asCALL_CDECL_OBJLAST);

	engine.get()->RegisterObjectMethod("TileLayer", "int getTileCount()", asMETHOD(Tilemap::Layer, getTileCount), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("TileLayer", "int getTile(int)", asMETHOD(Tilemap::Layer, getTile), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("TileLayer", "void getTileShape(int, float& out,float& out,float& out,float& out)", asMETHOD(Tilemap::Layer, getTileShape), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("TileLayer", "vec2 getObjectPosition(const string& in)", asMETHOD(Tilemap::Layer, getObjectPosition), asCALL_THISCALL);

	engine.get()->RegisterObjectProperty("TileLayer", "int width", asOFFSET(Tilemap::Layer, mWidth));
	engine.get()->RegisterObjectProperty("TileLayer", "int height", asOFFSET(Tilemap::Layer, mHeight));

	// Register Tilemap
	engine.get()->RegisterObjectType("Tilemap", sizeof(ScriptTilemap), asOBJ_REF);

	engine.get()->RegisterObjectBehaviour("Tilemap", asBEHAVE_FACTORY, "Tilemap@ f()", asFUNCTION(TilemapInstancer), asCALL_CDECL);
	engine.get()->RegisterObjectBehaviour("Tilemap", asBEHAVE_ADDREF, "void f()", asFUNCTION(TilemapAddRef), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectBehaviour("Tilemap", asBEHAVE_RELEASE, "void f()", asFUNCTION(TilemapReleaseRef), asCALL_CDECL_OBJLAST);

	engine.get()->RegisterObjectMethod("Tilemap", "bool loadTMX(const string& in)", asMETHOD(Tilemap, loadTMX), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("Tilemap", "int getLayerCount()", asMETHOD(Tilemap, getLayerCount), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("Tilemap", "TileLayer@ getLayer(int index)", asMETHOD(Tilemap, getLayer), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("Tilemap", "TileLayer@ getLayerByName(const string& in)", asMETHOD(Tilemap, getLayerByName), asCALL_THISCALL);
	//engine.get()->RegisterObjectMethod("Tilemap", "string getLine()", asMETHOD(ScriptFile, getLine), asCALL_THISCALL);
	//engine.get()->RegisterObjectMethod("Tilemap", "bool atEnd()", asMETHOD(ScriptFile, atEnd), asCALL_THISCALL);
}

NEPHILIM_NS_END