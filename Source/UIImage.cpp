#include <Nephilim/UIImage.h>
#include <Nephilim/ASEngine.h>
#include <Nephilim/Sprite.h>
#include <AS/aswrappedcall.h>

NEPHILIM_NS_BEGIN

UIControl* UIImageRefCast(UIImage* a) 
{
	return refCast<UIImage, UIControl>(a);
}

void Wrap_UIImage_factory(asIScriptGeneric *gen)
{
	*reinterpret_cast<UIImage**>(gen->GetAddressOfReturnLocation()) = new UIImage();
}

void Wrap_UIImage_addReference(asIScriptGeneric *gen)
{
	reinterpret_cast<UIImage*>(gen->GetObject())->addReference();
}


void Wrap_UIImage_removeReference(asIScriptGeneric *gen)
{
	reinterpret_cast<UIImage*>(gen->GetObject())->removeReference();
}

bool registerUIImage(ASEngine* engine)
{
	engine->getASEngine()->RegisterObjectType("UIImage", sizeof(UIImage), asOBJ_REF);

	if(engine->getPortableMode())
	{
		engine->getASEngine()->RegisterObjectBehaviour("UIImage", asBEHAVE_FACTORY, "UIImage@ f()", asFUNCTION(Wrap_UIImage_factory), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectBehaviour("UIImage", asBEHAVE_ADDREF, "void f()",  asFUNCTION(Wrap_UIImage_addReference), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectBehaviour("UIImage", asBEHAVE_RELEASE, "void f()",  asFUNCTION(Wrap_UIImage_removeReference), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectBehaviour("UIImage", asBEHAVE_IMPLICIT_REF_CAST, "UIControl@ f()", WRAP_OBJ_LAST(UIImageRefCast), asCALL_GENERIC);

		engine->getASEngine()->RegisterObjectMethod("UIImage", "void setImage(const string &in)", WRAP_MFN(UIImage, setImage), asCALL_GENERIC);
	}
	else 
	{
		engine->getASEngine()->RegisterObjectBehaviour("UIImage", asBEHAVE_FACTORY, "UIImage@ f()", asFUNCTION(genericFactory<UIImage>), asCALL_CDECL);
		engine->getASEngine()->RegisterObjectBehaviour("UIImage", asBEHAVE_ADDREF, "void f()", asMETHOD(UIImage, addReference), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectBehaviour("UIImage", asBEHAVE_RELEASE, "void f()", asMETHOD(UIImage, removeReference), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectBehaviour("UIImage", asBEHAVE_IMPLICIT_REF_CAST, "UIControl@ f()", asFUNCTION((refCast<UIImage,UIControl>)), asCALL_CDECL_OBJLAST);
		
		engine->getASEngine()->RegisterObjectMethod("UIImage", "void setImage(const string &in)", asMETHOD(UIImage, setImage), asCALL_THISCALL);
	}

	/// Register the common UI control interface
	registerUIControlSubtype("UIImage", engine);

	return true;
}

UIImage::UIImage()
{
	t.loadFromFile("logo.png");
};

/// Reload all graphics because they were destroyed and are unavailable now
void UIImage::reloadGraphicalAssets()
{
	t.loadFromFile(m_path);
	TESTLOG("LOADED UIIMAGE AGAIN!")

	
}

/// Set the image of the control
void UIImage::setImage(const String& path)
{
	m_path = path;
	t.loadFromFile(path);
}

void UIImage::draw(Renderer* renderer)
{
	Sprite s;
	s.setPosition(m_bounds.left, m_bounds.top);
	s.setTexture(t);
	s.resize(m_bounds.width, m_bounds.height);
	renderer->draw(s);
};


NEPHILIM_NS_END