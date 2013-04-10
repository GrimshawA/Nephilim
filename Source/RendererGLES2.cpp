#include <Nephilim/RendererGLES2.h>
#include <Nephilim/Shader.h>
#include <Nephilim/CGL.h>
#include <Nephilim/Logger.h>

NEPHILIM_NS_BEGIN

static const char gVertexSource[] = 
	"attribute vec4 vertex;\n"
	"attribute vec4 color;\n"
	"attribute vec2 texCoord;\n"
	"varying vec4 fragColor;\n"
	"varying vec2 texUV;\n"
	"void main() {\n"
	"  gl_Position = vertex;\n"
	"	fragColor = color;\n"
	"  texUV = texCoord;\n"
	"}\n";

static const char gFragmentSource[] = 
	"precision mediump float;\n"
	"varying vec4 fragColor;\n"
	"varying vec2 texUV;\n"
	"uniform sampler2D texture;\n"
	"void main() {\n"
	"  gl_FragColor = texture2D(texture, texUV);\n"
	"}\n";

RendererGLES2::RendererGLES2()
: Renderer()
{
	m_shader = new Shader();
	m_shader->loadShader(Shader::VertexUnit, gVertexSource);
	m_shader->loadShader(Shader::FragmentUnit, gFragmentSource);
	m_shader->addAttributeLocation(0, "vertex");
	m_shader->addAttributeLocation(1, "color");
	m_shader->addAttributeLocation(2, "texCoord");
	m_shader->create();
	m_shader->bind();
}

/// Draw a vertex array
void RendererGLES2::draw(const VertexArray& varray)
{ 
	const char* data  = reinterpret_cast<const char*>(&varray.m_vertices[0]);
	enableVertexAttribArray(0);
	enableVertexAttribArray(1);
	enableVertexAttribArray(2);
	setVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(Vertex), data + 0);
	setVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, false, sizeof(Vertex), data + 8);
	setVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), data + 12);
	drawArrays(varray.geometryType, 0, varray.m_vertices.size());
	disableVertexAttribArray(0);
	disableVertexAttribArray(1);
	disableVertexAttribArray(2);
}

NEPHILIM_NS_END