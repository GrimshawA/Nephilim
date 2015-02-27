#include <Nephilim/Graphics/Texture2D.h>
#include <Nephilim/Graphics/GDI/GDI_Texture2D.h>

// to remove
#include <Nephilim/Graphics/GL/GLTexture.h>

NEPHILIM_NS_BEGIN

/// Construct the uninitialized texture
Texture2D::Texture2D()
: _impl(nullptr)
{

	_impl = new GLTexture2D;
}

/// Ensure destruction of the resource
Texture2D::~Texture2D()
{
	delete _impl;
}

/// Create the texture with the given size
bool Texture2D::create(std::size_t width, std::size_t height)
{
	return _impl->create(width, height);
}

/// A texture is a rectangle, with finite size
Vec2<int> Texture2D::getSize() const
{
	return _impl->getSize();
}

/// Loads a texture from disk with the global graphics API
/// Should be avoided in favor of the central asset loading
bool Texture2D::loadFromFile(const String& filename)
{
	return _impl->loadFromFile(filename);
}

/// Set the texture as repeating for sampling outside its area
void Texture2D::setRepeated(bool repeated)
{
	_impl->setRepeated(repeated);
}

/// Set the texture filtering mode
void Texture2D::setSmooth(bool smooth)
{
	_impl->setSmooth(smooth);
}

/// Loads the texture from a image buffer
/// Should be avoided in favor of the central asset loading
bool Texture2D::loadFromImage(const Image& image)
{
	return _impl->loadFromImage(image);
}

/// Updates a given region inside the texture with an array of pixels
void Texture2D::update(const Uint8* pixels, unsigned int width, unsigned int height, unsigned int x, unsigned int y)
{
	_impl->update(pixels, width, height, x, y);
}

/// Get the maximum size a texture can be
std::size_t Texture2D::getMaximumSize()
{
	return GLTexture2D::getMaximumSize();
}

/// Update the texture on the GPU with an array of pixels
void Texture2D::update(const Uint8* pixels)
{
	_impl->update(pixels);
}

/// Update the texture on the GPU from an image
void Texture2D::update(const Image& image)
{
	_impl->update(image);
}

/// Retrieve the texture from the GPU and into an image
/// Does not work in OpenGL ES platforms. An warning is logged in such platforms.
bool Texture2D::copyToImage(Image& image) const
{
	return true;
}

NEPHILIM_NS_END