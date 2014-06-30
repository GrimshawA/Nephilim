#ifndef NephilimSceneFormat_h__
#define NephilimSceneFormat_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>

#include <list>

NEPHILIM_NS_BEGIN
namespace rzr
{

/**
	\class SceneFormat
	\brief This is the interchange scene format of Nephilim.

	Being the interchange format of the engine, this is basically
	a technical specification that describes a game world and many of its associated parameters.

	A good comparison to what this class is about is to put it aside known formats like the main formats of
	3dsmax, blender and others, as well as FBX or Collada DAE.

	In sum, this class represents intermediate data for a game world and acts as an interface to load/save
	these game worlds from and to remote means like the hard drive in multiple formats, in comformance to 
	the specification.

	One common approach when prototyping games is to create by hand a XML file with some entities properly configured in it
	(following the nephilim scene spec), then load it to memory using this class. After that, use the automatic engine facilities
	that will convert this data into an actual playable game world.

	\todo Write the spec including spatialization and other details
*/
class NEPHILIM_API SceneFormat
{
public:

	struct Entity
	{
		String name;
	};

	std::list<Entity> entities;
};

};
NEPHILIM_NS_END
#endif // NephilimSceneFormat_h__
