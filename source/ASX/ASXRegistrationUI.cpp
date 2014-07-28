#include <Nephilim/ASX/ASXRegistrationUI.h>
#include <Nephilim/ASXEngine.h>
#include <Nephilim/AxPosition.h>

#include <Nephilim/UIView.h>
#include <Nephilim/Logger.h>

#include <angelscript.h>

namespace
{
	void dummy()
	{

	}
};


NEPHILIM_NS_BEGIN

void animateUIViewByName(const String& name, UIView* view)
{
	Log("ANIMATING %s", name.c_str());

	if(name == "AdvancePage" && !view->hasAnimatedChildren())
	{
		for(std::size_t i = 0; i < view->getChildCount(); ++i)
		{
			view->getChild(i)->commitAnimation(new AxPosition2D(view->getChild(i)->getPosition().x - view->getSize().x, view->getChild(i)->getPosition().y, 1.f));
		}
	}
	if(name == "ReturnPage" && !view->hasAnimatedChildren())
	{
		for(std::size_t i = 0; i < view->getChildCount(); ++i)
		{
			view->getChild(i)->commitAnimation(new AxPosition2D(view->getChild(i)->getPosition().x + view->getSize().x, view->getChild(i)->getPosition().y, 1.f));
		}
	}
}


void registerUserInterfaceASX(ASXEngine& engine)
{
	// Register the UIComponents enum
	engine.get()->RegisterEnum("UIComponent");
	engine.get()->RegisterEnumValue("UIComponent", "Button", UIComponentList::Button);
	engine.get()->RegisterEnumValue("UIComponent", "Background", UIComponentList::Background);
	engine.get()->RegisterEnumValue("UIComponent", "Text", UIComponentList::Text);


	// Register the UIView API
	engine.get()->RegisterObjectType("UIView", sizeof(UIView), asOBJ_REF);

	engine.get()->RegisterObjectBehaviour("UIView", asBEHAVE_ADDREF, "void f()", asFUNCTION(dummy), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectBehaviour("UIView", asBEHAVE_RELEASE, "void f()", asFUNCTION(dummy), asCALL_CDECL_OBJLAST);

	engine.get()->RegisterObjectMethod("UIView", "UIView@ create(const string& in)", asMETHOD(UIView, createChild), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("UIView", "void setRect(float, float, float, float)", asMETHODPR(UIView, setRect, (float,float,float,float), void), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("UIView", "void add(const string& in)", asMETHODPR(UIView, addComponent, (const String&), void), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("UIView", "void add(int)", asMETHODPR(UIView, addComponent, (int), void), asCALL_THISCALL);

	engine.get()->RegisterObjectMethod("UIView", "void load(const string& in)", asMETHOD(UIView, load), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("UIView", "void set(const string& in)", asMETHOD(UIView, setProperty), asCALL_THISCALL);

	engine.get()->RegisterObjectMethod("UIView", "void setName(const string& in)", asMETHOD(UIView, setName), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("UIView", "string getName()", asMETHOD(UIView, getName), asCALL_THISCALL);

	engine.get()->RegisterObjectMethod("UIView", "int getChildCount()", asMETHOD(UIView, getChildCount), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("UIView", "UIView@ getChild(int)", asMETHOD(UIView, getChild), asCALL_THISCALL);

	engine.get()->RegisterObjectMethod("UIView", "vec2 getPosition()", asMETHOD(UIView, getPosition), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("UIView", "void setPosition(float, float)", asMETHODPR(UIView, setPosition, (float,float), void), asCALL_THISCALL);
	
	engine.get()->RegisterObjectMethod("UIView", "vec2 getSize()", asMETHOD(UIView, getSize), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("UIView", "void setSize(float, float)", asMETHOD(UIView, setSize), asCALL_THISCALL);

	engine.get()->RegisterObjectMethod("UIView", "void addStringProperty(const string& in,const string& in)", asMETHOD(UIView, addStringProperty), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("UIView", "string getStringProperty(const string& in)", asMETHOD(UIView, getStringProperty), asCALL_THISCALL);

	engine.get()->RegisterObjectMethod("UIView", "void animate(const string& in)", asFUNCTION(animateUIViewByName), asCALL_CDECL_OBJLAST);
}

NEPHILIM_NS_END