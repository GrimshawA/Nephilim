#include <Nephilim/Graphics/Text.h>
#include <Nephilim/Graphics/GraphicsDevice.h>
#include <Nephilim/Graphics/RectangleShape.h>
#include <Nephilim/Graphics/GL/GLHelpers.h>

#include <Nephilim/Foundation/Logging.h>
#include <Nephilim/Foundation/Image.h>

#include <cassert>

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

Text::Text()
: m_string()
, m_font(&Font::getDefaultFont()),
m_characterSize(30),
m_style(Regular),
m_color(255,255,255),
m_vertices(Render::Primitive::Triangles, 0),
m_bounds(0,0,0,0)
{

}

/// Creates a text with default font and content text positioned at (x,y) as top-left coordinate
Text::Text(String text, float x, float y) : m_string(text),
											m_font(&Font::getDefaultFont()),
											m_characterSize(30),
											m_style(Regular),
											m_color(255,255,255),
											m_vertices(Render::Primitive::Triangles, 0),
											m_bounds(0,0,0,0)
{
		updateGeometry();
};

void Text::onDraw(GraphicsDevice* renderer)
{
	if(!m_font || m_vertices.m_vertices.empty()) return;

	renderer->setTexture(m_font->getTexture(m_characterSize));
	renderer->setBlendingEnabled(true);
	renderer->setBlendMode(Render::Blend::Alpha);
	if (useOwnTransform)
		renderer->setModelMatrix(mat4(getTransform().getMatrix()));
	renderer->draw(m_vertices);
	renderer->setModelMatrix(mat4());
};

////////////////////////////////////////////////////////////
void Text::setString(const String& string)
{
    m_string = string;
    updateGeometry();
}


////////////////////////////////////////////////////////////
void Text::setFont(const Font& font)
{
    if (m_font != &font)
    {
        m_font = &font;
        updateGeometry();
    }
}


////////////////////////////////////////////////////////////
void Text::setCharacterSize(unsigned int size)
{
    if (m_characterSize != size)
    {
        m_characterSize = size;
        updateGeometry();
    }
}


////////////////////////////////////////////////////////////
void Text::setStyle(Uint32 style)
{
    if (m_style != style)
    {
        m_style = style;
        updateGeometry();
    }
}


////////////////////////////////////////////////////////////
void Text::setColor(const Color& color)
{
   // if (color != m_color)
  //  {
        m_color = color;
        for (unsigned int i = 0; i < m_vertices.m_vertices.size(); ++i)
            m_vertices[i].color = m_color;
    //}
}


////////////////////////////////////////////////////////////
const UString& Text::getString() const
{
    return m_string;
}

FloatRect Text::getCharacterRect(int index)
{
	if(m_vertices.m_vertices.empty())return FloatRect();

	if(index < 0 || index > m_vertices.m_vertices.size() / 6 - 1) return FloatRect(0,0,0,0);
	else
	{
		return FloatRect(m_vertices[index*6].position.x, m_vertices[index*6].position.y, m_vertices[index*6+5].position.x - m_vertices[index*6].position.x, m_vertices[index*6+5].position.y - m_vertices[index*6].position.y);
	}
};

Vec2f Text::getCharacterPosition(int index)
{
	if(index < 0) return Vec2f(0,0);
	if(index > m_string.size()-1){
		Vec2f position(0,0);
		position.x += getLocalBounds().width;
		position.y += getLocalBounds().height;
		return position;
	}
	if(m_string.empty()) return Vec2f(0,0);
	else
	{
		Vec2f position(0,0);
		for(int i = 0; i < index; i++)
		{
			position.x += m_font->getGlyph(m_string[i], getCharacterSize(), false).advance;
		}
		return position;
	}
};


////////////////////////////////////////////////////////////
const Font& Text::getFont() const
{
   // assert(m_font != NULL); // can never be NULL, always &Font::getDefaultFont() by default
    return *m_font;
}


////////////////////////////////////////////////////////////
unsigned int Text::getCharacterSize() const
{
    return m_characterSize;
}


////////////////////////////////////////////////////////////
Uint32 Text::getStyle() const
{
    return m_style;
}


////////////////////////////////////////////////////////////
const Color& Text::getColor() const
{
    return m_color;
}


////////////////////////////////////////////////////////////
Vec2f Text::findCharacterPos(std::size_t index) const
{
    /*assert(m_font != NULL);

    // Adjust the index if it's out of range
    if (index > m_string.getSize())
        index = m_string.getSize();

    // Precompute the variables needed by the algorithm
    bool  bold   = (m_style & Bold) != 0;
    float hspace = static_cast<float>(m_font->getGlyph(L' ', m_characterSize, bold).advance);
    float vspace = static_cast<float>(m_font->getLineSpacing(m_characterSize));

    // Compute the position
    Vector2f position;
    Uint32 prevChar = 0;
    for (std::size_t i = 0; i < index; ++i)
    {
        Uint32 curChar = m_string[i];

        // Apply the kerning offset
        position.x += static_cast<float>(m_font->getKerning(prevChar, curChar, m_characterSize));
        prevChar = curChar;

        // Handle special characters
        switch (curChar)
        {
            case L' ' :  position.x += hspace;                 continue;
            case L'\t' : position.x += hspace * 4;             continue;
            case L'\n' : position.y += vspace; position.x = 0; continue;
            case L'\v' : position.y += vspace * 4;             continue;
        }

        // For regular characters, add the advance offset of the glyph
        position.x += static_cast<float>(m_font->getGlyph(curChar, m_characterSize, bold).advance);
    }

    // Transform the position to global coordinates
    position = getTransform().transformPoint(position);

    return position;*/

	return Vec2f();
}


