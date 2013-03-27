#ifndef PARABOLA_TEXTRENDERING_H
#define PARABOLA_TEXTRENDERING_H

#include "Platform.h"
#include "Strings.h"
#include "Drawable.h"
#include "Transformable.h"
#include "Font.h"
#include "Color.h"
#include "VertexArray.h"
#include "Rect.h"
#include "Logger.h"

#include <utf8.h>

#include <cstdlib>
#include <iterator>
#include <SFML/System/Utf.hpp>

PARABOLA_NAMESPACE_BEGIN

class UString : public std::basic_string<Uint32>{
public:
	UString(){

	}

	UString(String ansiString){
		clear();
		reserve(ansiString.length() + 1);
		/*std::locale locale = std::locale();
		sf::Utf32::fromAnsi(ansiString.c_str(), ansiString.c_str() + ansiString.length(), std::back_inserter(*this), locale);*/
		
		String temp;
		utf8::replace_invalid(ansiString.begin(), ansiString.end(), back_inserter(temp));
		ansiString = temp;
		
		const char* twochars = ansiString.c_str();
		std::vector<int> utf32result;
		utf8::utf8to32(twochars, twochars + ansiString.length(), back_inserter(*this));
		for(unsigned int i = 0; i < utf32result.size(); i++){
			*this += utf32result[i];
		}
		
		/*for(unsigned int i = 0; i < ansiString.length(); i++){

			Uint32 res;

			// Get the facet of the locale which deals with character conversion
			//const std::ctype<wchar_t>& facet = std::use_facet< std::ctype<wchar_t> >(std::locale());
			
			
			// Use the facet to convert each character of the input string
			//res = static_cast<Uint32>(facet.widen(ansiString[i]));

			*this += res;
			//*this += ansiString[i];
			TESTLOG("CHAR SET STRING -..........")
		}*/

		//*this += L'H';
	} 

	size_t getSize(){
		return size();
	}
};

class Font;

/**
		\ingroup Graphics
		\class Text
		\brief Extends sf::Text

		Inherits all sf::Text functionality and extends it for some more utility functions

*/
class PARABOLA_API Text : public Drawable, public Transformable{
public:		
	/// Creates a Text object with the default font, but no text string yet
	Text();
	/// Creates a text with default font and content text positioned at (x,y) as top-left coordinate
	Text(String text, float x, float y);
		/// Creates a text with the desired font at the specified position
		Text(const Font &font, String text, float x, float y);

		void setFont(const Font& font);
		/// Draws the text
		void setCharacterSize(unsigned int size);
		virtual void onDraw(Renderer* renderer);
		void setString(const String& string);
		/// Align the text to be centered between x and y - Horizontal Coordinates
		void alignCenterH(float x, float y);
		/// Align the text to be centered between x and y - Vertical Coordinates
		void alignCenterV(float x, float y);
		void updateGeometry();
		void setStyle(Uint32 style);
		void setColor(const Color& color);
		const UString& getString() const;
		Uint32 getStyle() const;
		const Color& getColor() const;
		Vec2f findCharacterPos(std::size_t index) const;
		FloatRect getLocalBounds() const;
		FloatRect getGlobalBounds() const;

		Vec2f getCharacterPosition(int index);
		FloatRect getCharacterRect(int index);

		const Font& getFont() const;
		unsigned int getCharacterSize() const;


	////////////////////////////////////////////////////////////
    /// \brief Enumeration of the string drawing styles
    ///
    ////////////////////////////////////////////////////////////
    enum Style
    {
        Regular    = 0,      ///< Regular characters, no style
        Bold       = 1 << 0, ///< Bold characters
        Italic     = 1 << 1, ///< Italic characters
        Underlined = 1 << 2  ///< Underlined characters
    };
private:
	/// The string with the graphical text content
	UString m_string;
	/// The font to use to draw this text
	const Font* m_font;
	/// Size of the characters
	unsigned int m_characterSize;
	/// Style of text
	Uint32 m_style;
	/// Color of the text
	Color m_color;
	/// Text geometry
	VertexArray m_vertices;
	/// Bounds of the text
	FloatRect m_bounds;
};

PARABOLA_NAMESPACE_END
#endif