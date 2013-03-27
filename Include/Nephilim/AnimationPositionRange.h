#ifndef ANIMATIONPOSITIONRANGE_H
#define ANIMATIONPOSITIONRANGE_H

#include "Platform.h"
#include "AnimationRange.h"

namespace pE{

	/**
		\class AnimationPositionRange
		\brief Provides a way to animate an object's position from point A to point B
	*/
	class PARABOLA_API AnimationPositionRange : public AnimationRange {
	public:
		AnimationPositionRange();
		AnimationPositionRange(Animated &Object);

		void SetBegin(Vec2f &Begin);
		void SetEnd(Vec2f &End);

		void Update(float Time);

	protected:
		Vec2f BeginPos, EndPos;
	};
};

#endif