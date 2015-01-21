#ifndef PARABOLA_ANIMATIONFACTORY_H
#define PARABOLA_ANIMATIONFACTORY_H

#include <Nephilim/Platform.h>
#include "AnimationInterface.h"
#include <Nephilim/Foundation/String.h>
#include "Signals.h"
#include "ReferenceCountable.h"
#include <map>



NEPHILIM_NS_BEGIN

class RocketElement;

/**
	\ingroup Animation
	\class AnimationFactory
	\brief Acts as a manager for a set of animations
*/
class NEPHILIM_API AnimationFactory : public RefCountable, public sigc::trackable {
public:
	
	/// Add a new animation to the factory
	void addAnimation(AnimationInterface* animation);

	void moveRocketElementTo(RocketElement* element, float x, float y, float duration);

	void resizeRocketElementTo(RocketElement* element, float width, float height, float duration);

	void addRocketElementContent(RocketElement* element, const String &content, float duration);


	/// Update the state of associated animations
	void update(float elapsedTime);

private:
	std::vector<AnimationInterface*> myAnimations;
};

NEPHILIM_NS_END
#endif