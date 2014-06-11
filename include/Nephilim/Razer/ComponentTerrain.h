#ifndef NephilimRazerComponentTerrain_h__
#define NephilimRazerComponentTerrain_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Texture.h>
#include <Nephilim/Image.h>
#include <Nephilim/Geometry.h>
#include <Nephilim/Razer/Component.h>

NEPHILIM_NS_BEGIN
namespace rzr
{

/**
	\class ComponentTransform
	\brief 3D transform for a entity, scale + rotation + translation
*/
class NEPHILIM_API ComponentTerrain : public Component
{
public:

	bool load(const String& heightmapFileName);

	Image heightmap;
	Uint8* heightmapRaw;

	GeometryData geometry;
	Texture surfaceTex;
};

};
NEPHILIM_NS_END
#endif // NephilimRazerComponentTerrain_h__
