#include <Nephilim/World/Components/ACameraComponent.h>

NEPHILIM_NS_BEGIN

ACameraComponent::ACameraComponent()
: up(0.f, 1.f, 0.f)
, eye(0.f, 20.f, 20.f)
, x(0.f)
, y(20.f)
, z(20.f)
, mOrtho(false)
, zNear(1.f)
, zFar(800.f)
, fieldOfView(90.f)
, size(1.f, 1.f)
{
	
}

/// Returns the world point in screen homogeneous coordinates (-1 to 1)
Vector2D ACameraComponent::worldToHomogeneous(Vector3D point)
{
	Vector3D cameraSpacePoint = t.getMatrix().inverse() * point;

	// Project it
	Vector4D projectedPoint = getProjection() * Vector4D(cameraSpacePoint, 1.f);

	return Vector2D(projectedPoint.x / projectedPoint.w, projectedPoint.y / projectedPoint.w);
}

void ACameraComponent::setSize(float width, float height)
{
	size.x = width;
	size.y = height;
}

/// Returns a ready projection matrix for these configs
mat4 ACameraComponent::getProjection()
{
	if (mOrtho)
	{
		return mat4::ortho(0.f, size.x, 0.f, size.y, 1.f, 4000.f);
	}
	else
	{
		return mat4::perspective(70.f, static_cast<float>(screenWidth) / static_cast<float>(screenHeight), 0.05f, 5000.f);
	}
}

/// Get a combined matrix for this camera, projection * view
mat4 ACameraComponent::getCombinedMatrix()
{
	return getProjection() * t.getMatrix().inverse();
}

/// Static: Unprojects a point from NDC to a world-space Ray
/// (This function may move. An helper function to save boilerplate code)
/// Outputs a ray with origin at the NEAR plane, at mouse coordinate, and direction towards where camera is looking
/// mouse input must be already normalized (-1 to 1) on both dimensions
Ray ACameraComponent::UnProjectPoint(const mat4& projection, const mat4& view, Vector2D mouse)
{
	vec4 camera_near(mouse.x, mouse.y, -1.f, 1.f);
	vec4 camera_far(mouse.x, mouse.y, 0.f, 1.f);

	vec4 view_space_position = projection.inverse() * camera_near;
	view_space_position.x /= view_space_position.w;
	view_space_position.y /= view_space_position.w;
	view_space_position.z /= view_space_position.w;
	view_space_position.w = 1.f;

	vec4 view_space_target = projection.inverse() * camera_far;
	view_space_target.x /= view_space_target.w;
	view_space_target.y /= view_space_target.w;
	view_space_target.z /= view_space_target.w;
	view_space_target.w = 1.f;

	vec4 model_space_position = view.inverse() * view_space_position;
	vec4 model_space_target = view.inverse() * view_space_target;

	//Log("Position: %f %f %f, Target %f %f %f", model_space_position.x,  model_space_position.y ,model_space_position.z, model_space_target.x, model_space_target.y, model_space_target.z);

	vec3 direction = (model_space_target - model_space_position).xyz();
	direction.normalize();
	return Ray(model_space_position.xyz(), direction);
}

NEPHILIM_NS_END
