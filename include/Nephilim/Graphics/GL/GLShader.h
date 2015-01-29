#ifndef NephilimGraphicsGLShader_h__
#define NephilimGraphicsGLShader_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Graphics/GDI/GDI_ShaderProgram.h>
#include <Nephilim/Foundation/String.h>

#include <vector>

NEPHILIM_NS_BEGIN

/**
	\class GLShader
	\brief Single shader program (OpenGL Shader: GLSL)
*/
class NEPHILIM_API GLShader : public GDI_ShaderProgram
{
public:
	/// Constructs an uninitialized shader
	/// The program identifier is initialized at 0.
	/// This means an invalid shader, which causes, not guaranteed, that the fixed-pipeline is activated
	GLShader();

	/// Safe release
	~GLShader();

	/// Reverts the shader back to an unitialized state
	void release();

	/// Binds variables in the program to predefined location index
	/// Just pass the location you want to be assigned to the variable name
	/// Calling this function only makes sense BEFORE calling create().
	void addAttributeLocation(unsigned int location, const String& name);

	/// Creates and links the program from previously compiled unit processors
	bool create();

	enum ShaderTypes
	{
		VertexUnit = 0,
		FragmentUnit = 1
	};

	/// Compiles a shader to be linked when create() is called
	bool loadShader(ShaderTypes type, const char* source);

	/// Compiles a shader to be linked when create() is called, from a source file
	bool loadShaderFromFile(ShaderTypes type, const String& filename);

	/// Binds the shader to the GPU
	void bind() const;

	/// Returns whether or not shaders can be used at the moment
	/// The result of this function depends primarily on the machine you're running the program on
	static bool isAvailable();

	/// Returns the internal id of the currently in-use program by OpenGL
	/// Returns 0 if none is active.
	static unsigned int getCurrentActiveProgram();

	/// Returns the string
	static String getVersion();

	void setUniformi(const String& uniform, int value);

	bool setUniformMatrix(const String& uniform, const float* values);
	bool setUniformTexture(const String& uniform, int textureUnit);

	bool setUniformVec4(const String& uniform, const float* values);
	bool setUniformVec3(const String& uniform, const float* values);
	bool setUniformFloat(const String& uniform, float value);

	unsigned int getIdentifier();

public:
	unsigned int m_id; ///< Internal shader identifier
	std::vector<std::pair<ShaderTypes, unsigned int> > m_shaders; ///< List of compiled shaders
	std::vector<std::pair<unsigned int, String> > m_attribs; ///< List of pre-binded attribute locations
};

NEPHILIM_NS_END
#endif // NephilimGraphicsGLShader_h__
