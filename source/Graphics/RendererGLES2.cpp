#include <Nephilim/Graphics/GLES2/RendererGLES2.h>
#include <Nephilim/Graphics/Shader.h>
#include <Nephilim/CGL.h>
#include <Nephilim/Matrix.h>
#include <Nephilim/Logger.h>
#include <Nephilim/Window.h>

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

static const char gVertexSource[] = 
	"attribute vec4 vertex;\n"
	"attribute vec4 color;\n"
	"attribute vec2 texCoord;\n"
	"varying vec4 fragColor;\n"
	"varying vec2 texUV;\n"
	"uniform mat4 projection;\n"
	"uniform mat4 model;\n"
	"uniform mat4 view;\n"
	"void main() {\n"
	"  gl_Position = projection * view * model * vertex;\n"
	"  fragColor = color;\n"
	"  texUV = texCoord;\n"
	"}\n";

static const char gFragmentSource[] = 
	"precision mediump float;\n"
	"varying vec4 fragColor;\n"
	"varying vec2 texUV;\n"
	"uniform int textured;\n"
	"uniform sampler2D texture;\n"
	"void main() {\n"
	"	gl_FragColor = texture2D(texture, texUV) * fragColor;\n"
	"}\n";

RendererGLES2::RendererGLES2()
: GraphicsDevice()
{
	m_type = OpenGLES2;
	m_name = "OpenGL ES 2.0";

	reloadDefaultShader();
}

/// This will cancel all shader-related settings and activate the default shader/fixed pipeline
void RendererGLES2::setDefaultShader()
{
	m_defaultShader.bind();
	m_activeShader = &m_defaultShader;
}

void RendererGLES2::reloadDefaultShader()
{
	m_defaultShader.release();
	m_defaultShader.loadShader(Shader::VertexUnit, gVertexSource);
	m_defaultShader.loadShader(Shader::FragmentUnit, gFragmentSource);
	m_defaultShader.addAttributeLocation(0, "vertex");
	m_defaultShader.addAttributeLocation(1, "color");
	m_defaultShader.addAttributeLocation(2, "texCoord");
	m_defaultShader.create();
	m_defaultShader.bind();

	m_defaultShader.setUniformMatrix("projection", m_projection.get());
	m_defaultShader.setUniformMatrix("view", m_view.get());
	m_defaultShader.setUniformMatrix("model", m_model.get());
}

/// Draw a vertex array
void RendererGLES2::draw(const VertexArray2D& varray, const RenderState& state)
{ 
	if(!m_activeShader)
	{
		return;
	}

	const char* data  = reinterpret_cast<const char*>(&varray.m_vertices[0]);

	m_activeShader->setUniformi("texture", 0);

	enableVertexAttribArray(0);
	enableVertexAttribArray(1);
	enableVertexAttribArray(2);

	setVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(VertexArray2D::Vertex), data + 0);
	setVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, true, sizeof(VertexArray2D::Vertex), data + 8);
	setVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(VertexArray2D::Vertex), data + 12);

	drawArrays(varray.geometryType, 0, varray.m_vertices.size());

	disableVertexAttribArray(0);
	disableVertexAttribArray(1);
	disableVertexAttribArray(2);
}

/// Set the current projection matrix
void RendererGLES2::setProjectionMatrix(const mat4& projection)
{
	GraphicsDevice::setProjectionMatrix(projection);
	if(m_activeShader) m_activeShader->setUniformMatrix("projection", projection.get());
}

/// Set the current view matrix
void RendererGLES2::setViewMatrix(const mat4& view)
{
	GraphicsDevice::setViewMatrix(view);
	if(m_activeShader) m_activeShader->setUniformMatrix("view", view.get());
}

/// Set the current model matrix
void RendererGLES2::setModelMatrix(const mat4& model)
{
	GraphicsDevice::setModelMatrix(model);
	if(m_activeShader) m_activeShader->setUniformMatrix("model", model.get());
}

void RendererGLES2::applyView(const View &view)
{
/*	if(!m_renderTarget) return;

	IntRect viewport = m_surface->getViewport(view);
	int top = m_surface->getHeight() - (viewport.top + viewport.height);
	glViewport(viewport.left, top, viewport.width, viewport.height);

	m_shader->setUniformMatrix("projection", view.getTransform().getMatrix());*/
}


/*
void RendererGLES2::drawDebugCircle(Vec2f center, float radius, Vec2f axis, Color color)
{
	VertexArray varray(Render::Primitive::TriangleFan, 0);
	const float k_segments = 32.0f;
	const float k_increment = 2.0f * 3.14159 / k_segments;
	float theta = 0.0f;
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int i = 0; i < k_segments; ++i)
	{
		Vec2f v = center + Vec2f(cosf(theta), sinf(theta)) * radius;
		theta += k_increment;
		varray.append(Vertex(v, color, Vec2f()));
	}

	glBlendFunc (GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_BLEND);

	draw(varray);
}
*/

NEPHILIM_NS_END