#ifndef PARABOLA_ANIMATIONVIEW_H
#define PARABOLA_ANIMATIONVIEW_H

#include "Platform.h"
#include "Animation.h"
#include "Views.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Animation
	\class AnimationView
	\brief Capable of animating a view, making effects with it

	It makes possible to animate a view in such ways as to simulate an earthquake,
	a crash, or simply a vibration..

	All effects are always made relative to the view center, so you can move it around and the effect will prevail.
*/
class PARABOLA_API AnimationView : public AnimationInterface{
public:
	/// Creates an animation for the view 
	AnimationView(View &view);

	/// Creates an animation, but doesn't set the view yet
	AnimationView();

	/// Set the view to animate
	void setView(View &view);

	/// Update the state of the view
	void update(float elapsedTime);

	/// Creates an earthquake in the animated view
	void createEarthquake(float duration, float intensity);

	/// Restores the saved view coordinates
	void restore();

	/// Custom stop to allow restoring
	void stop();

	/// When a view is assigned to this animation
	/// its initial position is saved, and is restored at the end of animation, if allow is true
	/// It is restored by default
	void allowRestore(bool allow);

	/// Requests the view data to be stored for later restoring.
	void saveState();

private:
	View *myView;
	float myTimeLeft;
	float center_x, center_y;
	float x_dev, y_dev;
	float x_max_deviation, y_max_deviation;
	float x_dir, y_dir;
	float x_speed, y_speed;
	float attenuation;

	bool myRestore;
	float saved_x, saved_y;
};

PARABOLA_NAMESPACE_END
#endif