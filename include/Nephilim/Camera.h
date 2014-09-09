#ifndef NephilimCamera_h__
#define NephilimCamera_h__

#include <Nephilim/Platform.h>
#include "Vectors.h"
#include "Matrix.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup Graphics
	\class FPSCamera
	\brief Experimental First Person camera class

	This camera only has 3 parameters, position, horizontal rotation and vertical rotation.

	Initially looking at (1,0,0)
*/
class NEPHILIM_API FPSCamera
{
public:
	/// Camera initialization
	FPSCamera();

	/// Rotate the camera's direction a bit
	void rotate(float x, float y);

	/// Get the position of the camera
	vec3 getPosition();

	/// Set the position of the camera
	void setPosition(vec3 position);

	/// Get the direction of the camera, the front
	vec3 getDirection();

	/// Get the view matrix for this camera
	mat4 getMatrix();

private:
	float m_xAngle;   ///< The horizontal rotation
	float m_yAngle;   ///< The vertical rotation
	vec3  m_position; ///< Position of this camera
};

NEPHILIM_NS_END
#endif // NephilimCamera_h__
