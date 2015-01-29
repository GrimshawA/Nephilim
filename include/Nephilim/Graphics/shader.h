#ifndef NephilimGraphicsShader_h__
#define NephilimGraphicsShader_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>

#include <vector>

NEPHILIM_NS_BEGIN

class GDI_ShaderProgram;

/**
	\class Shader
	\brief Renderer agnostic shader program resource

	A Shader object represents a program to draw geometry with.
	It can be HLSL/GLSL or even other; the drill is to use a 
	graphics device to activate the shader then draw geometry with it.

	The actual platform shader implementation is defined through an interface,
	which the Shader links to. This allows to redirect any shader object to a new
	implementation without even reallocating space for it. Also makes possible to inherit
	Shader for either reason to extend it, composition rocks!
*/
class NEPHILIM_API Shader
{
public:
	
	/// Low-level implementation of the shader (GL; DirectX; others)
	GDI_ShaderProgram* shaderImpl = nullptr;
};

NEPHILIM_NS_END
#endif // NephilimGraphicsShader_h__
