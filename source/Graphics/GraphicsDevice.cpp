#include <Nephilim/Graphics/GraphicsDevice.h>
#include <Nephilim/Graphics/Window.h>
#include <Nephilim/Graphics/CGL.h>
#include <Nephilim/Foundation/Logging.h>
#include <Nephilim/Graphics/Drawable.h>
#include <Nephilim/Foundation/Image.h>

#include <Nephilim/Graphics/IndexArray.h>
#include <Nephilim/Graphics/VertexArray.h>

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

GraphicsDevice::GraphicsDevice()
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
void GraphicsDevice::setDefaultShader(){}
void GraphicsDevice::setShader(Shader& shader){}

GraphicsDevice::Type GraphicsDevice::getType()
{
	return m_type;
}

/// Get the full name of this renderer
String GraphicsDevice::getName()
{
	return m_name;
}

Window* GraphicsDevice::getWindow()
{
	return m_window;
}

/// Set the clear color of the render target
void GraphicsDevice::setClearColor(const Color& color)
{
	m_clearColor = color;
	vec4 c = m_clearColor.normalized();
	glClearColor(c.x, c.y, c.z, c.w);
}

/// Set an hint to the renderer which tells it to prefer shaders by default(true), or to use the fixed pipeline instead
/// By default, it means a direction relation with setDefaultShader(). Applies only to platforms with both options available.
void GraphicsDevice::setShaderUsageHint(bool allow)
{
	m_shaderUsageHint = allow;
}

/// Get a current renderer-global matrix
mat4 GraphicsDevice::getProjectionMatrix()
{
	return m_projection;
}

/// Get a current renderer-global matrix
mat4 GraphicsDevice::getViewMatrix()
{
	return m_view;
}

/// Get a current renderer-global matrix
mat4 GraphicsDevice::getModelMatrix()
{
	return m_model;
}

/// Push client-side geometry to the GPU
/// This is usually slower than using a VBO because the data is uploaded to the GPU every time
void GraphicsDevice::draw(const VertexArray& vertexData)
{
}

/// Get the current clear color
Color GraphicsDevice::getClearColor()
{
	return m_clearColor;
}

void GraphicsDevice::setTarget(RenderTarget& target)
{
	//m_window = &target;
	//m_window->activate();
}

void GraphicsDevice::setDefaultTransforms()
{
	setProjectionMatrix(mat4::identity);
	setViewMatrix(mat4::identity);
	setModelMatrix(mat4::identity);
}

void GraphicsDevice::setDefaultViewport()
{
	setViewport(0.f, 0.f, 1.f, 1.f);
}

/// Set the viewport in target-relative coordinates
/// If you want to set the viewport in pixels, use setViewportInPixels()
void GraphicsDevice::setViewport(float left, float top, float width, float height)
{
	int bottom = m_window->getSize().y - (top*m_window->getSize().y + height*m_window->getSize().y);
	glViewport(left * m_window->getSize().x, bottom, width * m_window->getSize().x, height * m_window->getSize().y);
}

/// Set the viewport as in glViewport()
void GraphicsDevice::setViewportInPixels(int left, int top, int width, int height)
{
	int bottom = m_window->getSize().y - (top + height);
	glViewport(left, bottom, width, height);
}

/// Activates blending with the default mode: Alpha
void GraphicsDevice::setDefaultBlending()
{
	setBlendMode(Render::Blend::Alpha);
	glBlendEquation(GL_FUNC_ADD);
}

void GraphicsDevice::reloadDefaultShader()
{
}

