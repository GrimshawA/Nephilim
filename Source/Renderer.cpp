#include <Nephilim/Renderer.h>
#include <Nephilim/Surface.h>
#include <Nephilim/CGL.h>
#include <Nephilim/Logger.h>
#include <Nephilim/Drawable.h>
#include <Nephilim/Image.h>

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

Renderer::Renderer()
: m_type(Other)
, m_shaderUsageHint(true)
{
	m_primitiveTable[Render::Primitive::Triangles] = static_cast<int>(GL_TRIANGLES);
	m_primitiveTable[Render::Primitive::TriangleFan] = static_cast<int>(GL_TRIANGLE_FAN);
	m_primitiveTable[Render::Primitive::TriangleStrip] = static_cast<int>(GL_TRIANGLE_STRIP);
	m_primitiveTable[Render::Primitive::Lines] = static_cast<int>(GL_LINES);
	m_primitiveTable[Render::Primitive::LineLoop] = static_cast<int>(GL_LINE_LOOP);
	m_primitiveTable[Render::Primitive::Points] = static_cast<int>(GL_POINTS);
	m_primitiveTable[Render::Primitive::LineStrip] = static_cast<int>(GL_LINE_STRIP);

	setClearColor(Color::Orange);

	Image whiteTexture;
	whiteTexture.create(1,1,Color::White);
	m_defaultTexture.loadFromImage(whiteTexture);
};

// -- Unimplemented API at Renderer level
void Renderer::setDefaultShader(){}
void Renderer::setShader(Shader& shader){}

Renderer::Type Renderer::getType()
{
	return m_type;
}

/// Get the full name of this renderer
String Renderer::getName()
{
	return m_name;
}

/// Set the clear color of the render target
void Renderer::setClearColor(const Color& color)
{
	m_clearColor = color;
	vec4 c = m_clearColor.normalized();
	glClearColor(c.x, c.y, c.z, c.w);
}

/// Set an hint to the renderer which tells it to prefer shaders by default(true), or to use the fixed pipeline instead
/// By default, it means a direction relation with setDefaultShader(). Applies only to platforms with both options available.
void Renderer::setShaderUsageHint(bool allow)
{
	m_shaderUsageHint = allow;
}

/// Get the model matrix
mat4 Renderer::getModelMatrix()
{
	return m_model;
}

/// Get the current clear color
Color Renderer::getClearColor()
{
	return m_clearColor;
}

void Renderer::setTarget(RenderTarget& target)
{
	m_target = &target;
	m_target->activate();
}

void Renderer::setDefaultTransforms()
{
	setProjectionMatrix(mat4::identity);
	setViewMatrix(mat4::identity);
	setModelMatrix(mat4::identity);
}

void Renderer::setDefaultViewport()
{
	setViewport(0.f, 0.f, 1.f, 1.f);
}

/// Set the viewport in target-relative coordinates
/// If you want to set the viewport in pixels, use setViewportInPixels()
void Renderer::setViewport(float left, float top, float width, float height)
{
	int bottom = m_target->getSize().y - (top*m_target->getSize().y + height*m_target->getSize().y);
	glViewport(left * m_target->getSize().x, bottom, width * m_target->getSize().x, height * m_target->getSize().y);
}

/// Set the viewport as in glViewport()
void Renderer::setViewportInPixels(int left, int top, int width, int height)
{
	int bottom = m_target->getSize().y - (top + height);
	glViewport(left, bottom, width, height);
}

/// Activates blending with the default mode: Alpha
void Renderer::setDefaultBlending()
{
	setBlendMode(Render::Blend::Alpha);
	glBlendEquation(GL_FUNC_ADD);
}

