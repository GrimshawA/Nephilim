#ifndef NephilimQuaternion_h__
#define NephilimQuaternion_h__

#include "Platform.h"
#include "Matrix.h"

NEPHILIM_NS_BEGIN


class Quaternion
{
public:
	Quaternion();

	Quaternion(float nx, float ny, float nz, float nw);

	void rotateEulerAngles(float ax, float ay, float az);

	void rotateAxisAngle(float angle, float ax, float ay, float az);

	Quaternion operator*(const Quaternion& q2);

	void normalize();  

	float x,y,z,w;

	mat4 toMatrix();
	
	static Quaternion fromMatrix(mat4 m);
	static void fromAxisAngle(Quaternion& q, vec3 axis, float angle);
};

NEPHILIM_NS_END
#endif // NephilimQuaternion_h__
