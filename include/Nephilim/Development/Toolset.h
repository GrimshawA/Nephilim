#ifndef NephilimDevelopmentToolset_h__
#define NephilimDevelopmentToolset_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>
#include <Nephilim/Foundation/Time.h>
#include <Nephilim/Foundation/Event.h>

NEPHILIM_NS_BEGIN

class Widget;
class Renderer;

/**
	\class Editor
	\brief Base class for every tool in the engine's toolset

	This class plays a major role in the suite of tools present in the engine.
	This class serves as the base behavior and functionality that every built-in editor must have.

	Tools like the World Editor, Material editor, Image editor, Script editor and others, all derive from this base class.
	Following the behavior specification in any custom or built-in tool is essential as it allows the tools to be launched to edit
	any game on runtime by hooking on it and even allowing cooperative editing of assets if properly setup.

	The most common use case of the specific editor tools is under the engine's toolset as a external program used to develop games.

	The main purpose of the class is to group every editing tool ever existing in Nephilim in a consistent and unified ecosystem that spans
	to any game made with the engine, as well as external tools.
*/
class NEPHILIM_API IEditor
{
public:
	IEditor();

	virtual void onEvent(const Event& ev){}
	virtual void onUpdate(Time elapsedTime){}
	virtual void onRender(Renderer* renderer){};

	/// All instances of Editor based classes must identify the tool name
	String mName;

	/// Editor tools need to run on a UIView, where they show their tools
	Widget* mView;

	/// Not always used, but is meant to store an unique ID of this editor instance
	Int32 mInstanceId;
};

NEPHILIM_NS_END
#endif // NephilimDevelopmentToolset_h__
