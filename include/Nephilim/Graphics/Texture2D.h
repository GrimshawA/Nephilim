#ifndef NephilimTexture2D_h__
#define NephilimTexture2D_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

class GDI_Texture2D;

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
	
	By favoring the underlying implementation by composition,
	Texture2D can be extended for more specialized before and
	even swap low level implementation on the fly.
*/
class NEPHILIM_API Texture2D
{
public:

	/// The actual texture resource, implemented in a low level renderer
	GDI_Texture2D* _impl = nullptr;

public:

	/// Construct the uninitialized texture
	Texture2D();

	/// Ensure destruction of the resource
	virtual ~Texture2D();	
};

NEPHILIM_NS_END
#endif // NephilimTexture2D_h__
