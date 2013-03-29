#include "Nephilim/Textures.h"
#include "Nephilim/Logger.h"
#include "Nephilim/FileInterface.h"

#include <string.h>

#if defined PARABOLA_ANDROID || defined PARABOLA_IPHONE

namespace privNS{
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"
};

#ifdef PARABOLA_ANDROID
#include <gles/gl.h>
#include <gles/glext.h>
#include <gles/glplatform.h>
#include <GLES2/gl2.h>
#endif

#ifdef PARABOLA_IPHONE
#include <OpenGLES/ES1/gl.h>
#include <GLUES/glu.h>
#endif





namespace
{
	// Convert a string to lower case
	std::string toLower(std::string str)
	{
		for (std::string::iterator i = str.begin(); i != str.end(); ++i)
			*i = static_cast<char>(std::tolower(*i));
		return str;
	}

	// stb_image callbacks that operate on a sf::InputStream
	int read(void* user, char* data, int size)
	{
		pE::ScopedFile* stream = static_cast<pE::ScopedFile*>(user);
		return static_cast<int>(stream->read(data, size));
	}
	void skip(void* user, unsigned int size)
	{
		pE::ScopedFile* stream = static_cast<pE::ScopedFile*>(user);
		stream->seek(stream->tell() + size);
	}
	int eof(void* user)
	{
		pE::ScopedFile* stream = static_cast<pE::ScopedFile*>(user);
		return stream->tell() >= stream->getSize();
	}
}

#endif

#ifdef PARABOLA_ANDROID

#include <GLES/gl.h>
#include <GLUES/glu.h>
#endif

#include <iostream>
#include <map>

#include <Nephilim/CGL.h>


PARABOLA_NAMESPACE_BEGIN

std::map<Texture*, Image> m_aliveTextures;

void reloadTextures(){
	for(std::map<Texture*, Image>::iterator it = m_aliveTextures.begin(); it != m_aliveTextures.end(); it++){
		(*it).first->loadFromImage((*it).second);
	}
};

////////////////////////////////////////////////////////////
void Image::create(unsigned int width, unsigned int height, const Color& color)
{
#ifdef PARABOLA_NOSFML
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

#else
	myImage.create(width, height, sf::Color(color.r, color.g, color.b, color.a));
#endif
}

////////////////////////////////////////////////////////////
void Image::setPixel(unsigned int x, unsigned int y, const Color& color)
{
#ifdef PARABOLA_NOSFML
	Uint8* pixel = &m_pixels[(x + y * m_size.x) * 4];
	*pixel++ = color.r;
	*pixel++ = color.g;
	*pixel++ = color.b;
	*pixel++ = color.a;
#else
	myImage.setPixel(x,y,sf::Color(color.r, color.g, color.b, color.a));
#endif
}


bool Image::loadFromFile(const String &path){
#ifdef PARABOLA_NOSFML

	//in android load through a stream
#ifdef PARABOLA_ANDROID
	ScopedFile* fp = new ScopedFile();
	if(FileInterface::getAssetFile(fp, path, true)){
		loadFromStream(fp);
		delete fp;
		return true;
	}
	delete fp;
#endif




	// Clear the array (just in case)
	m_pixels.clear();

	// Load the image and get a pointer to the pixels in memory
	int width, height, channels;
	unsigned char* ptr = privNS::stbi_load(String(FileInterface::m_root + path).c_str(), &width, &height, &channels,privNS::STBI_rgb_alpha);

	if (ptr && width && height)
	{
		// Assign the image properties
		m_size.x = width;
		m_size.y = height;

		// Copy the loaded pixels to the pixel buffer
		m_pixels.resize(width * height * 4);
		memcpy(&m_pixels[0], ptr, m_pixels.size());

		// Free the loaded pixels (they are now in our own pixel buffer)
		privNS::stbi_image_free(ptr);
		// Error, failed to load the image
		String errorResult = "Loaded \"" + path + "\". Reason : " + privNS::stbi_failure_reason();
		TESTLOG(errorResult.c_str())
		return true;
	}
	else
	{
		// Error, failed to load the image
		std::cout << "Failed to load image \"" << path << "\". Reason : " << privNS::stbi_failure_reason() << std::endl;
		String errorResult = "Failed to load image. \"" + path + "\". Reason : " + privNS::stbi_failure_reason();
		TESTLOG(errorResult.c_str())
		return false;
	}

#elif defined PARABOLA_DESKTOP
	FileInterface::onFileRequest.emit(path);
	return myImage.loadFromFile(FileInterface::m_root + path);
#endif

}

