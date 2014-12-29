#ifndef NephilimGraphicsShader_h__
#define NephilimGraphicsShader_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>

#include <vector>

NEPHILIM_NS_BEGIN

/**
	\ingroup Graphics
	\class Shader
	\brief Single shader program (abstract)

	Shader objects correspond to one GLSL/HLSL/Other shader program, usually located in the GPU
	for rendering geometry.

	This class controls the lifecyle of the shader programs too. Each shader is specific to its
	rendering API, and is destroyed when the shader goes out of scope.

	Its ideal to have one shader per different material, usually also an additional one per light type.
	Its up to the implementation to manage shader source and management, this is just a resource handler.
*/
class NEPHILIM_API Shader
{
public:
	/// Constructs an uninitialized shader
	/// The program identifier is initialized at 0.
	/// This means an invalid shader, which causes, not guaranteed, that the fixed-pipeline is activated
	Shader();

	/// Safe release
	~Shader();

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

	void pff();

	unsigned int getIdentifier();

public:
	unsigned int m_id; ///< Internal shader identifier
	std::vector<std::pair<ShaderTypes, unsigned int> > m_shaders; ///< List of compiled shaders
	std::vector<std::pair<unsigned int, String> > m_attribs; ///< List of pre-binded attribute locations
};

NEPHILIM_NS_END
#endif // NephilimGraphicsShader_h__
