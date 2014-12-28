#ifndef NephilimGraphicsSkeleton_h__
#define NephilimGraphicsSkeleton_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Math/Matrix.h>
#include <Nephilim/Strings.h>

#include <vector>

NEPHILIM_NS_BEGIN

/**
	\class Skeleton
	\brief Represents a deformable skeleton to be used for animation or rag doll physics

	A skeleton is basically a bunch of bones linked together hierarchically.
	These bones can then move and rotate in really complex ways, involving any combinations
	of skeletal animations, morph targets and even physics behaviors.

	As we change the skeleton state, all skeletal meshes that reference it automatically deform
	to match it, effectively making up rag dolls and interesting characters.
*/
class NEPHILIM_API Skeleton
{
public:

	class Bone
	{
	public:
		String name;
		Int32 parentId;
		Uint32 id;
		mat4 bindPoseMatrix;
	};

	/// Takes an array of bone transforms in their local spaces and converts them to transformed global space
	void convertToWorldSpace(std::vector<mat4>& localBoneTransforms);

	Int32 getIndexFromName(const String& name);

	std::vector<Bone> bones;
};

NEPHILIM_NS_END
#endif // NephilimGraphicsSkeleton_h__
