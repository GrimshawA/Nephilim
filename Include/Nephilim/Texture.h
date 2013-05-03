#ifndef PARABOLA_IMAGETEXTURE_H
#define PARABOLA_IMAGETEXTURE_H

#include "Platform.h"
#include "Vectors.h"
#include "Strings.h"
#include "Color.h"

NEPHILIM_NS_BEGIN

class Image;
/**
	\ingroup Graphics
	\class Texture
	\brief A 2D OpenGL Texture
*/
class NEPHILIM_API Texture{
public:
	/// Creates a uninitialized texture
	Texture();

	/// Copy to a new texture
	Texture(const Texture& other);

	/// Releases the texture resource
	~Texture();




	enum CoordinateType{
		Pixels,
		Normalized
	};


	void update(const Uint8* pixels);
	void update(const Image& image);
	void setSmooth(bool smooth);
	bool create(unsigned int width, unsigned int height);
	unsigned int getValidSize(unsigned int size);
	/// Copy the texture buffer to an image
	Image copyToImage() const;

	void loadFromImage(Image &image);

	/// Sets the desired transparency on all pixels with the selected color
	void createMaskFromColor(const Color &color, Uint8 alpha = 0);

	bool loadFromFile(const String &path);

	Vec2i getSize() const;

	void bind(CoordinateType coordinateType = Pixels) const;

	void update(const Uint8* pixels, unsigned int width, unsigned int height, unsigned int x, unsigned int y);

	static unsigned int getMaximumSize();

	/// Get the id of the currently bound texture for the currently set texture unit
	static unsigned int getCurrentBoundTexture();

public:

	unsigned int m_texture;
	Vec2i m_size;
	Vec2i m_actualSize;
	bool m_pixelsFlipped;
	bool m_isSmooth;

private:
	
};


	/**
		\ingroup Graphics
		\class RenderImage
		\brief Extends sf::RenderImage
	*/
	/*class RenderImage: public sf::RenderTexture{
	public:

	};*/

NEPHILIM_NS_END
#endif
