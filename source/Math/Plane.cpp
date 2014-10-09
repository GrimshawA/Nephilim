#include <Nephilim/Math/Plane.h>
#include <Nephilim/Math/Ray.h>

NEPHILIM_NS_BEGIN

/// Returns true if the ray intersects the plane
/// and sets t to the distance along the ray where the intersection happens.
bool Plane::raycast(const Ray& r, float& t)
{
	// assuming vectors are all normalized
	float denom = normal.dot(r.direction);
	if (denom > 1e-6)
	{
		vec3 p0l0 = origin - r.origin;
		t = p0l0.dot(normal) / denom;
		return (t >= 0);
	}
	return false;
}

NEPHILIM_NS_END