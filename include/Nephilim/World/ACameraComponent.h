#ifndef NephilimWorldACameraComponent_h__
#define NephilimWorldACameraComponent_h__

#include <Nephilim/World/ASceneComponent.h>

#include <Nephilim/Foundation/Vector.h>
#include <Nephilim/Foundation/Matrix.h>
#include <Nephilim/Foundation/Ray.h>

NEPHILIM_NS_BEGIN

/**
	\class ACameraComponent
	\brief Places a camera in the world
*/
class NEPHILIM_API ACameraComponent : public ASceneComponent
{
public:
	
	/// The camera can be set to orthographic or perspective
	bool mOrtho;

	/// Camera size, for defining aspect ratio and ortho size
	vec2 size;

	mat4 cameraTransform;

	float fieldOfView;

	/// ZNear value defines how close to the camera position the "capturing" begins, clips anything before it
	float zNear;
	
	/// ZFar value defins the range this camera can render
	float zFar;
	
public:

	/// Constructs a default camera at (0,0,0) looking down the -Z axis
	ACameraComponent();

	/// Returns the world point in screen homogeneous coordinates (-1 to 1)
	Vector2D worldToHomogeneous(Vector3D point);

	/// Get a combined matrix for this camera, projection * view
	mat4 getCombinedMatrix();

	void setSize(float width, float height);

	/// Returns a ready projection matrix for these configs
	mat4 getProjection();


	/// Static: Unprojects a point from NDC to a world-space Ray
	/// (This function may move. An helper function to save boilerplate code)
	/// Outputs a ray with origin at the NEAR plane, at mouse coordinate, and direction towards where camera is looking
	/// mouse input must be already normalized (-1 to 1) on both dimensions
	static Ray UnProjectPoint(const mat4& projection, const mat4& view, Vector2D mouse);
};

NEPHILIM_NS_END
#endif // NephilimWorldACameraComponent_h__
