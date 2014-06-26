#include <Nephilim/AnimationClip.h>

NEPHILIM_NS_BEGIN

////////////////////////////////////////////////////////////////////////// TRACK

/// Get the local track transform at time t
mat4 AnimationClip::Track::getTransformFromTime(float t)
{
	Int32 frameIndex = static_cast<Int32>(t);
	Int32 nextFrameIndex = (frameIndex + 1) % frames.size();
	float blend = t - frameIndex;

	vec3 finalPosition = vec3::lerp(frames[frameIndex].position, frames[nextFrameIndex].position, blend);
	Quaternion finalOrientation = Quaternion::slerp(frames[frameIndex].orientation, frames[nextFrameIndex].orientation, blend);

	return (mat4::translate(finalPosition) * finalOrientation.toMatrix());
}

//////////////////////////////////////////////////////////////////////////

void AnimationClip::getTransformsFromTime(float t, std::vector<mat4>& transforms)
{
	for(std::size_t i = 0; i < tracks.size(); ++i)
	{
		transforms[i] = tracks[i].getTransformFromTime(t);
	}
}

Int32 AnimationClip::getTrackIndexByName(const String& name)
{
	for(std::size_t i = 0; i < tracks.size(); ++i)
	{
		if(tracks[i].name == name)
		{
			return i;
		}
	}
	return 0;
}

void AnimationClip::clear()
{
	tracks.clear();
}

NEPHILIM_NS_END