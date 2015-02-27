#include <Nephilim/Graphics/Gfx.h>
#include <Nephilim/Graphics/Window.h>

NEPHILIM_NS_BEGIN
namespace gfx
{

/// Set the current program
void setProgram(Shader& program)
{
	GraphicsDevice::instance()->setShader(program);
}

/// Set the given vertex buffer as active
void setVertexBuffer(const VertexBuffer& vertexBuffer)
{
//	GraphicsDevice::instance()->setVertexBuffer(&vertexBuffer);
}

/// Let's a drawable object draw itself
void draw(Drawable& drawable)
{
	GraphicsDevice::instance()->draw(drawable);
}

/// Use the active window and matrices to get a world position from a screen coordinate
Vector2D ScreenToWorld2D(Vec2<int> point)
{
	Vector2D worldPoint(0.f, 0.f);
	Window* windowPtr = GraphicsDevice::instance()->getWindow();
	mat4 cameraMatrix = GraphicsDevice::instance()->getProjectionMatrix() * GraphicsDevice::instance()->getViewMatrix();
	if (windowPtr)
	{
		Vector2D homo = windowPtr->convertToHomogeneousCoordinate(point);
		Vector4D worldCoordinate = cameraMatrix.inverse() * Vector4D(homo.x, homo.y, 0.f, 1.f);

		worldPoint.x = worldCoordinate.x;
		worldPoint.y = worldCoordinate.y;
	}

	return worldPoint;
}

};
NEPHILIM_NS_END