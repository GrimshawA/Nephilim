#ifndef NephilimPlane_h__
#define NephilimPlane_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

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
	/// Returns true if the ray intersects the plane
	/// and sets t to the distance along the ray where the intersection happens.
	bool raycast(const Ray& r, float& t);
};

NEPHILIM_NS_END
#endif // NephilimPlane_h__
