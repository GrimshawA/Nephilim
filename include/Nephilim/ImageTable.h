#ifndef NephilimImageTable_h__
#define NephilimImageTable_h__

#include <Nephilim/Platform.h>
#include "Strings.h"
#include "Rect.h"

#include <map>

NEPHILIM_NS_BEGIN

/**
	\class ImageTable
	\brief Map named images to source rectangles in textures
*/
class NEPHILIM_API ImageTable
{
public:

	/// Clear the current table
	void clear();

	/// Load a image table from a file
	bool loadFromFile(const String& filename);

	/// Processes a image entry from a raw line as if it was from a file
	void processRawLine(const String& line);

	class ImageData
	{
	public:
		String src;
		FloatRect srcRect;
	};

	/// Direct acessor to table members
	ImageData& operator[](const String& alias);

	std::map<String, ImageData> table;
};

NEPHILIM_NS_END
#endif // NephilimImageTable_h__
