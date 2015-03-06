#ifndef NephilimWorldLanscape_h__
#define NephilimWorldLanscape_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/GameObject.h>
#include <Nephilim/World/ATerrainComponent.h>

#include <Nephilim/Foundation/Transform.h>
#include <Nephilim/Foundation/Vector.h>

NEPHILIM_NS_BEGIN

class World;

/**
	\class Landscape
	\brief An instance in the world of a landscape object

	Landscapes are especially optimized for terrains, details
	like rocks and foliage and trees. Also support 2D spline based
	terrains, 2D static sprites, and tile map based maps.

	One should never need to inherit Landscape, only write new
	components for it. Usually, its only inherited for custom streaming features
	or really fancy new terrain handling methods.
*/
class NEPHILIM_API Landscape : public GameObject
{
public:

	struct LandscapeHeightmapTerrainParams
	{

	};

	ATerrainComponent terrain;

	/// This is the root transform that affects the entire landscape
	Transform rootTransform;

public:

	/// Construction of the basic parameters
	Landscape();

	/// Get the location of this Landscape object
	Vector3D getLandscapeLocation();
};

NEPHILIM_NS_END
#endif // NephilimWorldLanscape_h__
