#ifndef NephilimRazerComponentCamera_h__
#define NephilimRazerComponentCamera_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Math/Vectors.h>
#include <Nephilim/Math/Matrix.h>
#include <Nephilim/World/Component.h>
#include <Nephilim/Math/Ray.h>

NEPHILIM_NS_BEGIN

/**
	\class CCamera
	\brief 
*/
class NEPHILIM_API CCameraLens : public Component
{
public:
	CCameraLens();

	void setSize(float width, float height);

	vec2 size; /// The size of the ortho camera

	vec3 position;
	vec3 eye;
	vec3 up;

	mat4 cameraTransform;

	float x,y,z; // where the camera is
	float center_x, center_y, center_z;

	bool mOrtho; // is it ortho or perspective
	float fieldOfView;
	float zNear;
	float zFar;

	float screenWidth;
	float screenHeight;

	/// Static: Unprojects a point from NDC to a world-space Ray
	/// (This function may move. An helper function to save boilerplate code)
	/// Outputs a ray with origin at the NEAR plane, at mouse coordinate, and direction towards where camera is looking
	/// mouse input must be already normalized (-1 to 1) on both dimensions
	static Ray UnProjectPoint(const mat4& projection, const mat4& view, Vector2D mouse);

public:
	/// Returns a ready projection matrix for these configs
	mat4 getProjection();
};

NEPHILIM_NS_END
#endif // NephilimRazerComponentCamera_h__
