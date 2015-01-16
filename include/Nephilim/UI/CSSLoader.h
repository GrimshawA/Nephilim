#ifndef NephilimUICSSLoader_h__
#define NephilimUICSSLoader_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>

NEPHILIM_NS_BEGIN

class TextStream;
class StyleSheet;

/**
	\class CSSLoader
	\brief Parse CSS code into runtime structures
*/
class NEPHILIM_API CSSLoader
{
public:

	StyleSheet* _storage = nullptr;

	/// Parse the file into runtime definitions
	bool load(const String& filename, StyleSheet& stylesheet);

	/// Parse the stream into the structures
	void parse(TextStream& stm);

	/// Parse a raw block directly
	/// A raw block is the contents between { } (excluded), no comments
	void parse_raw_block(const String& blk, const String& selector);

	class CSSBlock
	{
	public:

	};

};

NEPHILIM_NS_END
#endif // NephilimUICSSLoader_h__
