#ifndef NephilimGraphicsFont_h__
#define NephilimGraphicsFont_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Graphics/Glyph.h>
#include <Nephilim/Graphics/GL/GLTexture.h>

#include <map>
#include <string>
#include <vector>

NEPHILIM_NS_BEGIN

class File;

/**
	\ingroup Graphics
	\class Font
	\brief Loads and stores information about a freetype font
*/
class NEPHILIM_API Font
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// This constructor defines an empty font
    ///
    ////////////////////////////////////////////////////////////
    Font();

    ////////////////////////////////////////////////////////////
    /// \brief Copy constructor
    ///
    /// \param copy Instance to copy
    ///
    ////////////////////////////////////////////////////////////
    Font(const Font& copy);

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    /// Cleans up all the internal resources used by the font
    ///
    ////////////////////////////////////////////////////////////
    ~Font();

	/// Is this font already loaded and valid?
	bool isLoaded();

    ////////////////////////////////////////////////////////////
    /// \brief Load the font from a file
    ///
    /// The supported font formats are: TrueType, Type 1, CFF,
    /// OpenType, SFNT, X11 PCF, Windows FNT, BDF, PFR and Type 42.
    /// Note that this function know nothing about the standard
    /// fonts installed on the user's system, thus you can't
    /// load them directly.
    ///
    /// \param filename Path of the font file to load
    ///
    /// \return True if loading succeeded, false if it failed
    ///
    /// \see loadFromMemory, loadFromStream
    ///
    ////////////////////////////////////////////////////////////
    bool loadFromFile(const std::string& filename);

    ////////////////////////////////////////////////////////////
    /// \brief Load the font from a file in memory
    ///
    /// The supported font formats are: TrueType, Type 1, CFF,
    /// OpenType, SFNT, X11 PCF, Windows FNT, BDF, PFR and Type 42.
    /// Warning: SFML cannot preload all the font data in this
    /// function, so the buffer pointed by \a data has to remain
    /// valid as long as the font is used.
    ///
    /// \param data        Pointer to the file data in memory
    /// \param sizeInBytes Size of the data to load, in bytes
    ///
    /// \return True if loading succeeded, false if it failed
    ///
    /// \see loadFromFile, loadFromStream
    ///
    ////////////////////////////////////////////////////////////
    bool loadFromMemory(const void* data, std::size_t sizeInBytes);

    ////////////////////////////////////////////////////////////
    /// \brief Load the font from a custom stream
    ///
    /// The supported font formats are: TrueType, Type 1, CFF,
    /// OpenType, SFNT, X11 PCF, Windows FNT, BDF, PFR and Type 42.
    /// Warning: SFML cannot preload all the font data in this
    /// function, so the contents of \a stream have to remain
    /// valid as long as the font is used.
    ///
    /// \param stream Source stream to read from
    ///
    /// \return True if loading succeeded, false if it failed
    ///
    /// \see loadFromFile, loadFromMemory
    ///
    ////////////////////////////////////////////////////////////
    bool loadFromStream(File& stream);

    ////////////////////////////////////////////////////////////
    /// \brief Retrieve a glyph of the font
    ///
    /// \param codePoint     Unicode code point of the character to get
    /// \param characterSize Reference character size
    /// \param bold          Retrieve the bold version or the regular one?
    ///
    /// \return The glyph corresponding to \a codePoint and \a characterSize
    ///
    ////////////////////////////////////////////////////////////
    const Glyph& getGlyph(Uint32 codePoint, unsigned int characterSize, bool bold) const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the kerning offset of two glyphs
    ///
    /// The kerning is an extra offset (negative) to apply between two
    /// glyphs when rendering them, to make the pair look more "natural".
    /// For example, the pair "AV" have a special kerning to make them
    /// closer than other characters. Most of the glyphs pairs have a
    /// kerning offset of zero, though.
    ///
    /// \param first         Unicode code point of the first character
    /// \param second        Unicode code point of the second character
    /// \param characterSize Reference character size
    ///
    /// \return Kerning value for \a first and \a second, in pixels
    ///
    ////////////////////////////////////////////////////////////
    int getKerning(Uint32 first, Uint32 second, unsigned int characterSize) const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the line spacing
    ///
    /// Line spacing is the vertical offset to apply between two
    /// consecutive lines of text.
    ///
    /// \param characterSize Reference character size
    ///
    /// \return Line spacing, in pixels
    ///
    ////////////////////////////////////////////////////////////
    int getLineSpacing(unsigned int characterSize) const;

    ////////////////////////////////////////////////////////////
    /// \brief Retrieve the texture containing the loaded glyphs of a certain size
    ///
    /// The contents of the returned texture changes as more glyphs
    /// are requested, thus it is not very relevant. It is mainly
    /// used internally by sf::Text.
    ///
    /// \param characterSize Reference character size
    ///
    /// \return Texture containing the glyphs of the requested size
    ///
    ////////////////////////////////////////////////////////////
    const Texture& getTexture(unsigned int characterSize) const;

    ////////////////////////////////////////////////////////////
    /// \brief Overload of assignment operator
    ///
    /// \param right Instance to assign
    ///
    /// \return Reference to self
    ///
    ////////////////////////////////////////////////////////////
    Font& operator =(const Font& right);

    ////////////////////////////////////////////////////////////
    /// \brief Return the default built-in font
    ///
    /// This font is provided for convenience, it is used by
    /// sf::Text instances by default. It is provided so that
    /// users don't have to provide and load a font file in order
    /// to display text on screen.
    /// The font used is Arial.
    ///
    /// \return Reference to the built-in default font
    ///
    ////////////////////////////////////////////////////////////
    static const Font& getDefaultFont();

