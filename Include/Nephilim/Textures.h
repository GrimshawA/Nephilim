#ifndef PARABOLA_IMAGETEXTURE_H
#define PARABOLA_IMAGETEXTURE_H

#include "Platform.h"
#include "Vectors.h"
#include "Strings.h"
#include "Color.h"
#include "ScopedFile.h"
#include <vector>

#ifdef PARABOLA_WINDOWS
#include <windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#endif

#ifdef PARABOLA_ANDROID

#include <GLES/gl.h>
#include <GLUES/glu.h>
#endif


#ifdef PARABOLA_DESKTOP
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#endif

PARABOLA_NAMESPACE_BEGIN	

void reloadTextures();

class ScopedFile;

/**
	\ingroup Graphics
	\class Image
	\brief Extends sf::Image
*/
class Image{
public:
	bool loadFromFile(const String &path);

	bool loadFromStream(ScopedFile* stream);
	void setPixel(unsigned int x, unsigned int y, const Color& color);
	Vec2i getSize() const;

	/// Sets the desired transparency on all pixels with the selected color
	void createMaskFromColor(const Color &color, Uint8 alpha = 0);
	
	void create(unsigned int width, unsigned int height, const Color& color);

	void create(unsigned int width, unsigned int height,const Uint8* pixels);

	const Uint8* getPixelsPtr() const;

#ifdef PARABOLA_NOSFML
	std::vector<Uint8> m_pixels;
	Vec2i m_size;
#elif defined PARABOLA_DESKTOP
	sf::Image myImage;
#endif
};

/**
	\ingroup Graphics
	\class Texture
	\brief Extends sf::Texture
*/
class Texture{
public:
	/// Create an uninitialised texture
	Texture();

	enum CoordinateType{
		Pixels,
		Normalized
	};

	/// RAII release of the texture
	~Texture();
	void update(const Uint8* pixels);
	void update(const Image& image);
	void setSmooth(bool smooth);
	bool create(unsigned int width, unsigned int height);
	unsigned int getValidSize(unsigned int size);
	/// Copy the texture buffer to an image
	Image copyToImage();

	void loadFromImage(Image &image);

	/// Sets the desired transparency on all pixels with the selected color
	void createMaskFromColor(const Color &color, Uint8 alpha = 0);

	bool loadFromFile(const String &path);

	Vec2i getSize() const;

	void bind(CoordinateType coordinateType = Pixels) const;

	void update(const Uint8* pixels, unsigned int width, unsigned int height, unsigned int x, unsigned int y);

	static unsigned int getMaximumSize();

public:

	unsigned int m_texture;
	Vec2i m_size;
	Vec2i m_actualSize;
	bool m_pixelsFlipped;
	bool m_isSmooth;
};


	/**
		\ingroup Graphics
		\class RenderImage
		\brief Extends sf::RenderImage
	*/
	/*class RenderImage: public sf::RenderTexture{
	public:
		
	};*/

PARABOLA_NAMESPACE_END
#endif