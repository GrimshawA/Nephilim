#ifndef NephilimTilemap_h__
#define NephilimTilemap_h__

#include "Platform.h"
#include "Strings.h"
#include "Vectors.h"
#include "Rect.h"

#include <vector>
#include <map>

NEPHILIM_NS_BEGIN

class String;

/**
	\class Tilemap
	\brief Can load tilemap data from different formats

	Supports multiple layers, multiple tilesets, multiple formats, properties and object layers.
*/
class NEPHILIM_API Tilemap
{
public:
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
