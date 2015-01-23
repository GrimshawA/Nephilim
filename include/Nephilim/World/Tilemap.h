#ifndef NephilimTilemap_h__
#define NephilimTilemap_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>
#include <Nephilim/Foundation/Vector.h>
#include <Nephilim/Foundation/Rect.h>

#include <vector>
#include <map>
#include <stdint.h>

NEPHILIM_NS_BEGIN

class String;

struct Tile
{
	uint16_t id;
};

struct TilemapLayer
{

};

/**
	\class Tilemap
	\brief Stores tile data to be fed into any tile-based component

	The tilemaps are pretty abstract and just define a grid of cells and the type of each cell.
	It is lightweight yet versatile for multiple uses like different tile based terrain types,
	isometric and whatnot.

	Tilemaps are also not tied to a given orientation, each layer can be considered a slice with no particular orientation.

	Tilemaps are a bit like heightmaps, they can be chunky in memory and should only be kept if needed. 
	Usually, a huge tilemap can be loaded for an entire map, and portions of it will be fetched as needed to make render data.

	This can also be used for chunks of voxels quite easily, the lookups are really efficient to get the tile ID.
*/
class NEPHILIM_API Tilemap
{
public:

	struct MapSlice
	{
		std::vector<Tile> tileData; ///< The actual tile data of this slice
	};

	/// The slices in this tile data
	/// Usually assumed to be ordered from back-to-front or bottom-to-top depending on the context
	std::vector<MapSlice> slices;

	int32_t width; ///< The number of horizontal tiles
	int32_t height; ///< The number of vertical tiles

public:
	enum FileFormat
	{
		Binary,
		XML,
		TMX
	};

	/// This will save the data into a file
	bool saveToFile(const String& filename, FileFormat format);

	/// Fill the tilemap with a new size and slice count
	void fill(int32_t w, int32_t h, int32_t sliceCount, uint16_t fillID);

	/// Get a tile anywhere in the tilemap, no bound checking
	Tile getTile(std::size_t slice_index, std::size_t x, std::size_t y);

	bool loadTMX(const String& filename);

	int getLayerCount();

	/// Get the right UV for a given tile in a given layer
	FloatRect getTileUV(const String& layerName, std::size_t tileIndex);

	class Object
	{
	public:
		enum Type
		{
			Rectangle = 0,
			Ellipse,
			Polygon,
			PolyLine
		};

		int mObjectType;
		String mName;
		String mType;
		std::map<String,String> mProperties;
		std::vector<vec2> mPoints;
		vec2 mPosition;
	};

	class Layer
	{
	public:

		enum Type
		{
			Tiles = 0,
			Objects
		};
		
		int getTileCount();

		int getTile(int index);

		int getType();

		void getTileShape(int index, float& x, float& y, float& w, float& h);

		vec2 getObjectPosition(const String& name);

		/// Get a object from its name
		Object* getObject(const String& name);

		/// Check if the 2D coordinate is a valid tile coordinate in the layer
		bool isValidCoordinate2D(vec2i coord);


		String mName;
		int mWidth;
		int mHeight;
		int mType; ///1 for tile layer , 2 for object layer
		std::vector<Uint16> mTileData;
		std::vector<Object> mObjects;
	};

	class Tileset
	{
	public:
		String mPath; ///< Where the tileset is
		String mName; ///< The name of the tileset
		int mWidth;   ///< Width of the tileset in pixels
		int mHeight;  ///< Height of the tileset in pixels
		int mFirstGID;///< First tile's GID
		int mLastGID; ///< Last tile's GID
		int mSpacing; ///< Spacing between tiles
		int mTileWidth;///< Each tile's width in pixels
		int mTileHeight; ///< Each tile's height in pixels

		void computeLastGid();

		FloatRect getNormalizedCoordinates(int gid);

		bool containsGid(int gid);
	};

	Layer* getLayer(int index);

	Layer* getLayerByName(const String& name);

	

	void convertGIDtoUV(int gid, FloatRect& rect);

	std::size_t getTilesetIndexOfGid(int gid);


	std::vector<Layer*> mLayers;
	std::vector<Tileset> mTilesets;
	int mWidth;
	int mHeight;
	int mTileWidth;
	int mTileHeight;
};

NEPHILIM_NS_END
#endif // NephilimTilemap_h__
