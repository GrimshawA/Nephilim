#ifndef NephilimRazerComponentSkinnedModel_h__
#define NephilimRazerComponentSkinnedModel_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Time.h>
#include <Nephilim/Graphics/GraphicsDevice.h>
#include <Nephilim/Graphics/SkeletalMesh.h>
#include <Nephilim/Graphics/Skeleton.h>

#include <Nephilim/AnimationClip.h>
#include <Nephilim/World/Component.h>
#include <Nephilim/Geometry.h>

NEPHILIM_NS_BEGIN

/**
	\class 
	\brief 
*/
class NEPHILIM_API CSkeletalMesh : public Component
{
public:

	/// How far into the animation we are
	AnimationClip clip;
	Skeleton modelSkeleton;
	mat4 boneTransforms[128];
	float mAnimationTime;
	float mAnimationDuration;


	GeometryData champion;
	Texture championTexture;

	Shader rigShader;


public:
	CSkeletalMesh();

	void update(const Time& deltaTime);

	void render(GraphicsDevice* mRenderer);

	void loadAnimation(const String& filename, const String& skeletonName);
};

NEPHILIM_NS_END
#endif // NephilimRazerComponentSkinnedModel_h__