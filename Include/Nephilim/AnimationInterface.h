#ifndef PARABOLA_ANIMATION_INTERFACE_H
#define PARABOLA_ANIMATION_INTERFACE_H


#include "Platform.h"
#include "Vectors.h"
#include "Signals.h"
#include "AnimationEasing.h"
#include <vector>

PARABOLA_NAMESPACE_BEGIN

namespace PlayModes{
	enum State{
		Playing = 0,
		Stopped,
		Paused
	};
};

/**
	\ingroup Animation
	\class Animable
	\brief Base class for all objects that can be animated.
*/
class PARABOLA_API Animable{
public:

	/// Virtual destructor, for detaching running animations.
	virtual ~Animable();

	/// Signal to stop animations that are depending on this animable
	sigc::signal<void, Animable*> onDetachAnimation;

	virtual void animable_set_position(float x, float y) {};
	virtual Vec2f animable_get_position() {return Vec2f();};
	virtual void animable_set_color(int r, int g, int b, int a){}
	virtual Vec2f animable_get_size(){return Vec2f();}
	virtual void animable_set_size(float x, float y){}
	virtual void animable_add_character(char c){}
	virtual void animable_set_alpha(int alpha){}
};


namespace AnimationStates{
	enum Status{
		Stopped = 0,
		Paused,
		Playing
	};

	enum Loop{
		Looping = 0,
		Once
	};
};

/**
	\ingroup Animation
	\class AnimationInterface
	\brief Base class for all animations.

	Any animation class inherits
*/
class PARABOLA_API AnimationInterface : public sigc::trackable{
public:
	/// Creates the animation default states
	AnimationInterface();

	/// Get the current state of the animation
	AnimationStates::Status getStatus();

	/// Set the status of the animation directly - this won't emit any signals.
	void setStatus(AnimationStates::Status state);

	/// Called when the animation is updating
	/// \return MUST return the remaining time not used by the animation
	/// This is essential as in a play list of animations, when one finished, the next updates immediately.
	virtual float onUpdate(float elapsedTime) {return 0;};

	/// Called in the animation when its starting fresh, or after a reset
	virtual void onBegin();

	/// Called when the animation has ended - signal is emmited
	virtual void onEnd();

	/// Callback when the animation finishes
	sigc::signal<void> onFinish;

	/// Add a new object to this animation
	void addAnimable(Animable* animable);

	/// Remove animable from the list
	void removeAnimable(Animable* animable);

	/// Get the number of objects being animated
	int getAnimableCount();

	/// Get animable at index
	Animable* getAnimable(unsigned int index);

	/// Get the total time elapsed since this animation has started
	float getElapsedTime();

	/// Get the duration of the animation
	float getDuration();

	/// Set the duration of the animation
	void setDuration(float duration);

	/// Starts the updating of the animation
	virtual void play();

	/// Stops the updating of the animation
	virtual void stop();

	/// Checks if the animation is currently playing
	bool playing();

	/// Sets the animation as a loop if possible or not
	/// Animations can re implement this method, to disallow looping
	virtual void setLoop(bool isLoop);

	/// Checks if the animation is set to loop
	bool looping();

	/// Updates the state of the animation
	virtual void update(float elapsedTime){ };

protected:

	/// Restores the animated object(s) to their original state
	virtual void restore();

	/// Adds time to the total duration of this animation execution
	void addTime(float elapsedTime);

	/// Registered objects for animation update
	std::vector<Animable*> m_animables;

	/// The current state of the animation
	AnimationStates::Status m_playState;
	
	float m_totalElapsedTime;

private:
	
	int myStatus;
	bool myLooping;	

	float m_duration; ///< Duration of the animation, used in most.
};

PARABOLA_NAMESPACE_END
#endif