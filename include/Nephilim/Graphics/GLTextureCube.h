#ifndef NephilimGraphicsTextureCubeOpenGL_h__
#define NephilimGraphicsTextureCubeOpenGL_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Vectors.h>
#include <Nephilim/Graphics/TextureCube.h>

NEPHILIM_NS_BEGIN

/**
	\ingroup Graphics
	\class GLTextureCube
	\brief OpenGL implementation of cubemaps
*/
class NEPHILIM_API GLTextureCube : public TextureCube
{
public:
	void test();
};


NEPHILIM_NS_END
#endif // NephilimGraphicsTextureCubeOpenGL_h__
