#ifndef ANIMATIONKEYFRAME_H
#define ANIMATIONKEYFRAME_H

#include "Platform.h"
#include "Animation.h"
#include "Textures.h"
#include "BoundingBox.h"
#include <vector>
using namespace std;

namespace pE{

	enum KeyFramePositionType{
		Absolute = 0,
		Relative
	};

	class PARABOLA_API KeyFrame{
	public:
		KeyFrame(float TimeKey);

		//void AddImage(Image &SpriteSheet, BoundingBox Rect, float Time);
		//Image& Image();

		float GetTimeKey();
		void SetPosition(Vec2f Pos, KeyFramePositionType PositionType = Absolute); 
		Vec2f GetPosition();

		//BoundingBox& GetRect();

	private:
		Image *FrameImage;
		float TimeKey;
		BoundingBox FrameImageRect;

		Vec2f Position;
		unsigned int PositionType;

		bool PositionFlag, ColorFlag, ImageFlag;
	};

	class PARABOLA_API KeyFrameAnimation: public AbstractAnimation{
	public:
		KeyFrameAnimation();
		KeyFrameAnimation(string Name);


		void Animate(Animated* Object);
		void Update(float Time);

		int GetFrameIndex();

		KeyFrame* GetKeyFrame(int Index);		

		KeyFrame* AddKeyFrame(float TimeKey);

	private:
		vector<KeyFrame*> KeyFrames;
		vector<Vec2f> InitialPositions;
		int CurrentFrame;
	};
};

#endif