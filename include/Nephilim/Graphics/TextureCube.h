#ifndef NephilimGraphicsTextureCube_h__
#define NephilimGraphicsTextureCube_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Vector.h>

NEPHILIM_NS_BEGIN

/**
	\ingroup Graphics
	\class TextureCube
	\brief Represents a cubemap texture agnostic to the graphics API

*/
class NEPHILIM_API TextureCube
{
public:
	virtual void test() = 0;
};

NEPHILIM_NS_END
#endif // NephilimGraphicsTextureCube_h__
