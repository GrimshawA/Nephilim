#ifndef PARABOLA_ANIMATIONSPRITE_H
#define PARABOLA_ANIMATIONSPRITE_H

#include "Platform.h"
#include "Animation.h"
#include "Sprite.h"
#include "Rect.h"
#include "Textures.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Animation
	\class AnimationSprite
	\brief Represents an animation of image frames in a set of sprites

	Can animate a set of sprites at the same time and will set them with the
	right texture sub rect along time, to simulate movement.
*/
class PARABOLA_API AnimationSprite : public AnimationInterface{
public:
	class AnimationFrame;
	/// Creates a default sprite animation
	AnimationSprite();

	/// Add a frame
	void addFrame(Texture* texture, FloatRect rect, float duration);
	/// Add a new frame to the animation
	void addFrame2(AnimationFrame &frame);

	/// Get the number of frames in this animation
	int getFrameCount();

	/// Applies one of the frames to all sprites
	void applyFrame(int index);

	/// Overload of AnimationInterface. Plays the animation.
	void play();

	/// Overload of AnimationInterface. Stops the animation.
	void stop();

	/// Reset the animation to the beginning
	void reset();

	/// Update the sprites over time. Essentially means changing its texture when needed!
	void update(float elapsedTime);

	/**
		Builds the frames from a sprite sheet, in this case only a one-line sprite sheet.
		Just specify the width of each frame, and how many you want, and from what texture, and it will do the work.
	*/
	int buildFromHorizontalSheet(float frameWidth, int frameCount, Texture* texture);

	sigc::signal<void, Texture*, FloatRect> onFrameChange;

	class PARABOLA_API AnimationFrame{
	public:
		AnimationFrame();
		AnimationFrame(FloatRect &box, Texture *texture, double time);

		/// Define the texture wanted, if the rect is still undefined (positioned at -1 -1), it becomes the full texture rect
		void setTexture(Texture* texture);

		double time;
		FloatRect myRect;

		friend class AnimationSprite;
	private:
		Texture *myTexture;
	};

private:
	std::vector<AnimationFrame> frames;
	std::vector<Sprite*> animationSprites;
	double currentTime;
	/// Sum of frame durations
	double totalDuration;
	double localTime;
	int frameIndex;
};

PARABOLA_NAMESPACE_END
#endif