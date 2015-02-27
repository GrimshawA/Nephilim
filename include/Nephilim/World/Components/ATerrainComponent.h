#ifndef NephilimWorldATerrainComponent_h__
#define NephilimWorldATerrainComponent_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/Components/ASceneComponent.h>
#include <Nephilim/Graphics/Texture2D.h>
#include <Nephilim/Graphics/Geometry.h>

#include <Nephilim/Foundation/Image.h>

NEPHILIM_NS_BEGIN

/**
	\class ATerrainComponent
	\brief Places a terrain heightmap into the world
*/
class NEPHILIM_API ATerrainComponent : public ASceneComponent
{
public:

	bool load(const String& heightmapFileName);

	Image heightmap;
	Uint8* heightmapRaw;

	GeometryObject geometry;
	Texture2D surfaceTex;
};

NEPHILIM_NS_END
#endif // NephilimWorldATerrainComponent_h__