////////////////////////////////////////////////////////////
FloatRect Text::getLocalBounds() const
{
    return m_bounds;
}


////////////////////////////////////////////////////////////
FloatRect Text::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}

void Text::updateGeometry()
{
    assert(m_font != NULL);

    // Clear the previous geometry
    m_vertices.clear();

    if (m_string.empty())
        return;

    // Compute values related to the text style
    bool  bold               = (m_style & Bold) != 0;
    bool  underlined         = (m_style & Underlined) != 0;
    float italic             = (m_style & Italic) ? 0.208f : 0.f; // 12 degrees
    float underlineOffset    = m_characterSize * 0.1f;
    float underlineThickness = m_characterSize * (bold ? 0.1f : 0.07f);

    // Precompute the variables needed by the algorithm
    float hspace = static_cast<float>(m_font->getGlyph(L' ', m_characterSize, bold).advance);
    float vspace = static_cast<float>(m_font->getLineSpacing(m_characterSize));
    float x      = 0.f;
    float y      = static_cast<float>(m_characterSize);

    // Create one quad for each character
    Uint32 prevChar = 0;
    for (std::size_t i = 0; i < m_string.getSize(); ++i)
    {
        Uint32 curChar = m_string[i];

        // Apply the kerning offset
        x += static_cast<float>(m_font->getKerning(prevChar, curChar, m_characterSize));
        prevChar = curChar;

        // If we're using the underlined style and there's a new line, draw a line
        if (underlined && (curChar == L'\n'))
        {
            float top = y + underlineOffset;
            float bottom = top + underlineThickness;

            m_vertices.append(VertexArray2D::Vertex(Vec2f(0, top),    m_color, Vec2f(1, 1)));
            m_vertices.append(VertexArray2D::Vertex(Vec2f(x, top),    m_color, Vec2f(1, 1)));
            m_vertices.append(VertexArray2D::Vertex(Vec2f(x, bottom), m_color, Vec2f(1, 1)));
            m_vertices.append(VertexArray2D::Vertex(Vec2f(0, bottom), m_color, Vec2f(1, 1)));

			cout<<"No."<<endl;
        }

        // Handle special characters
        switch (curChar)
        {
            case L' ' :  x += hspace;        continue;
            case L'\t' : x += hspace * 4;    continue;
            case L'\n' : y += vspace; x = 0; continue;
            case L'\v' : y += vspace * 4;    continue;
        }

        // Extract the current glyph's description
        const Glyph& glyph = m_font->getGlyph(curChar, m_characterSize, bold);

        int left   = glyph.bounds.left;
        int top    = glyph.bounds.top;
        int right  = glyph.bounds.left + glyph.bounds.width;
        int bottom = glyph.bounds.top  + glyph.bounds.height;

        float u1 = static_cast<float>(glyph.textureRect.left);
        float v1 = static_cast<float>(glyph.textureRect.top);
        float u2 = static_cast<float>(glyph.textureRect.left + glyph.textureRect.width);
        float v2 = static_cast<float>(glyph.textureRect.top  + glyph.textureRect.height);

		Vec2i fontTextureSize = m_font->getTexture(m_characterSize).getSize();

		u1 /= fontTextureSize.x;
		u2 /= fontTextureSize.x;
		v1 /= fontTextureSize.y;
		v2 /= fontTextureSize.y;

     	m_vertices.append(VertexArray2D::Vertex(Vec2f(x + right - italic * bottom, y + bottom), m_color, Vec2f(u2, v2)));
		m_vertices.append(VertexArray2D::Vertex(Vec2f(x + left  - italic * top,    y + top),    m_color, Vec2f(u1, v1)));
		m_vertices.append(VertexArray2D::Vertex(Vec2f(x + left  - italic * bottom, y + bottom), m_color, Vec2f(u1, v2)));

		m_vertices.append(VertexArray2D::Vertex(Vec2f(x + right - italic * bottom, y + bottom), m_color, Vec2f(u2, v2)));
		m_vertices.append(VertexArray2D::Vertex(Vec2f(x + right - italic * top,    y + top),    m_color, Vec2f(u2, v1)));
		m_vertices.append(VertexArray2D::Vertex(Vec2f(x + left  - italic * top,    y + top),    m_color, Vec2f(u1, v1)));

	//	cout<< "U ("<<u1<<" "<<u2<<")" << endl;


        // Advance to the next character
        x += glyph.advance;
    }

    // If we're using the underlined style, add the last line
    if (underlined)
    {
        float top = y + underlineOffset;
        float bottom = top + underlineThickness;

        m_vertices.append(VertexArray2D::Vertex(Vec2f(0, top),    m_color, Vec2f(1, 1)));
        m_vertices.append(VertexArray2D::Vertex(Vec2f(x, top),    m_color, Vec2f(1, 1)));
        m_vertices.append(VertexArray2D::Vertex(Vec2f(x, bottom), m_color, Vec2f(1, 1)));
        m_vertices.append(VertexArray2D::Vertex(Vec2f(0, bottom), m_color, Vec2f(1, 1)));

		cout<<"No."<<endl;
    }

    // Recompute the bounding rectangle
    m_bounds = m_vertices.getBounds();
}

NEPHILIM_NS_END