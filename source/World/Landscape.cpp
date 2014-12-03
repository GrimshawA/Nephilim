#include <Nephilim/World/Landscape.h>

NEPHILIM_NS_BEGIN

/// Construction of the basic parameters
Landscape::Landscape()
{
	terrain.load("heightmap.png");
}

/// Get the location of this Landscape object
Vector3D Landscape::getLandscapeLocation()
{
	return Vector3D();
}

NEPHILIM_NS_END