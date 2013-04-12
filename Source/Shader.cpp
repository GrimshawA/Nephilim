#include <Nephilim/Shader.h>
#include <Nephilim/CGL.h>
#include <Nephilim/Logger.h>

#include <iostream>
using namespace std;


NEPHILIM_NS_BEGIN

/// Constructs an uninitialized shader
/// The program identifier is initialized at 0.
/// This means an invalid shader, which causes, not guaranteed, that the fixed-pipeline is activated
Shader::Shader()
: m_id(0)
{

}

void Shader::pff()
{
	int total = -1;
	glGetProgramiv( m_id, GL_ACTIVE_UNIFORMS, &total ); 
	for(int i=0; i<total; ++i)  {
		int name_len=-1, num=-1;
		GLenum type = GL_ZERO;
		char name[100];
		glGetActiveUniform( m_id, GLuint(i), sizeof(name)-1,
			&name_len, &num, &type, name );
		name[name_len] = 0;
		cout<< "Uniform: "<<name<<endl;
	}
}


/// Binds variables in the program to predefined location index
/// Just pass the location you want to be assigned to the variable name
/// Calling this function only makes sense BEFORE calling create().
void Shader::addAttributeLocation(unsigned int location, const String& name)
{
	m_attribs.push_back(make_pair(location,name));
}

/// Compiles a shader to be linked when create() is called
bool Shader::loadShader(ShaderTypes type, const char* source)
{
	bool success = false;

	GLuint shader = 0;

	switch(type)
	{
		case VertexUnit:	shader = glCreateShader(GL_VERTEX_SHADER);	break;
		case FragmentUnit:	shader = glCreateShader(GL_FRAGMENT_SHADER);   break;
	}

	if (shader) {
		glShaderSource(shader, 1, &source, NULL);
		glCompileShader(shader);
		GLint compiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			GLint infoLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
			if (infoLen) {
				char* buf = new char[infoLen];
				if (buf) {
					glGetShaderInfoLog(shader, infoLen, NULL, buf);
					PRINTLOG("GLSL", "Failed to load shader: %s\n", buf);
					delete [] buf;
				}
				glDeleteShader(shader);
				shader = 0;
			}
		}
		else
		{
			m_shaders.push_back(std::make_pair(type, static_cast<unsigned int>(shader)));
			success = true;
		}
	}

	return success;
}

/// Binds the shader to the GPU
void Shader::bind()
{
	glUseProgram(static_cast<GLuint>(m_id));
}

/// Creates and links the program from previously compiled unit processors
bool Shader::create()
{
	// There must be some shaders to create a program
	if(m_shaders.empty()) return false;

	bool success = false;

	GLuint id = glCreateProgram();
	if(id)
	{
		// Bind attribute locations
		for(std::vector<std::pair<unsigned int, String> >::iterator it = m_attribs.begin(); it != m_attribs.end(); ++it)
		{
			glBindAttribLocation(id, static_cast<GLuint>(it->first), static_cast<const GLchar*>(it->second.c_str()));
		}

		// Attach compiled shaders
		for(std::vector<std::pair<ShaderTypes, unsigned int> >::iterator it = m_shaders.begin(); it != m_shaders.end(); ++it)
		{
			glAttachShader(id, static_cast<GLuint>(it->second));
		}

		// Link the program
		glLinkProgram(id);

		GLint linkStatus = GL_FALSE;
		glGetProgramiv(id, GL_LINK_STATUS, &linkStatus);
		if (linkStatus != GL_TRUE) {

			// -- re do
			GLint bufLength = 0;
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &bufLength);
			if (bufLength) {
				char* buf = new char[bufLength+1];
				if (buf) {
					glGetProgramInfoLog(id, bufLength, NULL, buf);
					buf[bufLength] = '\0';
					String mstr(buf);
					mstr.removeCharacter('\r');
					mstr.removeCharacter('\n');
					PRINTLOG("GLSL", "Failed to link shader program(%d): %s\n",mstr.length(), mstr.c_str());
					delete [] buf;
				}
			}
			// --

			glDeleteProgram(id);
			id = 0;
		}
		else success = true;
	}
	m_id = static_cast<unsigned int>(id);
	return success;
}

void Shader::setUniformi(const String& uniform, int value)
{
	bind();
	GLint uniform_id = glGetUniformLocation(m_id, uniform.c_str());
	if(uniform_id != -1)
	{
		glUniform1i(uniform_id, value);
	}
}

bool Shader::setUniformMatrix(const String& uniform, const float* values)
{
	bind();
	GLint uniform_id = glGetUniformLocation(m_id, uniform.c_str());
	if(uniform_id != -1)
	{
		glUniformMatrix4fv(uniform_id, 1, GL_FALSE, values);
		return true;
	}
	return false;
}



/// Returns whether or not shaders can be used at the moment
/// The result of this function depends primarily on the machine you're running the program on
bool Shader::isAvailable()
{
	return true;
}

/// Returns the internal id of the currently in-use program by OpenGL
unsigned int Shader::getCurrentActiveProgram()
{
	GLint id;
	glGetIntegerv(GL_CURRENT_PROGRAM, &id);
	return static_cast<unsigned int>(id);
}

/// Returns the string
String Shader::getVersion()
{
	const GLubyte* str = glGetString(GL_SHADING_LANGUAGE_VERSION);
	return reinterpret_cast<const char*>(str);
}

NEPHILIM_NS_END
