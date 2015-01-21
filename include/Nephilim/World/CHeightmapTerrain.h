#ifndef NephilimRazerComponentTerrain_h__
#define NephilimRazerComponentTerrain_h__

#include <Nephilim/Platform.h>

#include <Nephilim/Graphics/GLTexture.h>
#include <Nephilim/Graphics/Geometry.h>

#include <Nephilim/Foundation/Image.h>
#include <Nephilim/World/Component.h>

NEPHILIM_NS_BEGIN

/**
	\class ComponentTransform
	\brief 3D transform for a entity, scale + rotation + translation
*/
class NEPHILIM_API CHeightmapTerrain : public Component
{
public:

	bool load(const String& heightmapFileName);

	Image heightmap;
	Uint8* heightmapRaw;

	GeometryData geometry;
	Texture surfaceTex;
};

NEPHILIM_NS_END
#endif // NephilimRazerComponentTerrain_h__
