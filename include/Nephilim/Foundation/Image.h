#ifndef Image_h__
#define Image_h__

#include <Nephilim/Platform.h>
#include "Strings.h"
#include "Color.h"
#include <Nephilim/Math/Vectors.h>

#include <vector>

NEPHILIM_NS_BEGIN

class File;

/**
	\ingroup Graphics
	\class Image
	\brief Loads and saves images

	Supported formats:
		PNG
		PSD
		TGA
		JPG
		BMP

	(todo - add stb specs)
*/
class NEPHILIM_API Image
{
public:
	/// Creates an empty image with size (0,0)
	Image();

	/// Attempts to save the image buffer in a file
	bool saveToFile(const String& path);

	/// Attempts to load an image from a file
	bool loadFromFile(const String &path);

	/// Attempts to load an image from an open stream
	bool loadFromStream(File* stream);

	/// Set the color of an individual pixel
	void setPixel(unsigned int x, unsigned int y, const Color& color);

	/// Get the color of an individual pixel
	Color getPixel(unsigned int x, unsigned int y);

	/// Scales the image to a new size
	Image scale(int width, int height);

	/// Get the size of the image
	Vec2i getSize() const;

	/// Sets the desired transparency on all pixels with the selected color
	void createMaskFromColor(const Color &color, Uint8 alpha = 0);

	/// Creates or recreates the image with a selected fill color
	void create(unsigned int width, unsigned int height, const Color& color);

	/// Creates or recreates the image from a pixel array
	void create(unsigned int width, unsigned int height,const Uint8* pixels);

	/// Get the raw array of pixels
	const Uint8* getPixelsPtr() const;

private:
	std::vector<Uint8> m_pixels; ///< The dynamic array of pixels
	Vec2i m_size;				 ///< The size of the image
};

NEPHILIM_NS_END
#endif // Image_h__
