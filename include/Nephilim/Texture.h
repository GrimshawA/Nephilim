#ifndef Texture_h__
#define Texture_h__

#include "Platform.h"
#include "Vectors.h"
#include "Strings.h"
#include "Color.h"

NEPHILIM_NS_BEGIN

class Image;
/**
	\ingroup Graphics
	\class Texture
	\brief OpenGL Texture. RGBA format - 8 bits per component
*/
class NEPHILIM_API Texture
{
public:
	/// Creates a uninitialized texture
	Texture();

	/// Copy to a new texture
	Texture(const Texture& other);

	/// Releases the texture resource
	~Texture();

	/// Unload the texture
	void unload();

	/// Get the internal OpenGL identifier of this texture
	unsigned int getIdentifier() const;

	/// Update the texture on the GPU with an array of pixels
	void update(const Uint8* pixels);

	/// Update the texture on the GPU from an image
	void update(const Image& image);

	/// Enables smoothing in the texture
	/// When smoothing is enabled, the pixels will be linearly interpolated when the image is scaled
	/// When smoothing is disabled, texturing will always pick the nearest color, with no calculations.
	void setSmooth(bool smooth);

	/// Enables repeating in the texture
	/// When repeating is enabled, texture coordinates bigger than the texture will still be valid, and the end result is a pattern with the texture
	void setRepeated(bool repeated);

	/// Create or recreate the texture with a given size
	bool create(unsigned int width, unsigned int height);

	/// Get a valid power-of-two size - do not use
	unsigned int getValidSize(unsigned int size);

	/// Retrieve the texture from the GPU and into an image
	/// Does not work in OpenGL ES platforms. An warning is logged in such platforms.
	Image copyToImage() const;

	/// Loads directly from an image
	void loadFromImage(Image &image, bool generateMipMaps = false);

	/// Load a texture from a file
	/// This is a proxy for Image::loadFromFile() and then Texture::loadFromImage()
	bool loadFromFile(const String &path);

	/// Get the size of the texture
	Vec2i getSize() const;

	/// Bind this texture to the currently active texture unit
	void bind() const;

	/// Updates a given region inside the texture with an array of pixels
	void update(const Uint8* pixels, unsigned int width, unsigned int height, unsigned int x, unsigned int y);

	/// Get the maximum allowed size of textures
	/// The result will be hardward-dependent
	static unsigned int getMaximumSize();

	/// Get the id of the currently bound texture for the currently set texture unit
	static unsigned int getCurrentBoundTexture();

private:
	unsigned int m_texture; ///< OpenGL texture
	Vec2i m_size;           ///< Requested size of the texture
	Vec2i m_actualSize;     ///< Actual size of the texture in the GPU
	bool m_pixelsFlipped;   ///< Is this texture upside-down?
	bool m_isSmooth;        ///< Is this texture smoothed?
	bool m_isRepeated;      ///< Is this texture repeating?
};

NEPHILIM_NS_END
#endif // Texture_h__