private :

    ////////////////////////////////////////////////////////////
    /// \brief Structure defining a row of glyphs
    ///
    ////////////////////////////////////////////////////////////
    struct Row
    {
        Row(unsigned int rowTop, unsigned int rowHeight) : width(0), top(rowTop), height(rowHeight) {}

        unsigned int width;  ///< Current width of the row
        unsigned int top;    ///< Y position of the row into the texture
        unsigned int height; ///< Height of the row
    };

    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    typedef std::map<Uint32, Glyph> GlyphTable; ///< Table mapping a codepoint to its glyph

    ////////////////////////////////////////////////////////////
    /// \brief Structure defining a page of glyphs
    ///
    ////////////////////////////////////////////////////////////
    struct Page
    {
        Page();
		~Page();

        GlyphTable       glyphs;  ///< Table mapping code points to their corresponding glyph
        Texture      texture; ///< Texture containing the pixels of the glyphs
        unsigned int     nextRow; ///< Y position of the next new row in the texture
        std::vector<Row> rows;    ///< List containing the position of all the existing rows
    };

    ////////////////////////////////////////////////////////////
    /// \brief Free all the internal resources
    ///
    ////////////////////////////////////////////////////////////
    void cleanup();

    ////////////////////////////////////////////////////////////
    /// \brief Load a new glyph and store it in the cache
    ///
    /// \param codePoint     Unicode code point of the character to load
    /// \param characterSize Reference character size
    /// \param bold          Retrieve the bold version or the regular one?
    ///
    /// \return The glyph corresponding to \a codePoint and \a characterSize
    ///
    ////////////////////////////////////////////////////////////
    Glyph loadGlyph(Uint32 codePoint, unsigned int characterSize, bool bold) const;

    ////////////////////////////////////////////////////////////
    /// \brief Find a suitable rectangle within the texture for a glyph
    ///
    /// \param page   Page of glyphs to search in
    /// \param width  Width of the rectangle
    /// \param height Height of the rectangle
    ///
    /// \return Found rectangle within the texture
    ///
    ////////////////////////////////////////////////////////////
    IntRect findGlyphRect(Page& page, unsigned int width, unsigned int height) const;

    ////////////////////////////////////////////////////////////
    /// \brief Make sure that the given size is the current one
    ///
    /// \param characterSize Reference character size
    ///
    /// \return True on success, false if any error happened
    ///
    ////////////////////////////////////////////////////////////
    bool setCurrentSize(unsigned int characterSize) const;

    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    typedef std::map<unsigned int, Page*> PageTable; ///< Table mapping a character size to its page (texture)

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    void*                      m_library;     ///< Pointer to the internal library interface (it is typeless to avoid exposing implementation details)
    void*                      m_face;        ///< Pointer to the internal font face (it is typeless to avoid exposing implementation details)
    void*                      m_streamRec;   ///< Pointer to the stream rec instance (it is typeless to avoid exposing implementation details)
    int*                       m_refCount;    ///< Reference counter used by implicit sharing
    mutable PageTable          m_pages;       ///< Table containing the glyphs pages by character size
    mutable std::vector<Uint8> m_pixelBuffer; ///< Pixel buffer holding a glyph's pixels before being written to the texture
};

NEPHILIM_NS_END
#endif // NephilimGraphicsFont_h__