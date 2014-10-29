#ifndef NephilimRay_h__
#define NephilimRay_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Vectors.h>
#include <Nephilim/Math/AABB.h>

NEPHILIM_NS_BEGIN

/**
	\class Ray
	\brief A ray is a mathematical construct that is represented by a infinite line in 3D space, starting in a given position and extending infinitely in a given direction
*/
class NEPHILIM_API Ray
{
public:
	Ray() { }
	Ray(vec3 o, vec3 d) {
		origin = o;
		direction = d;
		inv_direction = vec3(1/d.x, 1/d.y, 1/d.z);
		sign[0] = (inv_direction.x < 0);
		sign[1] = (inv_direction.y < 0);
		sign[2] = (inv_direction.z < 0);
	}
	Ray(const Ray &r) {
		origin = r.origin;
		direction = r.direction;
		inv_direction = r.inv_direction;
		sign[0] = r.sign[0]; sign[1] = r.sign[1]; sign[2] = r.sign[2];
	}

	vec3 origin;
	vec3 direction;
	vec3 inv_direction;
	int sign[3];


	bool hits(AABB aabb);
};

NEPHILIM_NS_END
#endif // NephilimRay_h__
