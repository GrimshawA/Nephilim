#include <Nephilim/Texture.h>
#include <Nephilim/Image.h>
#include <Nephilim/Logger.h>
#include <Nephilim/CGL.h>

#include <string.h>

NEPHILIM_NS_BEGIN

Texture::Texture()
: m_size(0,0)
, m_actualSize(0,0)
, m_texture(0)
, m_pixelsFlipped(false)
, m_isSmooth(false)
, m_isRepeated(false)
{

}

Texture::Texture(const Texture& other)
: m_size(0,0)
, m_actualSize(0,0)
, m_texture(0)
, m_pixelsFlipped(false)
, m_isSmooth(false)
, m_isRepeated(false)
{
	if (other.m_texture)
	{
		Image img = other.copyToImage();
		loadFromImage(img);
	}
}

Texture::~Texture()
{
	// Ensure the texture is destroyed in the GPU when the texture dies
	unload();
}

void Texture::unload()
{
	if(m_texture > 0)
	{
		GLuint tt = m_texture;
		glDeleteTextures(1, &tt);
		m_texture = 0;
	}
}

unsigned int Texture::getIdentifier() const
{
	return m_texture;
}

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
		//Log("Just allocated texture at create() %d", texture);
	}

	// Make sure that the current texture binding will be preserved
	//priv::TextureSaver save;

	// Initialize the texture
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_actualSize.x, m_actualSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_isRepeated ? GL_REPEAT : GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_isRepeated ? GL_REPEAT : GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_isSmooth ? GL_LINEAR : GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_isSmooth ? GL_LINEAR : GL_NEAREST);
	
	return true;
}

void Texture::generateMipMaps()
{
#ifdef NEPHILIM_DESKTOP
	bind();
	glGenerateMipmapEXT(GL_TEXTURE_2D);
	Log("Generated Mipmaps");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
#endif
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

void Texture::loadFromImage(Image &image, bool generateMipMaps){
	if(image.getSize().x == 0 && image.getSize().y == 0)
	{
		// Invalid image.
		return;
	}

	m_size = image.getSize();
	m_actualSize = m_size;
	GLuint tt = 0;
	glGenTextures(1, &tt);
	m_texture = tt;

	glBindTexture(GL_TEXTURE_2D, m_texture);

	generateMipMaps = false;
	if(!generateMipMaps)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
/*#ifdef NEPHILIM_DESKTOP
		glGenerateMipmapEXT(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
#else*/
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//#endif

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_isRepeated ? GL_REPEAT : GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_isRepeated ? GL_REPEAT : GL_CLAMP_TO_EDGE);
	}
	else
	{

		Vec2i currentSize = image.getSize();
		Image scaledDown = image;
		int i = 0;
		bool done = false;
		while(!done)
		{
			glTexImage2D(GL_TEXTURE_2D, i, GL_RGBA, scaledDown.getSize().x, scaledDown.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, scaledDown.getPixelsPtr());
			if(scaledDown.getSize() == Vec2i(1,1))
			{
				// done
				done = true;
			}
			else
			{
				scaledDown = scaledDown.scale(scaledDown.getSize().x  / 2, scaledDown.getSize().y / 2);
				//scaledDown.saveToFile("wood" + String::number(i) + ".png");
				currentSize = scaledDown.getSize();
				i++;
			}
			Log("Uploaded mipmap level %d. Size(%d,%d)", i, scaledDown.getSize().x, scaledDown.getSize().y);			
		}
		Log("%d Mipmaps until reached %dx%d", i, currentSize.x, currentSize.y);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_isRepeated ? GL_REPEAT : GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_isRepeated ? GL_REPEAT : GL_CLAMP_TO_EDGE);
	}
}

void Texture::setRepeated(bool repeated)
{
	m_isRepeated = repeated;

	bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_isRepeated ? GL_REPEAT : GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_isRepeated ? GL_REPEAT : GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_isRepeated ? GL_REPEAT : GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_isRepeated ? GL_REPEAT : GL_CLAMP);
}


bool Texture::loadFromFile(const String &path){
	bool result = false;
	Image image;
	result = image.loadFromFile(path);
	loadFromImage(image);
	return result;
}

/// Copy the texture buffer to an image
Image Texture::copyToImage() const
{

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
		glBindTexture(GL_TEXTURE_2D, m_texture);
#ifndef NEPHILIM_ANDROID
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);
#else
		Log("Texture::copyToImage() is not allowed in Android.");
#endif
	}
	else
	{
		// Texture is either padded or flipped, we have to use a slower algorithm

		// All the pixels will first be copied to a temporary array
		std::vector<Uint8> allPixels(m_actualSize.x * m_actualSize.y * 4);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		
#ifndef NEPHILIM_ANDROID
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, &allPixels[0]);
#else
		Log("Texture::copyToImage() is not allowed in Android.");
#endif	

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

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_texture);
};

/// Get the id of the currently bound texture for the currently set texture unit
unsigned int Texture::getCurrentBoundTexture()
{
	GLint id;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &id);
	return id;
}

NEPHILIM_NS_END
