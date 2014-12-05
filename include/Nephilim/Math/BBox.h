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
class NEPHILIM_API BBox
{
public:
	// corners
	vec3 parameters[2];


public:
	BBox();

	BBox(const vec3 &min, const vec3 &max);

	/// Construct the AABB from a center position and dimensions
	BBox(const vec3& position, float hx, float hy, float hz);

	// (t0, t1) is the interval for valid hits
	bool intersect(const Ray &, float t0, float t1) const;

	/// Set the origin of the box, its center
	void setOrigin(float x, float y, float z);

	/// Set the extents (size) of the box in half-size
	void setExtents(float hx, float hy, float hz);

	/// Get the extents of this box
	Vector3D getExtents();

	/// Get the origin of this box
	Vector3D getOrigin();

	static BBox Create(Vector3D origin, Vector3D extents);
};



NEPHILIM_NS_END
#endif // NephilimAABB_h__