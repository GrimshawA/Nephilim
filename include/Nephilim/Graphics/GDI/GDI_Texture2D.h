#ifndef NephilimGraphicsGDI_Texture2D_h__
#define NephilimGraphicsGDI_Texture2D_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Vector.h>
#include <Nephilim/Foundation/String.h>

NEPHILIM_NS_BEGIN

class Image;

/**
	\class GDI_Texture2D
	\brief Interface for implementing regular textures
*/
class NEPHILIM_API GDI_Texture2D
{
public:

	/// Create or recreate the texture with a given size
	virtual bool create(unsigned int width, unsigned int height);

	/// Retrieve the texture from the GPU and into an image
	/// Does not work in OpenGL ES platforms. An warning is logged in such platforms.
	/// Returns false if the operation fails
	virtual bool copyToImage(Image& image) const;

	/// Get the texture rectangle size
	virtual Vector2<int> getSize() const = 0;

	/// Loads the texture from disk
	virtual bool loadFromFile(const String& filename);

	/// Loads the texture from a image buffer
	virtual bool loadFromImage(const Image& image);

	/// Sets the texture repeat mode
	virtual void setRepeated(bool repeated);

	/// Set the texture filtering mode
	virtual void setSmooth(bool smooth);

	/// Updates a given region inside the texture with an array of pixels
	virtual void update(const Uint8* pixels, unsigned int width, unsigned int height, unsigned int x, unsigned int y);

	/// Update the texture on the GPU with an array of pixels
	virtual void update(const Uint8* pixels);

	/// Update the texture on the GPU from an image
	virtual void update(const Image& image);
};

NEPHILIM_NS_END
#endif // NephilimGraphicsGDI_Texture2D_h__
