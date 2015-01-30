#ifndef NephilimWorldActorSkeletalMeshComponent_h__
#define NephilimWorldActorSkeletalMeshComponent_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/GameObject.h>
#include <Nephilim/World/Actor.h>
#include <Nephilim/World/CTransform.h>
#include <Nephilim/World/Components/AInputComponent.h>
#include <Nephilim/World/Components/AStaticMeshComponent.h>
#include <Nephilim/World/Components/ASpriteComponent.h>
#include <Nephilim/World/Components/ABoxComponent.h>

#include <Nephilim/Foundation/BBox.h>

#include <Nephilim/Scripting/IScript.h>

#include <Nephilim/Foundation/Time.h>

#include <Nephilim/Graphics/GraphicsDevice.h>
#include <Nephilim/Graphics/SkeletalMesh.h>
#include <Nephilim/Graphics/Skeleton.h>
#include <Nephilim/Graphics/Geometry.h>
#include <Nephilim/Graphics/GL/GLShader.h>

#include <Nephilim/Animation/AnimationClip.h>

NEPHILIM_NS_BEGIN

/**
	\class ASkeletalMeshComponent
	\brief Adds a skeletal mesh to the actor
*/
class NEPHILIM_API ASkeletalMeshComponent : public ASceneComponent
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

	GLShader rigShader;


public:
	/// Default initialization
	ASkeletalMeshComponent();

	/// Updates the animation on its skeleton
	void update(const Time& deltaTime);

	/// Load an animation to be played in our skeleton
	void loadAnimation(const String& filename, const String& skeletonName);

	Texture myT;

public:

	void testTexture(const String& name)
	{
		myT.loadFromFile(name);
	}

	/// Update the animation
	void updateAnimation();
};

NEPHILIM_NS_END
#endif // NephilimWorldActorSkeletalMeshComponent_h__
