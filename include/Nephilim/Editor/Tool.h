#ifndef NephilimEditorTool_h__
#define NephilimEditorTool_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

/**
	\class Tool
	\brief [Editor] Base class for all tools in all editors

	This class aims to be generic enough to act the base
	class for every tool in every editor, native or later
	scripted by users. 

	It is mainly just a thin interface into making the engine/editor connect well with the individual tools.
*/
class NEPHILIM_API Tool
{
public:

};

NEPHILIM_NS_END
#endif // NephilimEditorTool_h__
