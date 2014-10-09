#ifndef NephilimAnimationClip_h__
#define NephilimAnimationClip_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Math/Quaternion.h>
#include <Nephilim/Vectors.h>
#include <Nephilim/Strings.h>

#include <vector>

NEPHILIM_NS_BEGIN

/**
	\class AnimationClip
	\brief Stores a keyframe animation

	Contains all the data required to perform skeleton based animation on a set of bones, or something else
*/
class NEPHILIM_API AnimationClip
{
public:
	class KeyFrame
	{
	public:
		vec3       position;
		vec3       scale;
		Quaternion orientation;
		float      time;
	};

	/**
		\class Track
		\brief Represents a individual track on an animation

		In most cases, a track represents an individual bone animation
	*/
	class Track
	{
	public:

		/// Get the local track transform at time t
		/// t must be between 0 and frames.size(), the fractional part is interpolated between two frames
		mat4 getTransformFromTime(float t);

		String                name;
		std::vector<KeyFrame> frames;
	};

	Int32 getTrackIndexByName(const String& name);

	void clear();

	void getTransformsFromTime(float t, std::vector<mat4>& transforms);

	std::vector<Track> tracks;
	Int32 playbackFramesPerSecond; ///< How many frames pass in a second for the animation to run at normal speed
	Int32 numFrames;
};

NEPHILIM_NS_END
#endif // NephilimAnimationClip_h__
