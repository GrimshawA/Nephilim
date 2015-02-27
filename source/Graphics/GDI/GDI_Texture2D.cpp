#include <Nephilim/Graphics/GDI/GDI_Texture2D.h>

NEPHILIM_NS_BEGIN

/// Retrieve the texture from the GPU and into an image
/// Does not work in OpenGL ES platforms. An warning is logged in such platforms.
/// Returns false if the operation fails
bool GDI_Texture2D::copyToImage(Image& image) const
{
	return false;
}

/// Create or recreate the texture with a given size
bool GDI_Texture2D::create(unsigned int width, unsigned int height)
{
	return false;
}

/// Loads the texture from disk
bool GDI_Texture2D::loadFromFile(const String& filename)
{
	return false;
}


/// Sets the texture repeat mode
void GDI_Texture2D::setRepeated(bool repeated)
{

}

/// Set the texture filtering mode
void GDI_Texture2D::setSmooth(bool smooth)
{

}

/// Loads the texture from a image buffer
bool GDI_Texture2D::loadFromImage(const Image& image)
{
	return false;
}


/// Updates a given region inside the texture with an array of pixels
void GDI_Texture2D::update(const Uint8* pixels, unsigned int width, unsigned int height, unsigned int x, unsigned int y)
{

}

/// Update the texture on the GPU with an array of pixels
void GDI_Texture2D::update(const Uint8* pixels)
{
}

/// Update the texture on the GPU from an image
void GDI_Texture2D::update(const Image& image)
{
}

NEPHILIM_NS_END