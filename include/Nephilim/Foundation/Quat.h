#ifndef NephilimQuaternion_h__
#define NephilimQuaternion_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Vector.h>
#include <Nephilim/Foundation/Matrix.h>
#include <Nephilim/Foundation/Spherical.h>

NEPHILIM_NS_BEGIN

/**
	\class Quaternion
	\brief Represents a rotation in three dimensions without locking issues
*/
class Quat
{
public:
	Quat();

	Quat(float nx, float ny, float nz, float nw);

	Quat(vec3 v, float nw);

	vec3 xyz();

	vec4 toAxisAngles();

	vec3 eulerAngles();

	Spherical sphericalCoordinates();

	void rotateEulerAngles(float ax, float ay, float az);

	void rotateAxisAngle(float angle, float ax, float ay, float az);

	float lengthSquared();

	Quat operator*(const Quat& q2);

	Quat operator*(float scalar);

	Quat operator+(const Quat& q2);

	inline Quat& operator*=(float scalar);

	void normalize();  

	float x,y,z,w;

	mat4 toMatrix();
	
	static Quat fromMatrix(mat4 m);
	static void fromAxisAngle(Quat& q, vec3 axis, float angle);

	static Quat slerp(Quat& q1, Quat& q2, float blend);

	static Quat lerp(Quat& q1, Quat& q2, float blend);

	static float dot(Quat& q1, Quat& q2);

	/// Equivalent to mat4::rotatez
	static Quat rotatez(float angle);

	/// Equivalent to mat4::rotatey
	static Quat rotatey(float angle);

	/// Equivalent to mat4::rotatex
	static Quat rotatex(float angle);

	static Quat identity;
};

NEPHILIM_NS_END
#endif // NephilimQuaternion_h__
