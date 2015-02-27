#ifndef NephilimFoundationTransform_h__
#define NephilimFoundationTransform_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Matrix.h>
#include <Nephilim/Foundation/Quat.h>
#include <Nephilim/World/Component.h>

NEPHILIM_NS_BEGIN

/**
	\class ComponentTransform
	\brief 3D transform for a entity, scale + rotation + translation
*/
class NEPHILIM_API Transform : public Component
{
public:

	Int32 parent = -1;
	mat4 matrix;

	/// Represents the 3D object rotation
	Quat     rotation;

	/// Represents the 3D position of the object
	Vector3D position;

	/// Represents the 3D scale of the object
	Vector3D scale;

public:

	/// Initialize the transform to the "identity" transform
	/// position(0,0,0), orientation as identity (down the -z axis), and a scale of 1
	Transform();

	/// Construct from a position
	Transform(vec3 pos);

	/// Set the position from a vec3
	void setPosition(const vec3& p);

	/// Set the position from a vec2
	void setPosition(const vec2& p);

	/// Set the position from 3 floats
	void setPosition(float px, float py);

	/// Set the position from 3 floats
	void setPosition(float px, float py, float pz);

	/// Get the position of this transform
	vec3 getPosition();

	/// Makes this transform orient itself to the target
	void setLookAt(Vector3D target);

	void rotateByEulerAngles(float x_axis, float y_axis, float z_axis);
	void rotateByAxisAngle(float angle, float x_axis, float y_axis, float z_axis);

	vec3 getForwardVector();
	vec3 getRightVector();

	mat4 getMatrix();
};

NEPHILIM_NS_END
#endif // NephilimFoundationTransform_h__