bool Image::loadFromStream(ScopedFile* stream){
#ifdef PARABOLA_NOSFML

	TESTLOG("Now loading a texture...")
	// Clear the array (just in case)
	m_pixels.clear();

	// Setup the stb_image callbacks
	privNS::stbi_io_callbacks callbacks;
	callbacks.read = &read;
	callbacks.skip = &skip;
	callbacks.eof  = &eof;

	// Load the image and get a pointer to the pixels in memory
	int width, height, channels;
	TESTLOG("NOTE DONE")

	unsigned char* ptr = privNS::stbi_load_from_callbacks(&callbacks, stream, &width, &height, &channels, privNS::STBI_rgb_alpha);

	TESTLOG("ITS DONE")

	if (ptr && width && height)
	{
		// Assign the image properties
		m_size.x = width;
		m_size.y = height;

		// Copy the loaded pixels to the pixel buffer
		m_pixels.resize(width * height * 4);
		memcpy(&m_pixels[0], ptr, m_pixels.size());

		// Free the loaded pixels (they are now in our own pixel buffer)
		privNS::stbi_image_free(ptr);

		return true;
	}
	else
	{
		// Error, failed to load the image
		TESTLOG("Failed to load image from stream. Reason : "/* + privNS::stbi_failure_reason())).c_str()*/);

		return false;
	}
#endif
	return true;
};


void Image::create(unsigned int width, unsigned int height,const Uint8* pixels){
#ifdef PARABOLA_NOSFML
	m_pixels.resize(width*height*4);
	memcpy(&m_pixels[0], pixels, m_pixels.size());
	m_size.x = width;
	m_size.y = height;
#elif defined PARABOLA_DESKTOP
	myImage.create(width, height, pixels);
#endif
}


Vec2i Image::getSize() const{
#ifdef PARABOLA_NOSFML
	return m_size;
#elif defined PARABOLA_DESKTOP
	return Vec2i(myImage.getSize().x, myImage.getSize().y);
#endif
};

const Uint8* Image::getPixelsPtr() const{
#ifdef PARABOLA_NOSFML
	return &m_pixels[0];
#elif defined PARABOLA_DESKTOP
	return myImage.getPixelsPtr();
#endif
};

/// Sets the desired transparency on all pixels with the selected color
void Image::createMaskFromColor(const Color &color, Uint8 alpha){
#ifdef PARABOLA_NOSFML
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
#else
	TESTLOG("attempting to change transparency\n")
	TESTLOG(String::number(color.g).c_str())
	myImage.createMaskFromColor(sf::Color(color.r,color.g,color.b), alpha);

#endif
};

/// Create an uninitialised texture
Texture::Texture() : m_size(0,0), m_actualSize(0,0), m_texture(0), m_pixelsFlipped(false),m_isSmooth(false){



};

/// RAII release of the texture
Texture::~Texture(){
	//delete the texture if exists
	if(m_texture){
		//glDeleteTextures(1, &m_texture);
		//PRINTLOG("ParabolaEngine", "Released texture with id: %d\n", m_texture);
		//m_aliveTextures.erase(m_aliveTextures.find(this));
	}
};




