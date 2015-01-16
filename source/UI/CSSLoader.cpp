#include <Nephilim/UI/CSSLoader.h>
#include <Nephilim/UI/Stylesheet.h>
#include <Nephilim/Logger.h>
#include <Nephilim/StringList.h>
#include <Nephilim/File.h>
#include <Nephilim/Foundation/TextStream.h>

#include <cctype>
#include <vector>

NEPHILIM_NS_BEGIN

/// Parse the file into runtime definitions
bool CSSLoader::load(const String& filename, StyleSheet& stylesheet)
{
	_storage = &stylesheet;

	File file(filename, IODevice::TextRead);
	if (file)
	{
		Log("File %s loaded", filename.c_str());
		TextStream stm(file);

		parse(stm);		
	}
	return true;
}

/// Parse the stream into the structures
void CSSLoader::parse(TextStream& stm)
{
	bool _onSelector = false;
	bool _onBlock = false;
	bool _onComment = false;

	String raw_block;
	String raw_selector;

	while (!stm.atEnd())
	{
		char next = stm.peek();

		if (std::isspace(next))
		{
			stm.readChar();
		}
		else
		{
			if (next == '{')
			{
				stm.readChar();
				_onBlock = true;
			}
			else if (next == '}')
			{
				stm.readChar();
				_onBlock = false;

				parse_raw_block(raw_block, raw_selector);
				raw_block.clear();
				raw_selector.clear();
			}
			else if (_onBlock)
			{
				//printf("%c", next);
				raw_block += stm.readChar();
			}
			else
			{
				raw_selector += stm.readChar();
			}
		}
	}
}

/// Parse a raw block directly
/// A raw block is the contents between { } (excluded), no comments
void CSSLoader::parse_raw_block(const String& blk, const String& selector)
{
	//Log("Block from %s", selector.c_str());
	//Log("Block is %s", blk.c_str());

	struct DefinitionPair
	{
		String attribute;
		String value;
	};

	// definitions in this block
	std::vector<DefinitionPair> definitions;

	String def_buff;
	Log("Selector %s", selector.c_str());

	StyleSheet::StyleArray stylesArray;

	for (std::size_t i = 0; i < blk.size(); ++i)
	{
		// in a split
		if (blk[i] == ';')
		{
			DefinitionPair pair;
			StringList pairElements = def_buff.split(':');
			pair.attribute = pairElements[0];
			pair.value = pairElements[1];
			def_buff.clear();

			stylesArray.entries.push_back(std::make_pair(pair.attribute, pair.value));

			Log("Definition: %s: %s", pair.attribute.c_str(), pair.value.c_str());
		}
		else
		{
			def_buff += blk[i];
		}
	}

	_storage->selectorList.push_back(selector);
	_storage->stylesList.push_back(stylesArray);
}

NEPHILIM_NS_END
