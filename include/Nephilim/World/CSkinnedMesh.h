#ifndef NephilimRazerComponentSkinnedModel_h__
#define NephilimRazerComponentSkinnedModel_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Time.h>
#include <Nephilim/Graphics/GraphicsDevice.h>
#include <Nephilim/AnimationClip.h>
#include <Nephilim/Skeleton.h>
#include <Nephilim/World/Component.h>
#include <Nephilim/Geometry.h>
#include "SKNLoader.h"
#include "SKLLoader.h"
#include "ANMLoader.h"

class AnimationANM;
class SkeletonSKL;

NEPHILIM_NS_BEGIN

/**
	\class 
	\brief 
*/
class NEPHILIM_API ComponentSkinnedModel : public Component
{
public:
	ComponentSkinnedModel();

	void update(const Time& deltaTime);

	void render(GraphicsDevice* mRenderer);

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

	GeometryData champion;
	Texture championTexture;
	SkeletonSKL skeletonskl;
	AnimationANM animations;

	Shader rigShader;
};

NEPHILIM_NS_END
#endif // NephilimRazerComponentSkinnedModel_h__