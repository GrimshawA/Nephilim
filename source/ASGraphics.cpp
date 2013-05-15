#include <AS/aswrappedcall.h>
#include "Nephilim/ASEngine.h"
//#include "Nephilim/SceneRenderer.h"
//#include "Nephilim/Sprite.h"
//#include "Nephilim/Texture.h"
#include "Nephilim/Color.h"
#include "Nephilim/Rect.h"
#include "Nephilim/Renderer.h"



NEPHILIM_NS_BEGIN
	/*
void SprConstructor(void *memory)
{
	// Initialize the pre-allocated memory by calling the
	// object constructor with the placement-new operator
	new(memory) Sprite();
}

void SprDestructor(void *memory)
{
	// Uninitialize the memory by calling the object destructor
	((Sprite*)memory)->~Sprite();
}

void dummyref(void*){

}


Sprite& dummyfac(){
	return *new Sprite();
}

SpriteExt& SpriteExtFactory(){
	return *new SpriteExt();
}


View& ViewFactory(){
	return *new View();
}

void ViewFactoryAdd(View *v){

}

void ViewFactoryRelease(View *v){

}*/


void ColorCTOR(void* memory){
	new(memory) Color();
}

void ColorKTOR(const Color& in, void* memory){
	new(memory) Color(in);
}

void ColorCTOR2(int r, int g, int b, void* memory){
	new(memory) Color(r,g,b);
}

void ColorDTOR(void* memory){
	((Color*)memory)->~Color();
}

void BBCTOR(void* memory){
	new(memory) FloatRect();
}

void BBCTOR2(float l, float t, float w, float h, void* memory){
	new(memory) FloatRect(l,t,w,h);
}

void BBDTOR(void* memory){
	((FloatRect*)memory)->~FloatRect();
}

/// Exports the renderer and a few more things
bool ASEngine::exportGraphics(){
	int r;

	exportReferenceDataType("Texture");
	exportReferenceDataType("Drawable");
	exportReferenceDataType("SpriteExt");
	exportReferenceDataType("AnimationSprite");
	exportReferenceDataType("Renderer");
	//exportReferenceDataType("Window");
	//exportReferenceDataType("View");

	// Class: Color
	asEngine->RegisterObjectType("Color", sizeof(Color), asOBJ_VALUE | asOBJ_APP_CLASS_C | asOBJ_APP_CLASS_ALLINTS);
	//asEngine->RegisterObjectType("Color", sizeof(Color), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_A);
	//asEngine->RegisterObjectType("View", sizeof(View), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK);
	asEngine->RegisterObjectType("BoundingBox", sizeof(FloatRect), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK);

	asEngine->RegisterObjectProperty("Color", "uint8 r", asOFFSET(Color, r));
	asEngine->RegisterObjectProperty("Color", "uint8 g", asOFFSET(Color, g));
	asEngine->RegisterObjectProperty("Color", "uint8 b", asOFFSET(Color, b));
	asEngine->RegisterObjectProperty("Color", "uint8 a", asOFFSET(Color, a));

	if(getPortableMode()){
		// Android generics

		// Class: Color
		asEngine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f()", WRAP_OBJ_LAST(constructObject<Color>), asCALL_GENERIC);
		asEngine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(int, int, int)", WRAP_OBJ_LAST(ColorCTOR2), asCALL_GENERIC);
		asEngine->RegisterObjectBehaviour("Color", asBEHAVE_DESTRUCT, "void f()", WRAP_OBJ_LAST(ColorDTOR), asCALL_GENERIC);
		asEngine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(const Color& in)", WRAP_OBJ_LAST(ObjectCopyConstructor<Color>), asCALL_GENERIC);

		asEngine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f()", WRAP_OBJ_LAST(BBCTOR), asCALL_GENERIC);
		asEngine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(float,float,float,float)", WRAP_OBJ_LAST(BBCTOR2), asCALL_GENERIC);
		asEngine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_DESTRUCT, "void f()", WRAP_OBJ_LAST(BBDTOR), asCALL_GENERIC);
		asEngine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const BoundingBox& in)", WRAP_OBJ_LAST(ObjectCopyConstructor<FloatRect>), asCALL_GENERIC);

		/*r = asEngine->RegisterObjectMethod("SpriteExt", "Texture@ addTexture(const string &in, const string &in, Color)", WRAP_MFN(SpriteExt, addTexture), asCALL_GENERIC);
		r = asEngine->RegisterObjectMethod("SpriteExt", "void triggerAnimation(const string &in)", WRAP_MFN(SpriteExt, triggerAnimation), asCALL_GENERIC);
		r = asEngine->RegisterObjectMethod("SpriteExt", "AnimationSprite@ addAnimation(const string &in)", WRAP_MFN(SpriteExt, addAnimation), asCALL_GENERIC);*/

