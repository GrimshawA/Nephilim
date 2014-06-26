#ifndef NephilimRazerComponentSkinnedModel_h__
#define NephilimRazerComponentSkinnedModel_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Time.h>
#include <Nephilim/Renderer.h>
#include <Nephilim/AnimationClip.h>
#include <Nephilim/Skeleton.h>
#include <Nephilim/Razer/Component.h>

class AnimationANM;
class SkeletonSKL;

NEPHILIM_NS_BEGIN

namespace rzr
{
/**
	\class 
	\brief 
*/
class NEPHILIM_API ComponentSkinnedModel : public Component
{
public:
	ComponentSkinnedModel();

	void update(const Time& deltaTime);

	void render(Renderer* mRenderer);

	void getBoneTransforms(mat4* transforms, AnimationANM& animation, SkeletonSKL& skeleton);

	void loadAnimation(const String& filename);

	mat4 baseTransform;

	mat4 boneTransforms[128];

	void setRotation(Quaternion r);

	/// How far into the animation we are
	float mAnimationTime;
	float mAnimationDuration;

	AnimationClip clip;
	Skeleton modelSkeleton;
};

};
NEPHILIM_NS_END
#endif // NephilimRazerComponentSkinnedModel_h__