#ifndef NephilimWorldATilemapComponent_h__
#define NephilimWorldATilemapComponent_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/ASceneComponent.h>

#include <Nephilim/Foundation/String.h>
#include <Nephilim/Foundation/Vector.h>
#include <Nephilim/World/Tilemap.h>
#include <Nephilim/Graphics/VertexArray.h>
#include <Nephilim/Graphics/IndexArray.h>

#include <vector>

NEPHILIM_NS_BEGIN

class Tilemap;

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
	\class ATilemapComponent
	\brief Place a tilemap into the world
*/
class NEPHILIM_API ATilemapComponent : public ASceneComponent
{
public:
	/// Initializes an empty world
	ATilemapComponent();

	/// Ensure destruction of all dependencies
	~ATilemapComponent();

	class Chunk;
	class Layer;

	/// Check if the tilemap has a layer with this name
	bool hasLayer(const String& layerName);

	/// Check if a given layer has a given object
	bool hasObject(const String& layerName, const String& objectName);

	/// Get how many points are there in the object
	size_t getObjectPointCount(const String& layerName, const String& objectName);

	/// Get the point i in the given object
	vec2 getObjectPoint(const String& layerName, const String& objectName, int index);

	/// Get the position of the given object
	vec2 getObjectPosition(const String& layerName, const String& objectName);

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
	
	//void generateCollisionData(const String& layerName, CollisionData& cd);

	/// Takes the input data from tileLayer and generates the geometry for rendering as cubes
	void generateCubes(Tilemap::Layer* tileLayer, const String& destLayer);

	void generateTiles(Tilemap::Layer* tileLayer, const String& destLayer);

	void getTileShape(int index, float& x, float &y, float& w, float& h);

	/// Change the tile size
	void setTileSize(vec3 size);

	std::vector<Layer> mLayers; ///< The layer information for this tilemap level
	std::vector<Chunk> mChunks;

	Tilemap mTilemapData; ///< The raw tilemap data stays in memory 

	vec3 mTileSize;  ///< The absolute size of each grid cell a.k.a tile
	vec2 mLevelSize; ///< The total size of this level, usually from (0,0) to (size.x, size.y) , in absolute coordinates
	vec2 mLevelSizeInTiles; ///< Size of this level, in number of tiles
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

NEPHILIM_NS_END
#endif // NephilimWorldATilemapComponent_h__
