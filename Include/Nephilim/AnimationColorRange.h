#ifndef ANIMATIONCOLORRANGE_H
#define ANIMATIONCOLORRANGE_H

#include "Platform.h"
#include "AnimationRange.h"
#include "Colors.h"

namespace pE{
	/**
		\class AnimationColorRange
		\brief Represents a color animation, going from color A to color B over a determined time.

	*/
	class PARABOLA_API AnimationColorRange: public AnimationRange{
	public:
		AnimationColorRange();
		AnimationColorRange(Animated &Object);

		void SetBegin(Color Begin);
		void SetEnd(Color End);

		void Update(float Time);

	protected:
		Color BeginColor, EndColor;
	};
};

#endif