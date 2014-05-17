#ifndef NephilimTilemap_h__
#define NephilimTilemap_h__

#include "Platform.h"
#include "Strings.h"
#include "Vectors.h"

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

		String mName;
		int mWidth;
		int mHeight;
		int mType; ///1 for tile layer , 2 for object layer
		std::vector<Uint16> mTileData;
		std::vector<Object> mObjects;
	};

	Layer* getLayer(int index);

	Layer* getLayerByName(const String& name);


	std::vector<Layer*> mLayers;
};

NEPHILIM_NS_END
#endif // NephilimTilemap_h__
