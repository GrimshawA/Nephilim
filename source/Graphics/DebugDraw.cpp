#include <Nephilim/Graphics/DebugDraw.h>
#include <Nephilim/Graphics/GraphicsDevice.h>
#include <Nephilim/CGL.h>
#include <Nephilim/Foundation/Logging.h>
#include <Nephilim/Geometry.h>
#include <Nephilim/Math/Math.h>

NEPHILIM_NS_BEGIN

DebugDraw::DebugDraw(GraphicsDevice* graphics)
: _graphics(graphics)
{

}

/// Draw a colored box
void DebugDraw::drawBox(float x, float y, float z, float size, Color a)
{
	_graphics->setDefaultTexture();

	GeometryData box;
	box.addBox(size, size, size);
	box.setAllColors(a);
	_graphics->setModelMatrix(mat4::translate(x, y, z));
	_graphics->draw(box);

	box.setAllColors(Color::Black);
	box.m_primitive = Render::Primitive::LineLoop;
	_graphics->draw(box);
}

NEPHILIM_NS_END