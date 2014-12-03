#ifndef NephilimWorldLanscape_h__
#define NephilimWorldLanscape_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Vectors.h>
#include <Nephilim/World/CTransform.h>
#include <Nephilim/World/CHeightmapTerrain.h>

NEPHILIM_NS_BEGIN

class World;

/**
	\class Landscape
	\brief An instance in the world of a landscape object

	Landscapes are especially optimized for terrains, details
	like rocks and foliage and trees. Also support 2D spline based
	terrains, 2D static sprites, and tile map based maps.
*/
class NEPHILIM_API Landscape
{
public:


	CHeightmapTerrain terrain;

	/// This is the root transform that affects the entire landscape
	CTransform rootTransform;

public:

	/// Construction of the basic parameters
	Landscape();

	/// Get the location of this Landscape object
	Vector3D getLandscapeLocation();

};

NEPHILIM_NS_END
#endif // NephilimWorldLanscape_h__
