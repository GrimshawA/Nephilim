#ifndef NephilimRazerComponentSkinnedModel_h__
#define NephilimRazerComponentSkinnedModel_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/Component.h>


#include <Nephilim/Foundation/Time.h>

#include <Nephilim/Graphics/GraphicsDevice.h>
#include <Nephilim/Graphics/SkeletalMesh.h>
#include <Nephilim/Graphics/Skeleton.h>

#include <Nephilim/AnimationClip.h>
#include <Nephilim/Geometry.h>

NEPHILIM_NS_BEGIN

/**
	\class CSkeletalMesh
	\brief This component is an instance of a SkeletalMesh asset.

	It can be rendered in bind pose but also be deformed dynamically by a Skeleton instance.

	Deformers:
	- Physics (the physics simulation can animate the limbs of the skeleton dynamically)
	- Animation (a skeletal animation changes the transforms of bones over time)
	- Morph Targets (the mesh is deformed from a set of blended morph targets, i.e, this SkeletalMesh is a
	human face and has a few different facial expressions as morph targets, and the system is able to output any combination of these targets)
*/
class NEPHILIM_API CSkeletalMesh : public Component
{
public:

	/// The skeletal mesh this component is linked to
	SkeletalMesh* skeletalMeshAsset = nullptr;


	/// How far into the animation we are
	AnimationClip clip;
	Skeleton modelSkeleton;
	mat4 boneTransforms[128];
	float mAnimationTime;
	float mAnimationDuration;

	Shader rigShader;


public:
	/// Default initialization
	CSkeletalMesh();

	/// Updates the animation on its skeleton
	void update(const Time& deltaTime);

	/// Load an animation to be played in our skeleton
	void loadAnimation(const String& filename, const String& skeletonName);
};

NEPHILIM_NS_END
#endif // NephilimRazerComponentSkinnedModel_h__