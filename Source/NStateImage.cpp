#include <Nephilim/NStateImage.h>
#include <Nephilim/ASEngine.h>
#include <Nephilim/Vectors.h>
#include <Nephilim/AnimationFade.h>
#include <Nephilim/AnimationStall.h>
#include <Nephilim/Renderer.h>

#include "AS/aswrappedcall.h"

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

State* NStateImageRefCast(NStateImage* a)
{
	return refCast<NStateImage, State>(a);
}

bool registerNStateImage(ASEngine* engine)
{
	engine->getASEngine()->RegisterObjectType("ImageState", sizeof(NStateImage), asOBJ_REF);

	if(engine->getPortableMode())
	{
		engine->getASEngine()->RegisterObjectBehaviour("ImageState", asBEHAVE_FACTORY, "ImageState@ f()", WRAP_FN(genericFactory<NStateImage>), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectBehaviour("ImageState", asBEHAVE_ADDREF, "void f()", WRAP_MFN(NStateImage, addReference), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectBehaviour("ImageState", asBEHAVE_RELEASE, "void f()", WRAP_MFN(NStateImage, removeReference), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectBehaviour("ImageState", asBEHAVE_IMPLICIT_REF_CAST, "State@ f()", WRAP_OBJ_LAST(NStateImageRefCast), asCALL_GENERIC);

		engine->getASEngine()->RegisterObjectMethod("ImageState", "void setImage(const string &in)", WRAP_MFN(NStateImage, setImage), asCALL_GENERIC);

	}
	else
	{
		engine->getASEngine()->RegisterObjectBehaviour("ImageState", asBEHAVE_FACTORY, "ImageState@ f()", asFUNCTION(genericFactory<NStateImage>), asCALL_CDECL);
		engine->getASEngine()->RegisterObjectBehaviour("ImageState", asBEHAVE_ADDREF, "void f()", asMETHOD(NStateImage, addReference), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectBehaviour("ImageState", asBEHAVE_RELEASE, "void f()", asMETHOD(NStateImage, removeReference), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectBehaviour("ImageState", asBEHAVE_IMPLICIT_REF_CAST, "State@ f()", asFUNCTION((refCast<NStateImage,State>)), asCALL_CDECL_OBJLAST);

		engine->getASEngine()->RegisterObjectMethod("ImageState", "void setImage(const string &in)", asMETHOD(NStateImage, setImage), asCALL_THISCALL);

	}

	

	return true;
};

/// Construct the state
NStateImage::NStateImage()
	:	State(),
		m_duration(5.f),
		m_elapsedTime(0.f)
{
	cout<<"[NStateImage] Construct"<<endl;

	m_fadeAnimation.addAnimation(new AnimationFade(&m_sprite, 1, 255, 1.5));
	m_fadeAnimation.addAnimation(new AnimationStall(2));
	m_fadeAnimation.addAnimation(new AnimationFade(&m_sprite, 255, 1, 1.5));

};

/// Destruct the state
NStateImage::~NStateImage()
{
	cout<<"[NStateImage] Destruct"<<endl;
};

void NStateImage::setImage(const String &image)
{
	cout<<"[NStateImage] Image: "<<image<<endl;

	m_texture.loadFromFile(image);
	m_sprite.setTexture(m_texture);
	m_sprite.resize(1024,768);

	m_fadeAnimation.play();
};

/// Tells the state how much time it should update itself
/// Must return false if updating lesser states is not wanted
/// Returning true will update other stack states.
bool NStateImage::onUpdate(Time &time)
{
	m_elapsedTime += time.asSeconds();
	m_fadeAnimation.onUpdate(time.asSeconds());
	if(m_elapsedTime >= m_duration)
	{
		// pop
		cout<<"[NStateImage] Finished."<<endl;
		finish(); 
	}
	return true;
};

/// Draws the state with the current renderer
/// If returns true, other states in the stack will be rendered
/// Otherwise this state has exclusivity over drawing
bool NStateImage::onDraw(Renderer *renderer)
{
	renderer->draw(m_sprite);
	return true;
};

NEPHILIM_NS_END