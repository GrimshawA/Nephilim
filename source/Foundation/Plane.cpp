#include <Nephilim/Foundation/Plane.h>
#include <Nephilim/Foundation/Ray.h>

NEPHILIM_NS_BEGIN

/// Construct a default plane
Plane::Plane()
{

}

/// Construct a plane from a position and a normal
Plane::Plane(Vector3D orig, Vector3D norm)
: origin(orig)
, normal(norm)
{
}

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

/// Flips the plane so it faces the opposing side
void Plane::flip()
{
	normal *= -1.f;
}

/// Performs a raycast on the plane on both sides, to ensure it hits from either one
bool Plane::raycastTwoSided(const Ray& r, float &t)
{
	if (raycast(r, t))
	{
		return true;
	}
	else
	{
		Plane flipped = *this;
		flipped.flip();
		return flipped.raycast(r, t);
	}
}

NEPHILIM_NS_END