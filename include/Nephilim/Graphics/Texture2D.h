#ifndef NephilimTexture2D_h__
#define NephilimTexture2D_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

/**
	\class Texture2D
	\brief Two dimensional texture

	Texture2D is the base class for different two
	dimensional texture implementations. For example,
	DirectX textures are instanced from a DirectX
	DLL from a subclass of Texture2D. A OpenGL
	texture will be subclassed from Texture2D as well and
	instanced appropriately.

	This is so game code can deal with an abstract Texture2D
	object, without worrying about what kind of API will be used
	to render the actual game. This allows for extreme
	flexibility as the games will easily run in new software
	or hardware rendering API's.
*/
class NEPHILIM_API Texture2D
{
public:

};

NEPHILIM_NS_END
#endif // NephilimTexture2D_h__
