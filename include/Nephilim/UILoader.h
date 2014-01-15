#ifndef NephilimUILoader_h__
#define NephilimUILoader_h__

#include "Platform.h"
#include "Strings.h"
#include "pugixml/pugixml.hpp"

NEPHILIM_NS_BEGIN

class UIView;

/**
	\class UILoaderXML
	\brief Loads and accesses the XML file with the UI
*/
class NEPHILIM_API UILoaderXML
{
public:
	bool loadFromFile(const String& filename);

	pugi::xml_document document; ///< Contains all the UI file data (xml)
};

class NEPHILIM_API UILoader
{
public:

	void configure(UIView* view, const String& filename); // v1 test
};

NEPHILIM_NS_END
#endif // NephilimUILoader_h__
