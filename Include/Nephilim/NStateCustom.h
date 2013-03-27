#ifndef NStateCustom_h__
#define NStateCustom_h__

#include "Platform.h"
#include "Strings.h"
#include "Sprite.h"
#include "Textures.h"
#include "State.h"
#include "ASSlot.h"
#include "UIManager.h"

PARABOLA_NAMESPACE_BEGIN
class ASEngine;
class ASScript;


/**
	\class NStateCustom
	\brief Exclusive use by ScriptedGameCore apps.
*/
class PARABOLA_API NStateCustom : public State
{
public:
	/// Construct the state
	NStateCustom();
	/// Destruct the state
	~NStateCustom();

	void onActivate();

	virtual void onAttach();

	ASSlot* makeSlot(const String &functionName);

	/// Callback when a message is received
	virtual void onMessageReceived(String message);

	/// Draws the state with the current renderer
	/// If returns true, other states in the stack will be rendered
	/// Otherwise this state has exclusivity over drawing
	virtual bool onDraw(Renderer *renderer);

	/// Tells the state how much time it should update itself
	/// Must return false if updating lesser states is not wanted
	/// Returning true will update other stack states.
	virtual bool onUpdate(Time &time);

	/// Delivers an event to the state
	/// If returns true, it will be propagated to the rest of the stack
	/// Otherwise it will remain under this.
	virtual bool onEvent(Event &event);

	void setImage(const String &image);

	/// The custom state needed parameters
	void set(const String& file);

	UIManager m_ui;

private:
	Texture m_texture;
	Sprite m_sprite;
	float m_duration;
	float m_elapsedTime;
	ASEngine* m_scriptEngine;
	ASScript* m_script;
	String m_fileName;
	String uid;
	bool m_exported;

	std::vector<ASSlot*> m_slots;
};

class ASEngine;
bool registerNStateCustom(ASEngine* engine);

PARABOLA_NAMESPACE_END
#endif // NStateCustom_h__
