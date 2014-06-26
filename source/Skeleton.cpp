#include <Nephilim/Skeleton.h>

NEPHILIM_NS_BEGIN

Int32 Skeleton::getIndexFromName(const String& name)
{
	for(std::size_t i = 0; i < bones.size(); ++i)
	{
		if(bones[i].name == name)
			return i;
	}
	return 0;
}

mat4 makeAbsoluteTransform(std::vector<mat4>& boneTransforms, int bone_id, Skeleton& skeleton)
{
	mat4 boneTransform = boneTransforms[bone_id];

	int parentID = skeleton.bones[bone_id].parentId;
	if(parentID >= 0)
	{
		boneTransform = makeAbsoluteTransform(boneTransforms, parentID, skeleton) * boneTransform;
	}

	return boneTransform;
}

/// Takes an array of bone transforms in their local spaces and converts them to transformed global space
void Skeleton::convertToWorldSpace(std::vector<mat4>& localBoneTransforms)
{
	std::vector<mat4> transforms_copy = localBoneTransforms;

	// For each bone, compute the global transform of the bone
	for(std::size_t i = 0; i < bones.size(); ++i)
	{
		localBoneTransforms[i] = makeAbsoluteTransform(transforms_copy, i, *this);
	}
}

NEPHILIM_NS_END
