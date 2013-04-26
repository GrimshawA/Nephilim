#include <Nephilim/Renderer.h>
#include <Nephilim/Surface.h>
#include <Nephilim/CGL.h>
#include <Nephilim/Logger.h>
#include <Nephilim/Drawable.h>

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

Renderer::Renderer()
: m_type(Other)
, m_shader(NULL)
{
	m_primitiveTable[Render::Primitive::Triangles] = static_cast<int>(GL_TRIANGLES);
	m_primitiveTable[Render::Primitive::TriangleFan] = static_cast<int>(GL_TRIANGLE_FAN);
	m_primitiveTable[Render::Primitive::Lines] = static_cast<int>(GL_LINES);
	m_primitiveTable[Render::Primitive::LineLoop] = static_cast<int>(GL_LINE_LOOP);
	m_primitiveTable[Render::Primitive::Points] = static_cast<int>(GL_POINTS);

	setClearColor(Color::Orange);
};

// -- Unimplemented API at Renderer level
void Renderer::setDefaultShader(){}
void Renderer::setShader(Shader& shader){}
void Renderer::drawVertexArray(VertexArray &vertexArray){}

Renderer::Type Renderer::getType()
{
	return m_type;
}

/// Effectively regains control of what texture are bound to all texture units, according to the renderer's data
void Renderer::resetTextures()
{
	glBindTexture(GL_TEXTURE_2D, 0);
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

/// Get the current clear color
Color Renderer::getClearColor()
{
	return m_clearColor;
}

void Renderer::setFramebuffer(Framebuffer& target)
{
	
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
void Renderer::setViewport(float left, float bottom, float width, float height)
{
	glViewport(left * m_target->getSize().x, bottom * m_target->getSize().y, width * m_target->getSize().x, height * m_target->getSize().y);
}

/// Set the viewport as in glViewport()
void Renderer::setViewportInPixels(float left, float bottom, float width, float height)
{
	glViewport(left, bottom, width, height);
}

/// Activates blending with the default mode: Alpha
void Renderer::setDefaultBlending()
{
	setBlendMode(Render::Blend::Alpha);
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

/// Activates the default render target, usually the Surface window
void Renderer::setDefaultTarget()
{
	m_surface->activate();
}

void Renderer::setClippingEnabled(bool enable)
{
	if(enable) glEnable (GL_SCISSOR_TEST);
	else       glDisable(GL_SCISSOR_TEST);
}



/// Draw a debug quad with the given color,angle and dimensions - slow
void Renderer::drawDebugQuad(float x, float y, float angle, float width, float height, Color color)
{
	Transform vtransform;
	vtransform.rotate(angle);
	vtransform.translate(x,y);

	mat4 translation = mat4::translate(x,y,0);

	VertexArray varray(Render::Primitive::Triangles, 6);
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

	//modelMatrix = const_cast<float*>(vtransform.getMatrix());
	draw(varray);
}

/// Draw a debug circle with the given color and radius - slow
void Renderer::drawDebugCircle(Vec2f center, float radius, Vec2f axis, Color color)
{
	VertexArray varray(Render::Primitive::TriangleFan, 0);
	const float k_segments = 32.0f;
	const float k_increment = 2.0f * 3.14159 / k_segments;
	float theta = 0.0f;
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4ub(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, color.a);

	for (int i = 0; i < k_segments; ++i)
	{
		Vec2f v = center + Vec2f(cosf(theta), sinf(theta)) * radius;
		theta += k_increment;
		varray.append(Vertex(v, color, Vec2f()));
	}
	glBlendFunc (GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_BLEND);

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
void Renderer::draw(const VertexArray& varray, const RenderState& state)
{
	TESTLOG("Why are you calling draw on an abstract base class?\n")
}

/// Allows a drawable to draw itself
void Renderer::draw(Drawable &drawable)
{
	drawable.onDraw(this);
}


/// Set the currently active view
void Renderer::setView(const View &view){
	m_currentView = view;
	applyView(m_currentView);
};

/// Activate view and push it to the stack
void Renderer::pushView(const View& view){
	m_viewStack.push(view);
	applyView(view);
};

/// Pop the current active view
void Renderer::popView(){
	m_viewStack.pop();
	if(!m_viewStack.empty()){
		applyView(m_viewStack.top());
	}
};

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


void Renderer::drawCube(float x, float y, float z, float len, Color color){

};

void Renderer::setDefaultViewRect(float x, float y){
	View v;
	v.setRect(0,0,x,y);
	setView(v);
};


/// Clear the bound buffer
void Renderer::clear(){
	glClear(GL_COLOR_BUFFER_BIT);
};


NEPHILIM_NS_END