////////////////////////////////////////////////////////////
bool Texture::create(unsigned int width, unsigned int height)
{
	// Check if texture parameters are valid before creating it
	if ((width == 0) || (height == 0))
	{
		//err() << "Failed to create texture, invalid size (" << width << "x" << height << ")" << std::endl;
		return false;
	}

	// Compute the internal texture dimensions depending on NPOT textures support
	Vec2i actualSize(getValidSize(width), getValidSize(height));

	// Check the maximum texture size
	unsigned int maxSize = getMaximumSize();
	if ((actualSize.x > maxSize) || (actualSize.y > maxSize))
	{
		/*err() << "Failed to create texture, its internal size is too high "
			<< "(" << actualSize.x << "x" << actualSize.y << ", "
			<< "maximum is " << maxSize << "x" << maxSize << ")"
			<< std::endl;*/
		return false;
	}

	// All the validity checks passed, we can store the new texture settings
	m_size.x        = width;
	m_size.y        = height;
	m_actualSize    = actualSize;
	m_pixelsFlipped = false;

	//ensureGlContext();

	// Create the OpenGL texture if it doesn't exist yet
	if (!m_texture)
	{
		GLuint texture;
		glGenTextures(1, &texture);
		m_texture = static_cast<unsigned int>(texture);
		//PRINTLOG("ParabolaEngine", "Allocated texture with id: %d\n", m_texture);

	}

	// Make sure that the current texture binding will be preserved
	//priv::TextureSaver save;

	// Initialize the texture
	glBindTexture(GL_TEXTURE_2D, m_texture);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_actualSize.x, m_actualSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_actualSize.x, m_actualSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_isRepeated ? GL_REPEAT : GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_isRepeated ? GL_REPEAT : GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_isSmooth ? GL_LINEAR : GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_isSmooth ? GL_LINEAR : GL_NEAREST);
	//m_cacheId = getUniqueId();

	return true;
}

////////////////////////////////////////////////////////////
void Texture::update(const Image& image)
{
	// Update the whole texture
	update(image.getPixelsPtr(), image.getSize().x, image.getSize().y, 0, 0);
}

////////////////////////////////////////////////////////////
void Texture::update(const Uint8* pixels)
{
	// Update the whole texture
	update(pixels, m_size.x, m_size.y, 0, 0);
}


////////////////////////////////////////////////////////////
unsigned int Texture::getValidSize(unsigned int size)
{
//	ensureGlContext();

	// Make sure that GLEW is initialized
	//priv::ensureGlewInit();

	/*if (GLEW_ARB_texture_non_power_of_two)
	{
		// If hardware supports NPOT textures, then just return the unmodified size
		return size;
	}
	else
	{
		// If hardware doesn't support NPOT textures, we calculate the nearest power of two
		unsigned int powerOfTwo = 1;
		while (powerOfTwo < size)
			powerOfTwo *= 2;

		return powerOfTwo;
	}*/

	return size;
}

void Texture::loadFromImage(Image &image){
	m_size = image.getSize();
	m_actualSize = m_size;
	glGenTextures(1, &m_texture);
	//PRINTLOG("ParabolaEngine", "Allocated texture with id: %d\n", m_texture);

	glBindTexture(GL_TEXTURE_2D, m_texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x, image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE,  image.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	m_aliveTextures[this] = image;
}

bool Texture::loadFromFile(const String &path){
	TESTLOG(path.c_str())
	bool result = false;
	Image image;
#ifdef PARABOLA_ANDROID
	//in android load through a stream
	/*ScopedFile* fp = new ScopedFile();
	if(FileInterface::getAssetFile(fp, path, true)){

		image.loadFromStream(fp);
		//image.loadFromFile(path);
	}
	delete fp;*/
	TESTLOG("GOING TO LOAD IMAGE")
	image.loadFromFile(path);
	TESTLOG("GOING TO FINISH LOAD IMAGE")

#elif defined PARABOLA_DESKTOP || defined PARABOLA_IPHONE
	result = image.loadFromFile(path);
#endif
	// STUPID DEBUG THING
	//image.createMaskFromColor(Color(0,128,0, 255), 0);

		loadFromImage(image);
	return result;
}

/// Copy the texture buffer to an image
Image Texture::copyToImage(){

	// Easy case: empty texture
	if (!m_texture)
		return Image();

	//ensureGlContext();

	// Make sure that the current texture binding will be preserved
	//priv::TextureSaver save;

	// Create an array of pixels
	Image image;
	std::vector<Uint8> pixels(m_size.x * m_size.y * 4);

	if ((m_size == m_actualSize) && !m_pixelsFlipped)
	{
		// Texture is not padded nor flipped, we can use a direct copy
#ifdef PARABOLA_DESKTOP
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);
#else
		/*GLuint fboTexture;
		glGenFramebuffers(1, &fboTexture);
		glBindFramebuffer(GL_FRAMEBUFFER, fboTexture);
		// attach renderbuffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);
		glReadPixels(0,0,getSize().x, getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);
		// unbind frame buffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);*/
#endif
	}
	else
	{
		// Texture is either padded or flipped, we have to use a slower algorithm

		// All the pixels will first be copied to a temporary array
		std::vector<Uint8> allPixels(m_actualSize.x * m_actualSize.y * 4);
		//glBindTexture(GL_TEXTURE_2D, m_texture);
		//glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, &allPixels[0]);

		// Then we copy the useful pixels from the temporary array to the final one
		const Uint8* src = &allPixels[0];
		Uint8* dst = &pixels[0];
		int srcPitch = m_actualSize.x * 4;
		int dstPitch = m_size.x * 4;

		// Handle the case where source pixels are flipped vertically
		if (m_pixelsFlipped)
		{
			src += srcPitch * (m_size.y - 1);
			srcPitch = -srcPitch;
		}

		for (unsigned int i = 0; i < m_size.y; ++i)
		{
			memcpy(dst, src, dstPitch);
			src += srcPitch;
			dst += dstPitch;
		}
	}

	// Create the image

	image.create(m_size.x, m_size.y, &pixels[0]);

	return image;


};


