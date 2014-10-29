#include <Nephilim/Math/AABB.h>
#include <Nephilim/Math/Ray.h>

NEPHILIM_NS_BEGIN

/// Construct the AABB from a center position and dimensions
AABB::AABB(const vec3& position, float hx, float hy, float hz)
{
	*this = AABB(vec3(position.x - hx, position.y - hy, position.z - hz), vec3(position.x + hx, position.y + hy, position.z + hz) );
}

bool AABB::intersect(const Ray &r, float t0, float t1) const
{
		float tmin, tmax, tymin, tymax, tzmin, tzmax;

		tmin = (parameters[r.sign[0]].x - r.origin.x) * r.inv_direction.x;
		tmax = (parameters[1-r.sign[0]].x - r.origin.x) * r.inv_direction.x;
		tymin = (parameters[r.sign[1]].y - r.origin.y) * r.inv_direction.y;
		tymax = (parameters[1-r.sign[1]].y - r.origin.y) * r.inv_direction.y;
		if ( (tmin > tymax) || (tymin > tmax) ) 
			return false;
		if (tymin > tmin)
			tmin = tymin;
		if (tymax < tmax)
			tmax = tymax;
		tzmin = (parameters[r.sign[2]].z - r.origin.z) * r.inv_direction.z;
		tzmax = (parameters[1-r.sign[2]].z - r.origin.z) * r.inv_direction.z;
		if ( (tmin > tzmax) || (tzmin > tmax) ) 
			return false;
		if (tzmin > tmin)
			tmin = tzmin;
		if (tzmax < tmax)
			tmax = tzmax;
		return ( (tmin < t1) && (tmax > t0) );
}

NEPHILIM_NS_END