/*		r = asEngine->RegisterObjectMethod("AnimationSprite", "void setLoop(bool)", WRAP_MFN(AnimationSprite, setLoop), asCALL_GENERIC);
		r = asEngine->RegisterObjectMethod("AnimationSprite", "void addFrame(Texture@, BoundingBox, float)", WRAP_MFN(AnimationSprite, addFrame), asCALL_GENERIC);
		*/
		r = asEngine->RegisterObjectMethod("Renderer", "void drawDebugQuad(float,float,float,float,float,Color)", WRAP_MFN(Renderer, drawDebugQuad), asCALL_GENERIC);
		r = asEngine->RegisterObjectMethod("Renderer", "void drawDebugCircle(Vec2f,float,Vec2f,Color)", WRAP_MFN(Renderer, drawDebugCircle), asCALL_GENERIC);
//		r = asEngine->RegisterObjectMethod("Renderer", "void drawDebugText(float,float, const string& in)", WRAP_MFN(Renderer, drawDebugText), asCALL_GENERIC);
//		r = asEngine->RegisterObjectMethod("Renderer", "void draw(Drawable@)", WRAP_MFN(Renderer, draw), asCALL_GENERIC);



	}
	else{
		// PC native calls

		// Class: Color
		asEngine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ColorCTOR), asCALL_CDECL_OBJLAST);
		asEngine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(int, int, int)", asFUNCTION(ColorCTOR2), asCALL_CDECL_OBJLAST);
		asEngine->RegisterObjectBehaviour("Color", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ColorDTOR), asCALL_CDECL_OBJLAST);
		asEngine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(const Color& in)", asFUNCTION(ColorKTOR), asCALL_CDECL_OBJLAST);


//        printf("Native calling\n");
		asEngine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(BBCTOR), asCALL_CDECL_OBJLAST);
		asEngine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(float,float,float,float)", asFUNCTION(BBCTOR2), asCALL_CDECL_OBJLAST);
		asEngine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(BBDTOR), asCALL_CDECL_OBJLAST);
		asEngine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const BoundingBox& in)", asFUNCTION(ObjectCopyConstructor<FloatRect>), asCALL_CDECL_OBJLAST);


