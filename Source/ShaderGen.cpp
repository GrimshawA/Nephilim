#include <Nephilim/ShaderGen.h>

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


NEPHILIM_NS_BEGIN

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

NEPHILIM_NS_END