#ifndef NephilimRazerComponentTilemap2D_h__
#define NephilimRazerComponentTilemap2D_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>
#include <Nephilim/Vectors.h>
#include <Nephilim/Tilemap.h>
#include <Nephilim/VertexArray.h>
#include <Nephilim/IndexArray.h>
#include <Nephilim/CollisionData.h>
#include <Nephilim/Razer/Component.h>

#include <vector>

NEPHILIM_NS_BEGIN

class Tilemap;

namespace rzr
{

class NEPHILIM_API Tilemap2DLayer
{
public:
	void generateRenderData();

	String           mName;       ///< Name of the layer
	int              mWidth;      ///< Amount of tiles per line
	int              mHeight;     ///< Amount of tiles per column
	std::vector<Uint16> mTileData;   ///< Original tile data


	/// A chunk layer can have N different tilesets and a vertex array is made for each one
	std::vector<VertexArray> mVertexSets;
	std::vector<IndexArray>  mIndexSets;
	std::vector<String>      mTextureSets;
};

/**
	\class ComponentTilemap2D
	\brief Manages a 2D level by itself
*/
class NEPHILIM_API ComponentTilemap2D : public Component
{
public:
	/// Initializes an empty world
	ComponentTilemap2D();

	/// Ensure destruction of all dependencies
	~ComponentTilemap2D();

	class Chunk;
	class Layer;

	/// The tiles for the main layer are cubes instead of flat squares
	void useCubes(bool enabled);

	/// Enables the side view type of map mode
	void setSideView(bool enabled);

	/// Load a tilemap file to memory
	bool load(const String& filename);

	/// Generates a chunk list for culling out for the entire map
	void allocateChunks();

	/// Converts the in memory tile data from a single layer to renderizable chunk data
	void prepareLayer(const String& layerName);
	
	void generateCollisionData(const String& layerName, CollisionData& cd);

	/// Takes the input data from tileLayer and generates the geometry for rendering as cubes
	void generateCubes(Tilemap::Layer* tileLayer, const String& destLayer);

	void generateTiles(Tilemap::Layer* tileLayer, const String& destLayer);

	void getTileShape(int index, float& x, float &y, float& w, float& h);

	std::vector<Layer> mLayers; ///< The layer information for this tilemap level
	std::vector<Chunk> mChunks;

	Tilemap mTilemapData; ///< The raw tilemap data stays in memory 

	vec3 mTileSize;  ///< The absolute size of each grid cell a.k.a tile
	vec2 mLevelSize; ///< The total size of this level, usually from (0,0) to (size.x, size.y)
	vec2 mChunkSize; ///< The total size of each chunk, in tiles
	vec2i mNumChunks; ///< Number of horizontal and vertical chunks allocated

	class Chunk
	{
	public:
		/// Each chunk has its own set of layers with the render data
		std::vector<Tilemap2DLayer> mLayers;

		Tilemap2DLayer& getLayer(const String& name);
	};

	class Layer
	{
	public:
		Layer(const String& name)
		: mName(name)
		, mCubeBased(false)
		{

		}

		String mName;
		bool mCubeBased;
	};
};

};
NEPHILIM_NS_END

#endif // NephilimRazerComponentTilemap2D_h__
