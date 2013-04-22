#ifndef Shader_h__
#define Shader_h__

#include "Platform.h"
#include "Strings.h"

#include <vector>

NEPHILIM_NS_BEGIN

/**
	\ingroup Graphics
	\class Shader
	\brief Controls one GLSL shader program

	This class is GLSL version agnostic but it does not any automatic conversion for you.
	Since different GLSL versions have different syntax and usage, you need to account for this in your program.

	It is only possible to activate one shader program at a time.
	Nevertheless, you can compose a shader in many different ways to fullfill different purposes.

	Usually, a shader contains:
	1..n vertex processors (Vertex Shader)
	1..n fragment processors (Pixel Shader)
	others (unused for now - Tesselation,Geometry,etc)

	A shader program can only define one main function per processor type.
*/
class NEPHILIM_API Shader
{
public:
	/// Constructs an uninitialized shader
	/// The program identifier is initialized at 0.
	/// This means an invalid shader, which causes, not guaranteed, that the fixed-pipeline is activated
	Shader();

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

	/// Binds the shader to the GPU
	void bind();

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

	void pff();

public:
	unsigned int m_id; ///< Internal shader identifier
	std::vector<std::pair<ShaderTypes, unsigned int> > m_shaders; ///< List of compiled shaders
	std::vector<std::pair<unsigned int, String> > m_attribs; ///< List of pre-binded attribute locations
};

NEPHILIM_NS_END
#endif // Shader_h__
