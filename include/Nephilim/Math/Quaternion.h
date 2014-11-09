#ifndef NephilimQuaternion_h__
#define NephilimQuaternion_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Vectors.h>
#include <Nephilim/Matrix.h>
#include <Nephilim/Math/Spherical.h>

NEPHILIM_NS_BEGIN


class Quaternion
{
public:
	Quaternion();

	Quaternion(float nx, float ny, float nz, float nw);

	Quaternion(vec3 v, float nw);

	vec3 xyz();

	vec4 toAxisAngles();

	vec3 eulerAngles();

	Spherical sphericalCoordinates();

	void rotateEulerAngles(float ax, float ay, float az);

	void rotateAxisAngle(float angle, float ax, float ay, float az);

	float lengthSquared();

	Quaternion operator*(const Quaternion& q2);

	Quaternion operator*(float scalar);

	Quaternion operator+(const Quaternion& q2);

	inline Quaternion& operator*=(float scalar);

	void normalize();  

	float x,y,z,w;

	mat4 toMatrix();
	
	static Quaternion fromMatrix(mat4 m);
	static void fromAxisAngle(Quaternion& q, vec3 axis, float angle);

	static Quaternion slerp(Quaternion& q1, Quaternion& q2, float blend);

	static Quaternion lerp(Quaternion& q1, Quaternion& q2, float blend);

	static float dot(Quaternion& q1, Quaternion& q2);

	static Quaternion identity;
};

NEPHILIM_NS_END
#endif // NephilimQuaternion_h__
