#ifndef PARABOLA_ANIMATIONTEXTWRITER_H
#define PARABOLA_ANIMATIONTEXTWRITER_H

#include "Platform.h"
#include "Strings.h"
#include "Animation.h"

PARABOLA_NAMESPACE_BEGIN

class PARABOLA_API AnimationTextWriter : public AnimationInterface{
public:
	/// Default construction
	AnimationTextWriter();

	/// Set the destination text for the animation
	void setText(const String &text);

	/// Set the duration of the writing
	void setDuration(float duration);

	/// Update state of the animation
	void update(float elapsedTime);

	/// Play override
	void play();

private:
	String myText;
	float myDuration;
	float myTotalTime;
	int prevIndex;
	AnimationEasingFunction *myFunction;
};

PARABOLA_NAMESPACE_END
#endif