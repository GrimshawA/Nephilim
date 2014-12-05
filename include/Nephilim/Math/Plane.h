#ifndef NephilimPlane_h__
#define NephilimPlane_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Vectors.h>


NEPHILIM_NS_BEGIN
class Ray;

/**
	\class Plane
	\brief Defines a infinite flat surface for calculations

	The plane is merely defined by a normal, that defines the direction it faces,
	as well as an offset from the origin, to displace it.
*/
class NEPHILIM_API Plane
{
public:
	vec3 origin;
	vec3 normal;

public:
	/// Construct a default plane
	Plane();

	/// Construct a plane from a position and a normal
	Plane(Vector3D orig, Vector3D norm);

	/// Flips the plane so it faces the opposing side
	void flip();

	/// Returns true if the ray intersects the plane
	/// and sets t to the distance along the ray where the intersection happens.
	bool raycast(const Ray& r, float& t);

	/// Performs a raycast on the plane on both sides, to ensure it hits from either one
	bool raycastTwoSided(const Ray& r, float &t);
};

NEPHILIM_NS_END
#endif // NephilimPlane_h__