void Renderer::setBlendMode(Render::Blend::Mode mode)
{
	setBlendingEnabled(true);

	switch(mode)
	{
		case Render::Blend::Add:
		{
			glBlendFunc(GL_ONE, GL_ONE);
		}
		break;

		case Render::Blend::Multiply:
		{
			glBlendFunc(GL_DST_COLOR, GL_ZERO);
		}
		break;

		case Render::Blend::Alpha:
		{
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		break;

		case Render::Blend::None:
		{
			glBlendFunc (GL_ONE, GL_ZERO);
		}
		break;
	}
}

void Renderer::setBlendingEnabled(bool enable)
{
	if(enable) glEnable(GL_BLEND);
	else		glDisable(GL_BLEND);
}

void Renderer::setDefaultTarget()
{
	m_surface->activate();
}

void Renderer::setClippingEnabled(bool enable)
{
	if(enable) glEnable (GL_SCISSOR_TEST);
	else       glDisable(GL_SCISSOR_TEST);
}

/// Resets the scissor clipping rectangle to the full target
void Renderer::resetClippingRect()
{

}

/// Set the scissor clipping rectangle, it cannot exceed the current rectangle
/// You can only request a sub-region of the current clipping area, unless you call resetClippingRect() first
void Renderer::setClippingRect(FloatRect rect)
{

}

void Renderer::setDepthTestEnabled(bool enable)
{
	if(enable) glEnable(GL_DEPTH_TEST);
	else       glDisable(GL_DEPTH_TEST);
}

void Renderer::clearDepthBuffer()
{
	glClear(GL_DEPTH_BUFFER_BIT);
}

void Renderer::clearStencilBuffer()
{
	glClear(GL_STENCIL_BUFFER_BIT);
}

void Renderer::clearColorBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::clearAllBuffers()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

/// Set the default depth test mode: false
void Renderer::setDefaultDepthTesting()
{
	setDepthTestEnabled(false);
}

/// Binds the default 1x1 full white texture at texture unit 0
void Renderer::setDefaultTexture()
{
	glActiveTexture(GL_TEXTURE0);
	m_defaultTexture.bind();
}

/// Draw a debug quad with the given color,angle and dimensions - slow
void Renderer::drawDebugQuad(float x, float y, float angle, float width, float height, Color color)
{
	Transform vtransform;
	vtransform.rotate(angle);
	vtransform.translate(x,y);

	mat4 translation = mat4::translate(x,y,0);

	VertexArray2D varray(Render::Primitive::Triangles, 6);
	varray[0].position = Vec2f(width/2,-height/2);
	varray[1].position = Vec2f(-width/2,height/2);
	varray[2].position = Vec2f(-width/2,-height/2);
	varray[3].position = Vec2f(width/2,-height/2);
	varray[4].position = Vec2f(width/2,height/2);
	varray[5].position = Vec2f(-width/2, height/2);

	varray[0].color = color;
	varray[1].color = color;
	varray[2].color = color;
	varray[3].color = color;
	varray[4].color = color;
	varray[5].color = color;

	for(int i = 0; i < 6; i++)
	{
		varray[i].position = vec4(translation * vec4(varray[i].position.x, varray[i].position.y, 0.f, 1.f)).xy();
	}

	draw(varray);
}

/// Draw a debug line with the given color - slow
void Renderer::drawDebugLine(Vec2f begin, Vec2f end, Color color)
{
	VertexArray2D varray(Render::Primitive::Lines, 2);
	varray[0].position = begin;
	varray[1].position = end;

	varray[0].color = color;
	varray[1].color = color;

	draw(varray);
}

/// Capture the currently bound frame buffer pixles to an image
bool Renderer::readPixels(Image& image)
{
	int width = static_cast<int>(m_target->getSize().x);
	int height = static_cast<int>(m_target->getSize().y);

	// copy rows one by one and flip them (OpenGL's origin is bottom while SFML's origin is top)
	std::vector<Uint8> pixels(width * height * 4);
	for (int i = 0; i < height; ++i)
	{
		Uint8* ptr = &pixels[i * width * 4];
		glReadPixels(0, height - i - 1, width, 1, GL_RGBA, GL_UNSIGNED_BYTE, ptr);
	}

	image.create(width, height, &pixels[0]);

	return false;
}

/// Draw a debug circle with the given color and radius - slow
void Renderer::drawDebugCircle(Vec2f center, float radius, Vec2f axis, Color color)
{
	VertexArray2D varray(Render::Primitive::TriangleFan, 0);
	const float k_segments = 32.0f;
	const float k_increment = 2.0f * 3.14159 / k_segments;
	float theta = 0.0f;

	for (int i = 0; i < k_segments; ++i)
	{
		Vec2f v = center + Vec2f(cosf(theta), sinf(theta)) * radius;
		theta += k_increment;
		varray.append(VertexArray2D::Vertex(v, color, Vec2f()));
	}

	/*theta = 0.0f;
	glColor4ub(color.r, color.g, color.b, color.a);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < k_segments; ++i)
	{
		Vec2f v = center + Vec2f(cosf(theta), sinf(theta)) * radius;
		glVertex2f(v.x, v.y);
		theta += k_increment;
	}
	glEnd();*/

	draw(varray);
}

void Renderer::drawArrays(Render::Primitive::Type primitiveType, int start, int count)
{
	glDrawArrays(static_cast<GLenum>(m_primitiveTable[primitiveType]), static_cast<GLint>(start), static_cast<GLsizei>(count));
}

void Renderer::enableVertexAttribArray(unsigned int index)
{
	glEnableVertexAttribArray(static_cast<GLuint>(index));
}

void Renderer::disableVertexAttribArray(unsigned int index)
{
	glDisableVertexAttribArray(static_cast<GLuint>(index));
}

void Renderer::setVertexAttribPointer(unsigned int index, int numComponents, int componentType, bool normalized, int stride, const void* ptr)
{
	glVertexAttribPointer(static_cast<GLuint>(index), static_cast<GLint>(numComponents), static_cast<GLenum>(componentType), static_cast<GLboolean>(normalized), static_cast<GLsizei>(stride), static_cast<const GLvoid*>(ptr));
}


/// Draw a vertex array
void Renderer::draw(const VertexArray2D& varray, const RenderState& state)
{
	Log("Why are you calling draw on an abstract base class?");
}

/// Allows a drawable to draw itself
void Renderer::draw(Drawable &drawable)
{
	drawable.onDraw(this);
}

void Renderer::setProjectionMatrix(const mat4& projection)
{
	m_projection = projection;
}
void Renderer::setViewMatrix(const mat4& view)
{
	m_view = view;
}
void Renderer::setModelMatrix(const mat4& model)
{
	m_model = model;
}

NEPHILIM_NS_END
