#ifndef NStateImage_h__
#define NStateImage_h__

#include "Platform.h"
#include "Strings.h"
#include "Sprite.h"
#include "Textures.h"
#include "State.h"
#include "AnimationGroupSequential.h"

PARABOLA_NAMESPACE_BEGIN

class PARABOLA_API NStateImage : public State
{
public:
	/// Construct the state
	NStateImage();
	/// Destruct the state
	~NStateImage();
	
	/// Draws the state with the current renderer
	/// If returns true, other states in the stack will be rendered
	/// Otherwise this state has exclusivity over drawing
	virtual bool onDraw(Renderer *renderer);

	/// Tells the state how much time it should update itself
	/// Must return false if updating lesser states is not wanted
	/// Returning true will update other stack states.
	virtual bool onUpdate(Time &time);

	void setImage(const String &image);

private:
	Texture m_texture;
	Sprite m_sprite;
	float m_duration;
	float m_elapsedTime;

	AnimationGroupSequential m_fadeAnimation;
};

class ASEngine;
bool registerNStateImage(ASEngine* engine);

PARABOLA_NAMESPACE_END
#endif // NStateImage_h__
