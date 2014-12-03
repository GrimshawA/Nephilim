#ifndef NephilimWorldBlueprint_h__
#define NephilimWorldBlueprint_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

class World;

/**
	\class Blueprint
	\brief An instanced structure based on the blueprint system

	Blueprints are literally plans to put a structure together procedurally
	from smaller components. A raw asset with the blueprint is used to instance
	as many structures like that as we want.

	A blueprint asset is made either by code or by an editor, ala The Sims house building,
	then the data is generated from the asset and used to spawn actual geometry with LOD's
	occlusion zones and all kinds of fancy stuff.

*/
class NEPHILIM_API Blueprint
{
private:

};

NEPHILIM_NS_END
#endif // NephilimWorldBlueprint_h__
