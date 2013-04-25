#ifndef Image_h__
#define Image_h__

#include "Platform.h"
#include "Strings.h"
#include "Color.h"
#include "Vectors.h"

#include <vector>

NEPHILIM_NS_BEGIN

class File;
/**
	\ingroup Graphics
	\class Image
	\brief Used to load, save and manipulate image buffers

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




	bool loadFromFile(const String &path);

	bool loadFromStream(File* stream);
	void setPixel(unsigned int x, unsigned int y, const Color& color);
	Vec2i getSize() const;

	/// Sets the desired transparency on all pixels with the selected color
	void createMaskFromColor(const Color &color, Uint8 alpha = 0);

	void create(unsigned int width, unsigned int height, const Color& color);

	void create(unsigned int width, unsigned int height,const Uint8* pixels);

	const Uint8* getPixelsPtr() const;

	std::vector<Uint8> m_pixels;
	Vec2i m_size;
};

NEPHILIM_NS_END
#endif // Image_h__
