#ifndef NephilimWorld_AFlipBookComponent_h__
#define NephilimWorld_AFlipBookComponent_h__

#include <Nephilim/World/ASceneComponent.h>
#include <Nephilim/Foundation/Rect.h>
#include <Nephilim/Graphics/Texture2D.h>
#include <Nephilim/Animation/Animation.h>

NEPHILIM_NS_BEGIN

/**
	\class FlipBookAnimation
	\brief Describes one sprite animation

	One animation can be for example a run or walk cycle,
	casting a spell, etc.
*/
class NEPHILIM_API FlipBookAnimation : public Animation
{
public:

	struct KeyFrame
	{
		FloatRect textureRect;
		Texture2D* texture;
		String TextureName; ///< While texture ptr is unresolved, we use this to fetch an appropriate texture ptr
		float t; // relative time this key frame happens on
	};

	std::vector<KeyFrame> keyFrames;

	bool Looping = true;

public:

	/// Load the animation from a JSON file
	bool loadfromFile(const String& filename);

	/// Find the correct keyframe data for the requested time
	KeyFrame getFrameAtTime(float t);

	/// Get duration of this animation
	float getDuration();

	/// Add a new frame to the animation
	void addFrame(Texture2D* texture, float keyTime);
};

/*
	\class AFlipBookComponent
	\brief Rectangular sprite with animation support

	This component is an animated sprite, and it can represent
	a character, for example. 

	By dynamically switching the animations to walk, run, jump and so on,
	one can make a nice cohesive character.

	The flip book can display one animation at a time
*/
class NEPHILIM_API AFlipBookComponent : public ASceneComponent
{
public:

	/// Current animation data that we're showing
	FlipBookAnimation* currentAnimation = nullptr;

	FlipBookAnimation::KeyFrame currentKeyFrame;

	/// Current relative time on currentAnimation
	float elapsedTime;
	
public:

	/// Construct the defaults
	AFlipBookComponent();

	/// Set the current animation this flip book is executing
	void setAnimation(FlipBookAnimation* animation);

	/// Update the animation with a delta time
	void update(float deltaTime);
};

NEPHILIM_NS_END
#endif // NephilimWorld_AFlipBookComponent_h__
