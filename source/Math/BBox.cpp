#include <Nephilim/Math/BBox.h>
#include <Nephilim/Math/Ray.h>

NEPHILIM_NS_BEGIN

BBox BBox::Create(Vector3D origin, Vector3D extents)
{
	return BBox(origin, extents.x, extents.y, extents.z);
}

BBox::BBox()
{

}

/// Construct the AABB from a center position and dimensions
BBox::BBox(const vec3& position, float hx, float hy, float hz)
{
	*this = BBox(vec3(position.x - hx, position.y - hy, position.z - hz), vec3(position.x + hx, position.y + hy, position.z + hz) );
}

BBox::BBox(const vec3 &min, const vec3 &max) 
{
	//assert(min < max);
	parameters[0] = min;
	parameters[1] = max;
}

/// Set the origin of the box, its center
void BBox::setOrigin(float x, float y, float z)
{
	vec3 extents = getExtents();

	*this = BBox(vec3(x, y, z), extents.x, extents.y, extents.z);
}

/// Set the extents (size) of the box in half-size
void BBox::setExtents(float hx, float hy, float hz)
{
	*this = BBox(getOrigin(), hx, hy, hz);
}

/// Get the extents of this box
Vector3D BBox::getExtents()
{
	return (parameters[1] - parameters[0]) * 0.5f;
}

/// Get the origin of this box
Vector3D BBox::getOrigin()
{
	Vector3D extents = getExtents();
	return Vector3D(parameters[0].x + extents.x, parameters[0].y + extents.y, parameters[0].z + extents.z);
}

bool BBox::intersect(const Ray &r, float t0, float t1) const
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