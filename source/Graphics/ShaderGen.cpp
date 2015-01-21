#include <Nephilim/ShaderGen.h>
#include <Nephilim/Graphics/Shader.h>

static const char gVertexShader2[] =
	"#version 330\n"

	"in vec4 vPosition;\n"
	"in vec4 ccc;"
	"uniform mat4 projectionMatrix;"
	"uniform mat4 modelViewMatrix;"
	"out vec4 fcolor;"
	"void main() {\n"
	"  gl_Position = projectionMatrix * modelViewMatrix * vPosition;\n"
	"  fcolor = ccc;"
	"}\n";

static const char gFragmentShader2[] = 
	"#version 330\n"
	"in vec4 fcolor;"
	"out vec4 output;"
	"void main() {\n"
	"  output = fcolor;\n"
	"}\n";

static const char gVertexShader[] = 
	"attribute vec4 vPosition;\n"
	"attribute vec4 ccc;"
	"varying vec4 finalColor;"
	"uniform mat4 projectionMatrix;"
	"uniform mat4 modelViewMatrix;"
	"void main() {\n"
	"  gl_Position = projectionMatrix * modelViewMatrix * vPosition;\n"
	"  finalColor = ccc;"
	"}\n";

static const char gFragmentShader[] = 
	"precision mediump float;\n"
	"varying vec4 finalColor;"
	"void main() {\n"
	"  gl_FragColor = finalColor;\n"
	"}\n";

static const char gV1[] = 
	"#version 330\n"

	"layout(location = 0)in vec4 vertex;\n"
	"void main() {\n"
	"  gl_Position = vertex;\n"
	"}\n";

static const char gF1[] = 
	"void main() {\n"
	"  gl_FragColor = vec4(1, 0, 0, 1);\n"
	"}\n";

NEPHILIM_NS_BEGIN

/// Prepares the default shader
bool ShaderGen::prepareDefault(Shader& shader)
{
	shader.loadShader(Shader::VertexUnit, gV1);
	shader.loadShader(Shader::FragmentUnit, gF1);
	shader.create();

	return true;
}

/// Returns the source code for the default vertex shader
String ShaderGen::getDefaultVertexShader()
{
	return "";
}

/// Returns the source code for the default fragment shader
String ShaderGen::getDefaultFragmentShader()
{
	return "";
}

/// Starts a clear source with VertexUnit composing mode
ShaderComposer::ShaderComposer()
{

}

/// Change the composer into another shader type
void ShaderComposer::setUnitType(ShaderComposer::ShaderType shaderType)
{

}

/// Clear the source
void ShaderComposer::clear()
{

}

/// Declare a vertex attribute array in the shader source
void ShaderComposer::addAttribute(const String& name)
{

}


NEPHILIM_NS_END