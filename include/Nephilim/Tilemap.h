#ifndef NephilimTilemap_h__
#define NephilimTilemap_h__

#include "Platform.h"
#include "Strings.h"
#include "Vectors.h"

#include <vector>

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


	class Layer
	{
	public:
		
		int getTileCount();

		void getTileShape(int index, float& x, float& y, float& w, float& h);

		String mName;
		int mWidth;
		int mHeight;
		int mType; ///1 for tile layer , 2 for object layer
		std::vector<Uint16> mTileData;
	};

	Layer* getLayer(int index);


	std::vector<Layer*> mLayers;
};

NEPHILIM_NS_END
#endif // NephilimTilemap_h__
