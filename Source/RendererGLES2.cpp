#include <Nephilim/RendererGLES2.h>
#include <Nephilim/Shader.h>
#include <Nephilim/CGL.h>
#include <Nephilim/Matrix.h>
#include <Nephilim/Logger.h>
#include <Nephilim/Surface.h>

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
	"	if(textured == 1) gl_FragColor = texture2D(texture, texUV) * fragColor;\n"
	"   else gl_FragColor = fragColor;\n"
	"}\n";

RendererGLES2::RendererGLES2()
: Renderer()
{
	m_type = OpenGLES2;
	m_name = "OpenGL ES 2.0";

	m_shader = new Shader();
	m_shader->loadShader(Shader::VertexUnit, gVertexSource);
	m_shader->loadShader(Shader::FragmentUnit, gFragmentSource);
	m_shader->addAttributeLocation(0, "vertex");
	m_shader->addAttributeLocation(1, "color");
	m_shader->addAttributeLocation(2, "texCoord");
	m_shader->create();
	m_shader->bind();

	m_shader->setUniformMatrix("projection", mat4().get());
	m_shader->setUniformMatrix("view", mat4().get());
	m_shader->setUniformMatrix("model", mat4().get());
}

/// Draw a vertex array
void RendererGLES2::draw(const VertexArray2D& varray)
{ 
	const char* data  = reinterpret_cast<const char*>(&varray.m_vertices[0]);
	
	if(varray.m_textured) m_shader->setUniformi("textured", 1);
	else m_shader->setUniformi("textured", 0);

	m_shader->setUniformi("texture", 0);
	
	//model
/*	if(modelMatrix)
	{
		m_shader->setUniformMatrix("model", modelMatrix);
	}
	*/

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

	//model
/*	if(modelMatrix)
	{
		bool r = m_shader->setUniformMatrix("model", mat4().get());
		modelMatrix = NULL;
	}*/
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