Vec2i Texture::getSize() const{
	return m_size;
}


////////////////////////////////////////////////////////////
void Texture::setSmooth(bool smooth)
{
	if (smooth != m_isSmooth)
	{
		m_isSmooth = smooth;

		if (m_texture)
		{
			//ensureGlContext();

			// Make sure that the current texture binding will be preserved
			//priv::TextureSaver save;

			glBindTexture(GL_TEXTURE_2D, m_texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_isSmooth ? GL_LINEAR : GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_isSmooth ? GL_LINEAR : GL_NEAREST);
		}
	}
}

/// Sets the desired transparency on all pixels with the selected color
void Texture::createMaskFromColor(const Color &color, Uint8 alpha){
	Image img = this->copyToImage();
	img.createMaskFromColor(color, alpha);
	loadFromImage(img);
};

////////////////////////////////////////////////////////////
void Texture::update(const Uint8* pixels, unsigned int width, unsigned int height, unsigned int x, unsigned int y)
{
	/*assert(x + width <= m_size.x);
	assert(y + height <= m_size.y);*/

	if (pixels && m_texture)
	{
		//ensureGlContext();

		// Make sure that the current texture binding will be preserved
		//priv::TextureSaver save;

		// Copy pixels from the given array to the texture
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		m_pixelsFlipped = false;
		//m_cacheId = getUniqueId();
	}
}

////////////////////////////////////////////////////////////
unsigned int Texture::getMaximumSize()
{
	//ensureGlContext();

	GLint size;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &size);

	return static_cast<unsigned int>(size);
}

void Texture::bind(CoordinateType coordinateType) const{
	glBindTexture(GL_TEXTURE_2D, m_texture);

	// Check if we need to define a special texture matrix
	if ((coordinateType == Pixels) || m_pixelsFlipped)
	{
		GLfloat matrix[16] = {1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f};

		// If non-normalized coordinates (= pixels) are requested, we need to
		// setup scale factors that convert the range [0 .. size] to [0 .. 1]
		if (coordinateType == Pixels)
		{
			matrix[0] = 1.f / m_actualSize.x;
			matrix[5] = 1.f / m_actualSize.y;
		}

		// If pixels are flipped we must invert the Y axis
		if (m_pixelsFlipped)
		{
			matrix[5] = -matrix[5];
			matrix[13] = static_cast<float>(m_size.y / m_actualSize.y);
		}

		// Load the matrix
		glMatrixMode(GL_TEXTURE);
		glLoadMatrixf(matrix);

		// Go back to model-view mode (sf::RenderTarget relies on it)
		glMatrixMode(GL_MODELVIEW);
	}
};

/************************************************************************/
/* Texture                                                              */
/************************************************************************/
/*void Texture::maskColor(const Color &color, unsigned char alpha){
	sf::Image img = this->copyToImage();
	img.createMaskFromColor(color, alpha);
	loadFromImage(img);
};

/// Get the size of the texture
Vec2f Texture::getSize(){
	return Vec2f(sf::Texture::getSize().x,sf::Texture::getSize().y);
};*/

PARABOLA_NAMESPACE_END