/*
		r = asEngine->RegisterObjectMethod("AnimationSprite", "void setLoop(bool)", asMETHOD(AnimationSprite, setLoop), asCALL_THISCALL);
		r = asEngine->RegisterObjectMethod("AnimationSprite", "void addFrame(Texture@, BoundingBox, float)", asMETHOD(AnimationSprite, addFrame), asCALL_THISCALL);
		*/
		//r = asEngine->RegisterObjectMethod("Renderer", "void setView(View)", asMETHOD(Renderer, setView), asCALL_THISCALL);
		r = asEngine->RegisterObjectMethod("Renderer", "void drawDebugQuad(float,float,float,float,float,Color)", asMETHOD(Renderer, drawDebugQuad), asCALL_THISCALL);
		r = asEngine->RegisterObjectMethod("Renderer", "void drawDebugCircle(Vec2f,float,Vec2f,Color)", asMETHOD(Renderer, drawDebugCircle), asCALL_THISCALL);
		//r = asEngine->RegisterObjectMethod("Renderer", "void setDefaultViewRect(float,float)", asMETHOD(Renderer, setDefaultViewRect), asCALL_THISCALL);
	//	r = asEngine->RegisterObjectMethod("Renderer", "void drawDebugText(float,float, const string& in)", asMETHOD(Renderer, drawDebugText), asCALL_THISCALL);

	//	r = asEngine->RegisterObjectMethod("Renderer", "void draw(Drawable@)", asMETHOD(Renderer, draw), asCALL_THISCALL);

		//
		//r = asEngine->RegisterObjectBehaviour("View", asBEHAVE_FACTORY, "View@ f()", asFUNCTION(ViewFactory), asCALL_CDECL); if(r < 0)printf("r %d", r);
		//r = asEngine->RegisterObjectBehaviour("View", asBEHAVE_ADDREF, "void f()", asFUNCTION(ViewFactoryAdd), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);
		//r = asEngine->RegisterObjectBehaviour("View", asBEHAVE_RELEASE, "void f()", asFUNCTION(ViewFactoryRelease), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);
		//r = asEngine->RegisterObjectMethod("View", "void setCenter(Vec2f)", asMETHODPR(View, setCenter, (Vec2f), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
		//r = asEngine->RegisterObjectMethod("View", "void setCenter(float, float)", asMETHODPR(View, setCenter, (float, float), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
		//r = asEngine->RegisterObjectMethod("View", "Vec2f getCenter()", asMETHOD(View, getCenter) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
		//r = asEngine->RegisterObjectMethod("View", "void move(float, float)", asMETHODPR(View, move, (float, float), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
		//r = asEngine->RegisterObjectMethod("View", "void setSize(float, float)", asMETHODPR(View, setSize, (float, float), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
		//r = asEngine->RegisterObjectMethod("View", "void setRotation(float)", asMETHOD(View, setRotation) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
		//r = asEngine->RegisterObjectMethod("View", "float getRotation()", asMETHOD(View, getRotation) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
		//r = asEngine->RegisterObjectMethod("View", "void rotate(float)", asMETHOD(View, rotate) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
		//r = asEngine->RegisterObjectMethod("View", "void zoom(float)", asMETHOD(View, zoom) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	//	r = asEngine->RegisterObjectMethod("View", "void setRect(float,float,float,float)", asMETHOD(View, setRect) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
		//r = asEngine->RegisterObjectMethod("View", "void setViewportPreset(int)", asMETHOD(View, setViewportPreset) , asCALL_THISCALL); if(r < 0)printf("r %d", r);

	}


	/*/// Export drawable
	exportReferenceDataType("Drawable");

	exportReferenceDataType("Texture");
	r = asEngine->RegisterObjectMethod("Texture", "Vec2f getSize()", asMETHOD(Texture, getSize) , asCALL_THISCALL); if(r < 0)printf("r %d", r);


	/// Export sprites
	asEngine->RegisterObjectType("Sprite", sizeof(Sprite), asOBJ_REF);
	// Register the behaviours
	//r = asEngine->RegisterObjectBehaviour("Sprite", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(SprConstructor), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);
//	r = asEngine->RegisterObjectBehaviour("Sprite", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(SprDestructor), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);

	// Registering the factory behaviour
	r = asEngine->RegisterObjectBehaviour("Sprite", asBEHAVE_FACTORY, "Sprite@ f()", asFUNCTION(dummyfac), asCALL_CDECL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("Sprite", asBEHAVE_ADDREF, "void f()", asFUNCTION(dummyref), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("Sprite", asBEHAVE_RELEASE, "void f()", asFUNCTION(dummyref), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);

	r = asEngine->RegisterObjectMethod("Sprite", "void setTexture(Texture@, bool)", asMETHOD(Sprite, setTexture) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("Sprite", "void setCenterPosition(Vec2f)", asMETHODPR(Sprite, setCenterPosition, (Vec2f), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("Sprite", "void setPosition(Vec2f)", asMETHODPR(Sprite, setPosition, (Vec2f), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("Sprite", "void setPosition(float x, float y)", asMETHODPR(Sprite, setPosition, (float, float), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("Sprite", "void resize(float x, float y)", asMETHODPR(Sprite, resize, (float,float), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("Sprite", "bool containsPoint(Vec2f)", asMETHODPR(Sprite, containsPoint, (Vec2f), bool) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("Sprite", "bool containsPoint(float x, float y)", asMETHODPR(Sprite, containsPoint, (float, float), bool) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("Sprite", "void flipVertical()", asMETHOD(Sprite, flipVertical) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("Sprite", "void flipHorizontal()", asMETHOD(Sprite, flipHorizontal) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("Sprite", "bool isFlippedHorizontally()", asMETHOD(Sprite, isFlippedHorizontally) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("Sprite", "bool isFlippedVertically()", asMETHOD(Sprite, isFlippedVertically) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("Sprite", "void setOrigin(float, float)", asMETHODPR(Sprite, setOrigin, (float, float), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	//r = asEngine->RegisterObjectMethod("Sprite", "void setOrigin(Vec2f)", asMETHOD(Sprite, isFlippedVertically) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("Sprite", "void setRotation(float)", asMETHODPR(Sprite, setRotation, (float), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);

	asEngine->RegisterObjectType("SpriteExt", sizeof(SpriteExt), asOBJ_REF);
	// Registering the factory behaviour
	r = asEngine->RegisterObjectBehaviour("SpriteExt", asBEHAVE_FACTORY, "SpriteExt@ f()", asFUNCTION(SpriteExtFactory), asCALL_CDECL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("SpriteExt", asBEHAVE_ADDREF, "void f()", asFUNCTION(dummyref), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("SpriteExt", asBEHAVE_RELEASE, "void f()", asFUNCTION(dummyref), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);

	r = asEngine->RegisterObjectMethod("SpriteExt", "bool loadFromTextFile(const string &in)", asMETHODPR(SpriteExt, loadFromTextFile, (const String&),bool) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("SpriteExt", "void update(float)", asMETHOD(SpriteExt, update) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("SpriteExt", "void triggerAnimation(const string &in)", asMETHOD(SpriteExt, triggerAnimation) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("SpriteExt", "void resize(float,float)", asMETHOD(SpriteExt, resize) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("SpriteExt", "void setPosition(Vec2f)", asMETHODPR(SpriteExt, setPosition, (Vec2f), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("SpriteExt", "void setPosition(float,float)", asMETHODPR(SpriteExt, setPosition, (float,float), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("SpriteExt", "void setOrigin(Vec2f)", asMETHODPR(SpriteExt, setOrigin, (Vec2f), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("SpriteExt", "void setOrigin(float,float)", asMETHODPR(SpriteExt, setOrigin, (float,float), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("SpriteExt", "void flip(bool,bool)", asMETHOD(SpriteExt, flip) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("SpriteExt", "bool getFlippedX()", asMETHOD(SpriteExt, getFlippedX) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("SpriteExt", "bool getFlippedY()", asMETHOD(SpriteExt, getFlippedY) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("SpriteExt", "bool containsPoint(float,float)", asMETHODPR(SpriteExt, containsPoint, (float,float), bool) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("SpriteExt", "bool containsPoint(Vec2f)", asMETHODPR(SpriteExt, containsPoint, (Vec2f), bool) , asCALL_THISCALL); if(r < 0)printf("r %d", r);


	asEngine->RegisterEnum("ViewportPreset");
	asEngine->RegisterEnumValue("ViewportPreset", "TopLeftQuarter", TopLeftQuarter);
	asEngine->RegisterEnumValue("ViewportPreset", "TopRightQuarter", TopRightQuarter);
	asEngine->RegisterEnumValue("ViewportPreset", "BottomLeftQuarter", BottomLeftQuarter);
	asEngine->RegisterEnumValue("ViewportPreset", "BottomRightQuarter", BottomRightQuarter);
	asEngine->RegisterEnumValue("ViewportPreset", "TopHalf", TopHalf);
	asEngine->RegisterEnumValue("ViewportPreset", "BottomHalf", BottomHalf);
	asEngine->RegisterEnumValue("ViewportPreset", "LeftHalf", LeftHalf);
	asEngine->RegisterEnumValue("ViewportPreset", "RightHalf", RightHalf);
	asEngine->RegisterEnumValue("ViewportPreset", "WideScreen", WideScreen);

	asEngine->RegisterObjectType("View", sizeof(View), asOBJ_REF);

	// Registering the factory behaviour


	/// Export renderer
	exportReferenceDataType("SceneRenderer");
	asEngine->RegisterObjectMethod("SceneRenderer", "void drawDebugText(const string &in, float, float)", asMETHOD(SceneRenderer, drawDebugText), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("SceneRenderer", "void drawDebugCircle(float, float, float)", asMETHOD(SceneRenderer, drawDebugCircle), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("SceneRenderer", "void activate()", asMETHOD(SceneRenderer, activateRenderTarget), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("SceneRenderer", "void draw(Drawable& inout)", asMETHODPR(SceneRenderer, draw, (Drawable&), void), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("SceneRenderer", "void draw(Sprite@)", asMETHODPR(SceneRenderer, draw, (Drawable&), void), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("SceneRenderer", "void draw(SpriteExt@)", asMETHODPR(SceneRenderer, draw, (Drawable&), void), asCALL_THISCALL);
	if(exportedParticles)
		asEngine->RegisterObjectMethod("SceneRenderer", "void draw(ParticleEffect@)", asMETHODPR(SceneRenderer, draw, (Drawable&), void), asCALL_THISCALL);

	asEngine->RegisterObjectMethod("SceneRenderer", "void setView(View@)", asMETHOD(SceneRenderer, setView), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("SceneRenderer", "Vec2f convertCoords(Vec2f)", asMETHODPR(SceneRenderer, convertLocalCoordinates, (Vec2f), Vec2f), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("SceneRenderer", "Vec2f convertCoords(Vec2f, View@)", asMETHODPR(SceneRenderer, convertLocalCoordinates, (Vec2f, View&), Vec2f), asCALL_THISCALL);

	*/

	exportedRenderer = true;

	return true;
};

NEPHILIM_NS_END
