#include <Nephilim/NStateCustom.h>
#include <Nephilim/ASEngine.h>
#include <Nephilim/Vectors.h>
#include <Nephilim/Renderer.h>
#include <Nephilim/ScriptedGameCore.h>
#include <Nephilim/UILineEdit.h>
#include <Nephilim/UIImage.h>

#include "AS/aswrappedcall.h"


#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

State* NStateCustomRefCast(NStateCustom* a)
{
	return refCast<NStateCustom, State>(a);
}

bool registerNStateCustom(ASEngine* engine)
{

	engine->getASEngine()->RegisterObjectType("CustomState", sizeof(NStateCustom), asOBJ_REF);
	
	if(engine->getPortableMode())
	{
		engine->getASEngine()->RegisterObjectBehaviour("CustomState", asBEHAVE_FACTORY, "CustomState@ f()", WRAP_FN(genericFactory<NStateCustom>), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectBehaviour("CustomState", asBEHAVE_ADDREF, "void f()", WRAP_MFN(NStateCustom, addReference), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectBehaviour("CustomState", asBEHAVE_RELEASE, "void f()", WRAP_MFN(NStateCustom, removeReference), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectBehaviour("CustomState", asBEHAVE_IMPLICIT_REF_CAST, "State@ f()", WRAP_OBJ_LAST(NStateCustomRefCast), asCALL_GENERIC);

		engine->getASEngine()->RegisterObjectMethod("CustomState", "void set(const string &in)", WRAP_MFN(NStateCustom, set), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectMethod("CustomState", "void finish()", WRAP_MFN(NStateCustom, finish), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectMethod("CustomState", "bool launchBindedState(const string &in)", WRAP_MFN(NStateCustom, launchBindedState), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectMethod("CustomState", "void sendMessage(const string &in, const string& in)", WRAP_MFN(NStateCustom, sendMessage), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectMethod("CustomState", "Slot@ slot(const string &in)", WRAP_MFN(NStateCustom, makeSlot), asCALL_GENERIC);
	}
	else
	{
		engine->getASEngine()->RegisterObjectBehaviour("CustomState", asBEHAVE_FACTORY, "CustomState@ f()", asFUNCTION(genericFactory<NStateCustom>), asCALL_CDECL);
		engine->getASEngine()->RegisterObjectBehaviour("CustomState", asBEHAVE_ADDREF, "void f()", asMETHOD(NStateCustom, addReference), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectBehaviour("CustomState", asBEHAVE_RELEASE, "void f()", asMETHOD(NStateCustom, removeReference), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectBehaviour("CustomState", asBEHAVE_IMPLICIT_REF_CAST, "State@ f()", asFUNCTION((refCast<NStateCustom,State>)), asCALL_CDECL_OBJLAST);

		engine->getASEngine()->RegisterObjectMethod("CustomState", "void set(const string &in)", asMETHOD(NStateCustom, set), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectMethod("CustomState", "void finish()", asMETHOD(NStateCustom, finish), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectMethod("CustomState", "bool launchBindedState(const string &in)", asMETHOD(NStateCustom, launchBindedState), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectMethod("CustomState", "void sendMessage(const string &in, const string& in)", asMETHOD(NStateCustom, sendMessage), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectMethod("CustomState", "Slot@ slot(const string &in)", asMETHOD(NStateCustom, makeSlot), asCALL_THISCALL);

	}

//	engine->getASEngine()->RegisterObjectProperty("CustomState", "UIManager ui", asOFFSET(NStateCustom, m_ui));

	return true;
};

/// The custom state needed parameters
void NStateCustom::set(const String& file)
{
	
	m_fileName = file;



}



/// Construct the state
NStateCustom::NStateCustom()
	:	State(),
	m_duration(5.f),
	m_elapsedTime(0.f),
	m_exported(false),
	m_script(NULL)
{
	cout<<"[NStateCustom] Construct"<<endl;
};

/// Destruct the state
NStateCustom::~NStateCustom()
{
	cout<<"[NStateCustom] Destruct"<<endl;
};

/// Callback when a message is received
void NStateCustom::onMessageReceived(String message)
{
	if(m_script)
	{
		m_script->prepareMethod("void onMessage(string)");
		m_script->prepareMethodArgument(0, &message, ScriptArgumentTypes::Object);
		m_script->call();
	}
}

ASSlot* NStateCustom::makeSlot(const String &functionName)
{
	ASSlot* sl = new ASSlot();
	sl->script = m_script;
	sl->functionName = functionName;
	//cout<<"Created slot("<<functionName<<"): "<<sl<<endl;
	return sl;
}


void NStateCustom::onAttach()
{
	m_scriptEngine = new ASEngine();
	m_scriptEngine->exportStrings();
	m_scriptEngine->exportBasicEngine();
	//m_scripting.exportBasicGameCore();
	m_scriptEngine->exportGraphics();
	m_scriptEngine->exportEvents();
	//m_scriptEngine->exportFiles();	

//	registerContentBank(m_scriptEngine);
//	registerView(m_scriptEngine);
	m_scriptEngine->exportMath();
//	registerStateStack(m_scriptEngine);
	registerScriptedGameCore(m_scriptEngine);
	//registerBrowserPreloader(&m_scripting);
	//registerNStateImage(&m_scripting);
	registerNStateCustom(m_scriptEngine);
	registerSprite(m_scriptEngine);

	registerUILineEdit(m_scriptEngine);
	registerUIImage(m_scriptEngine);

	m_scriptEngine->exportGlobalProperty("CustomState this", this);

//	m_ui.setArea(0,0,m_parent->getParentGame()->getWindow().getWidth(), m_parent->getParentGame()->getWindow().getHeight());

	if(m_parent && !m_exported)
	{
		m_exported = true;
		m_scriptEngine->exportGlobalProperty("ScriptedGameCore game", m_parent->getParentGame());
		cout<<"[NStateCustom] Exported game"<<endl;

		m_script = m_scriptEngine->loadScript(m_parent->getParentGame()->getFileSystemRoot() + m_fileName);
	}
};


void NStateCustom::onActivate()
{	
	if(m_script)
	{
		m_script->call(String("void onCreate()"));

		
	}
};


void NStateCustom::setImage(const String &image)
{
	cout<<"[NStateImage] Image: "<<image<<endl;

	m_texture.loadFromFile(image);
	m_sprite.setTexture(m_texture);
	m_sprite.resize(1024,768);
};

/// Delivers an event to the state
/// If returns true, it will be propagated to the rest of the stack
/// Otherwise it will remain under this.
bool NStateCustom::onEvent(Event &event)
{
	if(event.type == Event::Resized)
	{
		//PRINTLOG("Resize", "Resize: %d    %d\n", event.size.width, event.size.height);

/*		for(std::map<String,UIDocument*>::iterator it = m_ui.m_windows.begin(); it != m_ui.m_windows.end(); it++)
		{
			(*it).second->setRect(FloatRect(0,0,event.size.width, event.size.height));
		}*/
	}

	if(m_script)
	{
		m_script->prepareMethod("void onEvent(Event@)");
		m_script->prepareMethodArgument(0, &event, ScriptArgumentTypes::Object);
		m_script->call();
	}

/*	for(std::map<String,UIDocument*>::iterator it = m_ui.m_windows.begin(); it != m_ui.m_windows.end(); it++)
	{
		(*it).second->pushEvent(event);
	}*/
	return true;
}

/// Tells the state how much time it should update itself
/// Must return false if updating lesser states is not wanted
/// Returning true will update other stack states.
bool NStateCustom::onUpdate(Time &time)
{
	if(m_script)
	{
		float elapsedTime = time.asSeconds();
		m_script->prepareMethod("void onUpdate(float)");
		m_script->prepareMethodArgument(0, &elapsedTime, ScriptArgumentTypes::Float);
		m_script->call();
	}

/*	for(std::map<String,UIDocument*>::iterator it = m_ui.m_windows.begin(); it != m_ui.m_windows.end(); it++)
	{
		(*it).second->update(time.asSeconds());
	}*/

	return true;
};

/// Draws the state with the current renderer
/// If returns true, other states in the stack will be rendered
/// Otherwise this state has exclusivity over drawing
bool NStateCustom::onDraw(Renderer *renderer)
{
	// dirty rendering
	if(m_script)
	{
		m_script->prepareMethod("void onRender(Renderer@)");
		m_script->prepareMethodArgument(0, renderer, ScriptArgumentTypes::Object);
		m_script->call();
	}
	else
	{
		//renderer->drawDebugText(500, 100, "Script failed to compile.");
	}

	//renderer->drawDebugQuad(0,0,0,600,300, Color(250,200,200));

	return true;
};

NEPHILIM_NS_END