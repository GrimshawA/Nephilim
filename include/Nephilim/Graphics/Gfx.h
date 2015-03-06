#ifndef NephilimGfx_h__
#define NephilimGfx_h__

#include <Nephilim/Graphics/GraphicsDevice.h>

NEPHILIM_NS_BEGIN
/// This namespace includes all graphics functions for accessing the GDI (graphics device interface), to interface with GL, DX etc
namespace gfx
{

/// Set the current program
void setProgram(Shader& program);

/// Set the given vertex buffer as active
void setVertexBuffer(const VertexBuffer& vertexBuffer);

/// Let's a drawable object draw itself
void draw(Drawable& drawable);

/// Use the active window and matrices to get a world position from a screen coordinate
Vector2D ScreenToWorld2D(Vector2<int> point);

};
NEPHILIM_NS_END
#endif // NephilimGfx_h__
