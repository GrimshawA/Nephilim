#ifndef PARABOLA_ANIMATIONFACTORY_H
#define PARABOLA_ANIMATIONFACTORY_H

#include "Platform.h"
#include "AnimationInterface.h"
#include "Strings.h"
#include "Signals.h"
#include "ReferenceCountable.h"
#include <map>



PARABOLA_NAMESPACE_BEGIN

class RocketElement;

/**
	\ingroup Animation
	\class AnimationFactory
	\brief Acts as a manager for a set of animations
*/
class PARABOLA_API AnimationFactory : public RefCountable, public sigc::trackable {
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

PARABOLA_NAMESPACE_END
#endif