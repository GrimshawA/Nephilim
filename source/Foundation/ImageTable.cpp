#include <Nephilim/Foundation/ImageTable.h>
#include <Nephilim/Foundation/File.h>
#include <Nephilim/Foundation/Logging.h>
#include <Nephilim/Foundation/StringList.h>

NEPHILIM_NS_BEGIN

namespace 
{
	// Remove white space from the beggining and end
	void trim(String& s)
	{
		while(!s.empty() && (s[0] == ' ' || s[0] == '\t'))
		{
			s.erase(s.begin());
		}

		while(!s.empty() && (s[s.size()-1] == ' ' || s[s.size()-1] == '\t'))
		{
			s.erase(s.begin() + s.size() - 1);
		}
	}
};

/// Clear the current table
void ImageTable::clear()
{
	table.clear();
}

/// Direct acessor to table members
ImageTable::ImageData& ImageTable::operator[](const String& alias)
{
	return table[alias];
}

/// Load a image table from a file
bool ImageTable::loadFromFile(const String& filename)
{
	File reader(filename, IODevice::TextRead);
	if(reader)
	{
		while(!reader.atEnd())
		{
			String line = reader.getLine();
			
			processRawLine(line);
		}
		return true;
	}
	else
	{
		return false;
	}
}

/// Processes a image entry from a raw line as if it was from a file
void ImageTable::processRawLine(const String& line)
{
	if(line.empty())
	{
		return;
	}

	if(line[0] == '#')
	{
		return;
	}

	StringList params = line.split('|');
	if(params.size() == 3)
	{
		String alias = params[0];
		String src   = params[1];
		String rect  = params[2];

		trim(alias);
		trim(src);
		trim(rect);

		FloatRect textureRect;

		StringList rectParams = rect.split(' ');
		if(rectParams.size() == 4)
		{
			textureRect.left = rectParams[0].toFloat();
			textureRect.top = rectParams[1].toFloat();
			textureRect.width = rectParams[2].toFloat();
			textureRect.height = rectParams[3].toFloat();
		}
		
		ImageData data;
		data.src = src;
		data.srcRect = textureRect;

		table[alias] = data;

		//Log("alias %s = %s src with %f, %f, %f, %f rect", alias.c_str(), src.c_str(), textureRect.left, textureRect.top, textureRect.width, textureRect.height);

		//Log("%s|", alias.c_str());
		//Log("%s|", src.c_str());
		//Log("%s|", rect.c_str());
	}
}

NEPHILIM_NS_END