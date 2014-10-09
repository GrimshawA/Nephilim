#ifndef NephilimAABB_h__
#define NephilimAABB_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Vectors.h>

NEPHILIM_NS_BEGIN

class Ray;
/**
	\class AABB
	\brief Represents a 3D parallelepiped with axis aligned edges
*/
class NEPHILIM_API AABB
{
public:
	AABB() { }
	AABB(const vec3 &min, const vec3 &max) {
		//assert(min < max);
		parameters[0] = min;
		parameters[1] = max;
	}

	/// Construct the AABB from a center position and dimensions
	AABB(const vec3& position, float hx, float hy, float hz);

	// (t0, t1) is the interval for valid hits
	bool intersect(const Ray &, float t0, float t1) const;

	// corners
	vec3 parameters[2];

	//bool intersect(const Ray &r, float t0, float t1) 
};

NEPHILIM_NS_END
#endif // NephilimAABB_h__