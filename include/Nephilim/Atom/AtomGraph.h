#ifndef NephilimAtomGraph_h__
#define NephilimAtomGraph_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

/**
	\class AtomGraph
	\brief Holds the runtime data of one atom visual script

	The ATOM language supports written and visual coding.
	The visual scripts are graphs of connected nodes stored in a file,
	while regular scripts are source files on actual text.

	On runtime, the written scripts are just a string and
	the visual ones are an AtomGraph object.
*/
class NEPHILIM_API AtomGraph
{
public:

	class AtomNode
	{

	};

	class AtomConnection
	{

	};

	std::vector<AtomNode> nodes;
	std::vector<AtomConnection> connections;
};

NEPHILIM_NS_END
#endif // NephilimAtomGraph_h__
