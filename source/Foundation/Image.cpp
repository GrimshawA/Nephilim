#include <Nephilim/Foundation/Image.h>
#include <Nephilim/Foundation/File.h>
#include <Nephilim/Foundation/Logging.h>

#include <string.h>

// If SFML is used, use stb_image as header only because it was already defined
//#if defined NEPHILIM_SFML && defined SFML_STATIC
//#define STBI_HEADER_FILE_ONLY
//#endif

//#if (defined NEPHILIM_SFML && !defined SFML_STATIC) || !defined NEPHILIM_SFML
#define STB_IMAGE_WRITE_IMPLEMENTATION
//#endif

#include "stb_image/stb_image.h"
#include "stb_image/stb_image_write.h"

NEPHILIM_NS_BEGIN

namespace
{
	// stb_image callbacks that operate on a sf::InputStream
	int read(void* user, char* data, int size)
	{
		File* stream = static_cast<File*>(user);
		return static_cast<int>(stream->read(data, size));
	}
	void skip(void* user, unsigned int size)
	{
		File* stream = static_cast<File*>(user);
		stream->seek(stream->tell() + size);
	}
	int eof(void* user)
	{
		File* stream = static_cast<File*>(user);
		return stream->tell() >= stream->getSize();
	}
}
Image::Image()
: m_size(0,0)
{

}

bool Image::saveToFile(const String& path)
{
	return stbi_write_png(path.c_str(), m_size.x, m_size.y, 4, &m_pixels[0], 0) != 0;
}

void Image::create(unsigned int width, unsigned int height, const Color& color)
{
	// Assign the new size
	m_size.x = width;
	m_size.y = height;

	// Resize the pixel buffer
	m_pixels.resize(width * height * 4);

	// Fill it with the specified color
	Uint8* ptr = &m_pixels[0];
	Uint8* end = ptr + m_pixels.size();
	while (ptr < end)
	{
		*ptr++ = color.r;
		*ptr++ = color.g;
		*ptr++ = color.b;
		*ptr++ = color.a;
	}
}

void Image::setPixel(unsigned int x, unsigned int y, const Color& color)
{
	Uint8* pixel = &m_pixels[(x + y * m_size.x) * 4];
	*pixel++ = color.r;
	*pixel++ = color.g;
	*pixel++ = color.b;
	*pixel++ = color.a;
}

bool Image::loadFromFile(const String &path){

	File stream(path, IODevice::BinaryRead);

	if(!stream)
	{
	    Log("Image: Invalid path: %s", path.c_str());
	    return false;
	}

	// Setup the stb_image callbacks
	stbi_io_callbacks callbacks;
	callbacks.read = &read;
	callbacks.skip = &skip;
	callbacks.eof  = &eof;

	// Clear the array (just in case)
	m_pixels.clear();

	// Load the image and get a pointer to the pixels in memory
	int width, height, channels;
	//unsigned char* ptr = stbi_load(String(path).c_str(), &width, &height, &channels,STBI_rgb_alpha);
	unsigned char* ptr = stbi_load_from_callbacks(&callbacks, &stream, &width, &height, &channels, STBI_rgb_alpha);

	if (ptr && width && height)
	{
		// Assign the image properties
		m_size.x = width;
		m_size.y = height;

		// Copy the loaded pixels to the pixel buffer
		m_pixels.resize(width * height * 4);
		memcpy(&m_pixels[0], ptr, m_pixels.size());

		// Free the loaded pixels (they are now in our own pixel buffer)
		stbi_image_free(ptr);

		return true;
	}
	else
	{
		// Error, failed to load the image
		String errorResult = "Failed to load image. \"" + path + "\". Reason : " + stbi_failure_reason();
		Log("%s", errorResult.c_str());
		return false;
	}

	return true;
}

/// Get the color of an individual pixel
Color Image::getPixel(unsigned int x, unsigned int y)
{
	Uint8* pixel = &m_pixels[(x + y * m_size.x) * 4];
	Color color;
	color.r = *pixel++;
	color.g = *pixel++;
	color.b = *pixel++;
	color.a = *pixel++;
	return color;
}

/// Scales the image to a new size
Image Image::scale(int width, int height)
{
	Image image;
	image.create(width, height, Color::Black);

	for(int i = 0; i < width; ++i)
	{
		for(int j = 0; j < height; ++j)
		{
			vec2 norm(static_cast<float>(i) / width, static_cast<float>(j) / height);
			norm.x *= m_size.x;
			norm.y *= m_size.y;
			//Log("Norm: %f, %f", norm.x, norm.y);
			image.setPixel(i,j, getPixel(static_cast<unsigned int>(norm.x), static_cast<unsigned int>(norm.y)));
		}
	}
	return image;
}

bool Image::loadFromStream(File* stream){

	// Clear the array (just in case)
	m_pixels.clear();

	// Setup the stb_image callbacks
	stbi_io_callbacks callbacks;
	callbacks.read = &read;
	callbacks.skip = &skip;
	callbacks.eof  = &eof;

	// Load the image and get a pointer to the pixels in memory
	int width, height, channels;

	unsigned char* ptr = stbi_load_from_callbacks(&callbacks, stream, &width, &height, &channels, STBI_rgb_alpha);

	if (ptr && width && height)
	{
		// Assign the image properties
		m_size.x = width;
		m_size.y = height;

		// Copy the loaded pixels to the pixel buffer
		m_pixels.resize(width * height * 4);
		memcpy(&m_pixels[0], ptr, m_pixels.size());

		// Free the loaded pixels (they are now in our own pixel buffer)
		stbi_image_free(ptr);

		return true;
	}
	else
	{
		// Error, failed to load the image
		Log("Failed to load image from stream. Reason : %s", stbi_failure_reason());
		return false;
	}

	return true;
}

void Image::create(unsigned int width, unsigned int height,const Uint8* pixels){

	m_pixels.resize(width*height*4);
	memcpy(&m_pixels[0], pixels, m_pixels.size());
	m_size.x = width;
	m_size.y = height;
}

Vec2i Image::getSize() const
{
	return m_size;
}

const Uint8* Image::getPixelsPtr() const
{
	return &m_pixels[0];
}

void Image::createMaskFromColor(const Color &color, Uint8 alpha)
{
	// Make sure that the image is not empty
	if (!m_pixels.empty())
	{
		// Replace the alpha of the pixels that match the transparent color
		Uint8* ptr = &m_pixels[0];
		Uint8* end = ptr + m_pixels.size();
		while (ptr < end)
		{
			if ((ptr[0] == color.r) && (ptr[1] == color.g) && (ptr[2] == color.b) && (ptr[3] == color.a))
				ptr[3] = alpha;
			ptr += 4;
		}
	}
}

NEPHILIM_NS_END