void GraphicsDevice::setBlendMode(Render::Blend::Mode mode)
{
	setBlendingEnabled(true);

	switch(mode)
	{
		case Render::Blend::Add:
		{
			glBlendFunc(GL_ONE, GL_ONE);
		}
		break;

		case Render::Blend::AddAlpha:
			{
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);				
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

void GraphicsDevice::setBlendingEnabled(bool enable)
{
	if(enable) glEnable(GL_BLEND);
	else		glDisable(GL_BLEND);
}

void GraphicsDevice::setDefaultTarget()
{
	m_window->activate();
}

void GraphicsDevice::setClippingEnabled(bool enable)
{
	if(enable) glEnable (GL_SCISSOR_TEST);
	else       glDisable(GL_SCISSOR_TEST);
}

/// Resets the scissor clipping rectangle to the full target
void GraphicsDevice::resetClippingRect()
{

}

/// Set the scissor clipping rectangle, it cannot exceed the current rectangle
/// You can only request a sub-region of the current clipping area, unless you call resetClippingRect() first
void GraphicsDevice::setClippingRect(FloatRect rect)
{
	glScissor(rect.left, m_window->getSize().y - (rect.top + rect.height), rect.width, rect.height);
}

void GraphicsDevice::pushClippingRect(FloatRect rect, bool isNormalized)
{
	setClippingEnabled(true);

	// If its normalized, convert back to pixels for the calculations
	if(isNormalized)
	{
		rect.left *= getWindow()->width();
		rect.width *= getWindow()->width();
		rect.top *= getWindow()->height();
		rect.height *= getWindow()->height();
	}

	FloatRect finalRect;

	if(m_scissorStack.empty())
	{
		// compare against the full window size
		finalRect = FloatRect(0, 0, m_window->getSize().x, m_window->getSize().y);
	}
	else
	{
		// compare against the previous scissor test
		finalRect = m_scissorStack.top();
	}

	// Crop rect if needed and push
	if(rect.left < finalRect.left)
	{
		rect.width = rect.width - finalRect.left - rect.left;
		rect.left = finalRect.left;
	}
	if(rect.top < finalRect.top)
	{
		rect.height = rect.height - finalRect.top - rect.top;
		rect.top = finalRect.top;
	}
	if(rect.left + rect.width > finalRect.left + finalRect.width)
	{
		rect.width = finalRect.left + finalRect.width - rect.left;
	}
	if(rect.top + rect.height > finalRect.top + finalRect.height)
	{
		rect.height = finalRect.top + finalRect.height - rect.top;
	}	

	// Push the final approved rect to the stack
	m_scissorStack.push(rect);

	// Activate the nested scissor region already cut
	setClippingRect(rect);
}

void GraphicsDevice::popClippingRect()
{
	if (!m_scissorStack.empty())
	m_scissorStack.pop();

	if(m_scissorStack.empty())
		setClippingEnabled(false);
}

void GraphicsDevice::setDepthTestEnabled(bool enable)
{
	if(enable) glEnable(GL_DEPTH_TEST);
	else       glDisable(GL_DEPTH_TEST);
}

void GraphicsDevice::clearDepthBuffer()
{
	glClear(GL_DEPTH_BUFFER_BIT);
}

void GraphicsDevice::clearStencilBuffer()
{
	glClear(GL_STENCIL_BUFFER_BIT);
}

void GraphicsDevice::clearColorBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void GraphicsDevice::clearAllBuffers()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

/// Set the default depth test mode: false
void GraphicsDevice::setDefaultDepthTesting()
{
	setDepthTestEnabled(false);
}

/// Binds the default 1x1 full white texture at texture unit 0
void GraphicsDevice::setDefaultTexture()
{
	glActiveTexture(GL_TEXTURE0);
	m_defaultTexture.bind();
}

/// Draw a debug quad with the given color,angle and dimensions - slow
void GraphicsDevice::drawDebugQuad(float x, float y, float angle, float width, float height, Color color)
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
void GraphicsDevice::drawDebugLine(Vec2f begin, Vec2f end, Color color)
{
	VertexArray2D varray(Render::Primitive::Lines, 2);
	varray[0].position = begin;
	varray[1].position = end;

	varray[0].color = color;
	varray[1].color = color;

	draw(varray);
}

/// Capture the currently bound frame buffer pixles to an image
bool GraphicsDevice::readPixels(Image& image)
{
	int width = static_cast<int>(m_window->getSize().x);
	int height = static_cast<int>(m_window->getSize().y);

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

/// Orders the renderer to reload the default texture etc
void GraphicsDevice::reloadResources()
{
	reloadDefaultShader();

	Image whiteTexture;
	whiteTexture.create(1,1,Color::White);
	m_defaultTexture.loadFromImage(whiteTexture);
}

/// Draw a debug circle with the given color and radius - slow
void GraphicsDevice::drawDebugCircle(Vec2f center, float radius, Vec2f axis, Color color)
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

void GraphicsDevice::drawArrays(Render::Primitive::Type primitiveType, int start, int count)
{
	glDrawArrays(static_cast<GLenum>(m_primitiveTable[primitiveType]), static_cast<GLint>(start), static_cast<GLsizei>(count));
}

void GraphicsDevice::enableVertexAttribArray(unsigned int index)
{
	glEnableVertexAttribArray(static_cast<GLuint>(index));
}

void GraphicsDevice::disableVertexAttribArray(unsigned int index)
{
	glDisableVertexAttribArray(static_cast<GLuint>(index));
}

void GraphicsDevice::setVertexAttribPointer(unsigned int index, int numComponents, int componentType, bool normalized, int stride, const void* ptr)
{
	glVertexAttribPointer(static_cast<GLuint>(index), static_cast<GLint>(numComponents), static_cast<GLenum>(componentType), static_cast<GLboolean>(normalized), static_cast<GLsizei>(stride), static_cast<const GLvoid*>(ptr));
}


/// Draw a vertex array
void GraphicsDevice::draw(const VertexArray2D& varray, const RenderState& state)
{
	Log("Why are you calling draw on an abstract base class?");
}

/// Draw a client-side vertex array with a index array
void GraphicsDevice::draw(const VertexArray& vertexArray, const IndexArray& indexArray)
{
	if (vertexArray._data.size())
	{
		//Log("Drawing a vertex array %d triangles!!!", indexArray.size() / 3);

		enableVertexAttribArray(0);
		enableVertexAttribArray(1);
		enableVertexAttribArray(2);

		setVertexAttribPointer(0, 3, GL_FLOAT, false, vertexArray.stride(), vertexArray.data());
		setVertexAttribPointer(1, 4, GL_FLOAT, false, vertexArray.stride(), &vertexArray._data[0] + vertexArray.getAttributeOffset(1));
		setVertexAttribPointer(2, 2, GL_FLOAT, false, vertexArray.stride(), &vertexArray._data[0] + vertexArray.getAttributeOffset(2));

		glDrawElements(GL_TRIANGLES, indexArray.size(), GL_UNSIGNED_SHORT, indexArray.data());

		disableVertexAttribArray(0);
		disableVertexAttribArray(1);
		disableVertexAttribArray(2);
	}
}

/// Allows a drawable to draw itself
void GraphicsDevice::draw(Drawable &drawable)
{
	drawable.onDraw(this);
}

void GraphicsDevice::setProjectionMatrix(const mat4& projection)
{
	m_projection = projection;
}
void GraphicsDevice::setViewMatrix(const mat4& view)
{
	m_view = view;
}
void GraphicsDevice::setModelMatrix(const mat4& model)
{
	m_model = model;
}

/// The renderer always has a target resolution to operate
/// On windowed mode, its the size of the window's client area and in fullscreen the native resolution we're running at
int GraphicsDevice::resolutionWidth()
{
	return getWindow()->width();
}

/// The renderer always has a target resolution to operate
/// On windowed mode, its the size of the window's client area and in fullscreen the native resolution we're running at
int GraphicsDevice::resolutionHeight()
{
	return getWindow()->height();
}

NEPHILIM_NS_END
