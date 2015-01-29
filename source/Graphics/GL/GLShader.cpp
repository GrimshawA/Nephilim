#include <Nephilim/Graphics/GL/GLShader.h>
#include <Nephilim/Graphics/GL/GLHelpers.h>

#include <Nephilim/Foundation/Logging.h>
#include <Nephilim/Foundation/File.h>

NEPHILIM_NS_BEGIN

/// Constructs an uninitialized shader
/// The program identifier is initialized at 0.
/// This means an invalid shader, which causes, not guaranteed, that the fixed-pipeline is activated
GLShader::GLShader()
: m_id(0)
{
}

/// Safe release
GLShader::~GLShader()
{
	release();
}

/// Reverts the shader back to an unitialized state
void GLShader::release()
{
	if(m_id > 0)
	{
		// Attach compiled shaders
		for(std::vector<std::pair<ShaderTypes, unsigned int> >::iterator it = m_shaders.begin(); it != m_shaders.end(); ++it)
		{
			glDeleteShader(static_cast<GLuint>(it->second));
		}

		glDeleteProgram(m_id);

		m_shaders.clear();
		m_attribs.clear();
		m_id = 0;
	}
}

/// Binds variables in the program to predefined location index
/// Just pass the location you want to be assigned to the variable name
/// Calling this function only makes sense BEFORE calling create().
void GLShader::addAttributeLocation(unsigned int location, const String& name)
{
	m_attribs.push_back(make_pair(location,name));
}

String getFileContents(const String& filename)
{
	File myFile(filename, IODevice::TextRead);
	if(!myFile)
		return "";

	String contents;

	while(!myFile.atEnd())
		contents += myFile.getChar();

	contents += '\0';

	return contents;
}

/// Compiles a shader to be linked when create() is called, from a source file
bool GLShader::loadShaderFromFile(ShaderTypes type, const String& filename)
{
	bool success = false;

	GLuint shader = 0;

	switch(type)
	{
	case VertexUnit:	shader = glCreateShader(GL_VERTEX_SHADER);	break;
	case FragmentUnit:	shader = glCreateShader(GL_FRAGMENT_SHADER);   break;
	}

	String shaderCode = getFileContents(filename);
	const char* source = shaderCode.c_str();

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
					//PRINTLOG("GLSL", "Failed to load shader: %s\n", buf);
					String mstr(buf);
					//mstr.removeCharacter('\r');
					//mstr.removeCharacter('\n');
					//std::cout << "GLSL: " << mstr << std::endl;
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

/// Compiles a shader to be linked when create() is called
bool GLShader::loadShader(ShaderTypes type, const char* source)
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
					//PRINTLOG("GLSL", "Failed to load shader: %s\n", buf);
					String mstr(buf);
					//mstr.removeCharacter('\r');
					//mstr.removeCharacter('\n');
					//std::cout << "GLSL: " << mstr << std::endl;
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
void GLShader::bind() const
{
	glUseProgram(static_cast<GLuint>(m_id));
}

unsigned int GLShader::getIdentifier()
{
	return m_id;
}


/// Creates and links the program from previously compiled unit processors
bool GLShader::create()
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
					//std::cout << "GLSL: " << mstr << std::endl;
					//PRINTLOG("GLSL", "Failed to link shader program(%d): %s\n",mstr.length(), mstr.c_str());
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

void GLShader::setUniformi(const String& uniform, int value)
{
	bind();
	GLint uniform_id = glGetUniformLocation(m_id, uniform.c_str());
	if(uniform_id != -1)
	{
		glUniform1i(uniform_id, value);
	}
}

bool GLShader::setUniformMatrix(const String& uniform, const float* values)
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

bool GLShader::setUniformVec4(const String& uniform, const float* values)
{
	bind();
	GLint uniform_id = glGetUniformLocation(m_id, uniform.c_str());
	if(uniform_id != -1)
	{
		glUniform4fv(uniform_id, 1, values);
		return true;
	}
	return false;
}

bool GLShader::setUniformVec3(const String& uniform, const float* values)
{
	bind();
	GLint uniform_id = glGetUniformLocation(m_id, uniform.c_str());
	if(uniform_id != -1)
	{
		glUniform3fv(uniform_id, 1, values);
		return true;
	}
	return false;
}

bool GLShader::setUniformFloat(const String& uniform, float value)
{
	bind();
	GLint uniform_id = glGetUniformLocation(m_id, uniform.c_str());
	if(uniform_id != -1)
	{
		glUniform1f(uniform_id, value);
		return true;
	}
	return false;
}

bool GLShader::setUniformTexture(const String& uniform, int textureUnit)
{
	bind();
	GLint uniform_id = glGetUniformLocation(m_id, uniform.c_str());
	if(uniform_id != -1)
	{
		glUniform1i(uniform_id, textureUnit);
		return true;
	}
	return false;
}

/// Returns whether or not shaders can be used at the moment
/// The result of this function depends primarily on the machine you're running the program on
bool GLShader::isAvailable()
{
	return true;
}

/// Returns the internal id of the currently in-use program by OpenGL
unsigned int GLShader::getCurrentActiveProgram()
{
	GLint id;
	glGetIntegerv(GL_CURRENT_PROGRAM, &id);
	return static_cast<unsigned int>(id);
}

/// Returns the string
String GLShader::getVersion()
{
	const GLubyte* str = glGetString(GL_SHADING_LANGUAGE_VERSION);
	return reinterpret_cast<const char*>(str);
}

NEPHILIM_NS_END
