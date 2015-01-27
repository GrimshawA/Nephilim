#ifndef NephilimWorldActorSkeletalMeshComponent_h__
#define NephilimWorldActorSkeletalMeshComponent_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/GameObject.h>
#include <Nephilim/World/Actor.h>
#include <Nephilim/World/CTransform.h>
#include <Nephilim/World/CInput.h>
#include <Nephilim/World/CStaticMesh.h>
#include <Nephilim/World/CSprite.h>
#include <Nephilim/World/CColliderBox.h>
#include <Nephilim/World/CSkeletalMesh.h>
#include <Nephilim/Foundation/BBox.h>

#include <Nephilim/Scripting/IScript.h>

NEPHILIM_NS_BEGIN

/**
	\class ASkeletalMeshComponent
	\brief Adds a skeletal mesh to the actor
*/
class NEPHILIM_API ASkeletalMeshComponent : public ASceneComponent, public CSkeletalMesh
{
public:



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
