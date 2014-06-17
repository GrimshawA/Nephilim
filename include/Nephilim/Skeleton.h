#ifndef NephilimSkeleton_h__
#define NephilimSkeleton_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Matrix.h>
#include <Nephilim/Strings.h>

#include <vector>

NEPHILIM_NS_BEGIN

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
#endif // NephilimSkeleton_h__
