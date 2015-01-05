#ifndef NephilimUILoaderXMLFormat_h__
#define NephilimUILoaderXMLFormat_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>
#include <Nephilim/UI/UILoader.h>

NEPHILIM_NS_BEGIN

class UIView;

/**
	\class UILoaderXML
	\brief Loads and accesses the XML file with the UI
*/
class NEPHILIM_API UILoaderXML : public UILoader
{
public:
	/// Load the xml file into the node
	bool loadFromFile(const String& filename, UIView* root_view);
};

NEPHILIM_NS_END
#endif // NephilimUILoaderXMLFormat_h__
