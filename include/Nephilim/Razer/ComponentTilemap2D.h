#ifndef NephilimRazerComponentTilemap2D_h__
#define NephilimRazerComponentTilemap2D_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>
#include <Nephilim/VertexArray.h>
#include <Nephilim/Razer/Component.h>

#include <vector>

NEPHILIM_NS_BEGIN
namespace rzr
{

class NEPHILIM_API Tilemap2DLayer
{
public:
	void generateRenderData();

	String           mName;       ///< Name of the layer
	int              mWidth;      ///< Amount of tiles per line
	int              mHeight;     ///< Amount of tiles per column
	std::vector<int> mTileData;   ///< Original tile data
	VertexArray      mVertexData; ///< Rendering data for the layer
	IndexArray       mIndexData;  ///< Rendering data for the layer
};

/**
	\class ComponentTilemap2D
	\brief 3D transform for a entity, scale + rotation + translation
*/
class NEPHILIM_API ComponentTilemap2D : public Component
{
public:
	bool load(const String& filename);

	void getTileShape(int index, float& x, float &y, float& w, float& h);

	std::vector<Tilemap2DLayer> mLayers;
};

};
NEPHILIM_NS_END

#endif // NephilimRazerComponentTilemap2D_h__
