#ifndef NephilimTexture2D_h__
#define NephilimTexture2D_h__

#include <Nephilim/Foundation/Asset.h>
#include <Nephilim/Foundation/String.h>
#include <Nephilim/Foundation/Vector.h>

NEPHILIM_NS_BEGIN

class GDI_Texture2D;
class Image;

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
class NEPHILIM_API Texture2D : public Asset
{
public:

	/// The actual texture resource, implemented in a low level renderer
	GDI_Texture2D* _impl = nullptr;

public:

	/// Construct the uninitialized texture
	Texture2D();

	/// Ensure destruction of the resource
	virtual ~Texture2D();

	/// Create the texture with the given size
	bool create(std::size_t width, std::size_t height);

	/// Set the texture as repeating for sampling outside its area
	void setRepeated(bool repeated);

	/// Set the texture filtering mode
	void setSmooth(bool smooth);

	/// Loads a texture from disk with the global graphics API
	/// Should be avoided in favor of the central asset loading
	bool loadFromFile(const String& filename);

	/// Loads the texture from a image buffer
	/// Should be avoided in favor of the central asset loading
	bool loadFromImage(const Image& image);

	/// Retrieve the texture from the GPU and into an image
	/// Does not work in OpenGL ES platforms. An warning is logged in such platforms.
	/// Returns false if the operation fails
	bool copyToImage(Image& image) const;

	/// A texture is a rectangle, with finite size
	Vector2<int> getSize() const;

	/// Updates a given region inside the texture with an array of pixels
	void update(const Uint8* pixels, unsigned int width, unsigned int height, unsigned int x, unsigned int y);

	/// Update the texture on the GPU with an array of pixels
	void update(const Uint8* pixels);

	/// Update the texture on the GPU from an image
	void update(const Image& image);

	/// Get the maximum size a texture can be
	static std::size_t getMaximumSize();
};

NEPHILIM_NS_END
#endif // NephilimTexture2D_h__
