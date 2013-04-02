#ifndef ShaderGen_h__
#define ShaderGen_h__

#include "Platform.h"
#include "Strings.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup Graphics
	\class ShaderGen
	\brief GLSL tools for generating portable source code
*/
class NEPHILIM_API ShaderGen
{
public:


	/// Returns the source code for the default vertex shader
	static String getDefaultVertexShader();

	/// Returns the source code for the default fragment shader
	static String getDefaultFragmentShader();
};

NEPHILIM_NS_END
#endif // ShaderGen_h__
