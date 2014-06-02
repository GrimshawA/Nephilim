#include <Nephilim/Razer/ComponentTilemap2D.h>
#include <Nephilim/Strings.h>
#include <Nephilim/Vectors.h>
#include <Nephilim/Tilemap.h>
#include <Nephilim/Logger.h>
#include <Nephilim/Path.h>

#include <pugixml/pugixml.hpp>

NEPHILIM_NS_BEGIN
namespace rzr
{

/// Initializes an empty world
ComponentTilemap2D::ComponentTilemap2D()
: mTileSize(1.f, 1.f, 1.f)
, mChunkSize(30.f, 30.f)
{

}

/// Ensure destruction of all dependencies
ComponentTilemap2D::~ComponentTilemap2D()
{

}

/// The tiles for the main layer are cubes instead of flat squares
void ComponentTilemap2D::useCubes(bool enabled)
{

}

/// Enables the side view type of map mode
void ComponentTilemap2D::setSideView(bool enabled)
{

}

bool ComponentTilemap2D::load(const String& filename)
{
	Path path(filename);

	if(path.getExtension() == "tmx")
	{
		// We're trying to load a Tiled map file (XML)
		Tilemap level;
		level.loadTMX(filename);
		
		// Total map size
		mLevelSize.x = level.mWidth * mTileSize.x;
		mLevelSize.y = level.mHeight * mTileSize.y;


		Log("=> Loading 2D level with size(%f, %f)", mLevelSize.x, mLevelSize.y);

		for(size_t i = 0; i < level.mLayers.size(); ++i)
		{
			mLayers.push_back(Layer(level.mLayers[i]->mName));
		}

		allocateChunks();

		/// For each layer, lets fill the tile data
		for(size_t i = 0; i < level.mLayers.size(); ++i)
		{
			
		}
	}

	return true;
}

/// Generates a chunk list for culling out for the entire map
void ComponentTilemap2D::allocateChunks()
{
	int pagesHorizontal = ceilf(mLevelSize.x / (mChunkSize.x * mTileSize.x));
	int pagesVertical = ceilf(mLevelSize.y / (mChunkSize.y * mTileSize.y));

	mChunks.resize(pagesHorizontal * pagesVertical);
	for(size_t i = 0; i < mChunks.size(); ++i)
	{
		mChunks[i].mLayers.resize(mLayers.size());
	}

	Log("=> Allocated %d chunks for this map", mChunks.size());
}

void Tilemap2DLayer::generateRenderData()
{
	mVertexData.format.attributes.push_back(VertexFormat::Attribute(sizeof(float), 2, VertexFormat::Position));
	mVertexData.format.attributes.push_back(VertexFormat::Attribute(sizeof(float), 4, VertexFormat::Color));
	mVertexData.format.attributes.push_back(VertexFormat::Attribute(sizeof(float), 2, VertexFormat::TexCoord));

	// Allocate Width * Height * 4 vertices per tile
	mVertexData.allocateData(4 * mHeight * mWidth);

	// Allocate the faces, each tile has 2 faces, which is 6 indices
	mIndexData.indices.resize(6 * mHeight * mWidth);

	struct vertex_format
	{
		vec2 position;
		vec4 color;
		vec2 uv;
	};

	vertex_format* tile_array = reinterpret_cast<vertex_format*>(&mVertexData.data[0]);
	int tile_index = 0;
	int vindex = 0;
	int iindex = 0;

	// For each tile, generate the actual rendering data for it
	for(int j = 0; j < mHeight; ++j)
	{
		for(int i = 0; i < mWidth; ++i)
		{
			
			tile_array[vindex].position   = vec2(i * 32.f,        -j * 32.f); // top-left corner
			tile_array[vindex+1].position = vec2(i * 32.f + 32.f, -j * 32.f); // top-right corner
			tile_array[vindex+2].position = vec2(i * 32.f + 32.f, -j * 32.f + 32.f); // bottom-right corner
			tile_array[vindex+3].position = vec2(i * 32.f,        -j * 32.f + 32.f); // bottom-left corner

			if(mTileData[tile_index] == 0)
			{
				tile_array[vindex].position   = vec2(0.f, 0.f); // top-left corner
				tile_array[vindex+1].position = vec2(0.f, 0.f); // top-right corner
				tile_array[vindex+2].position = vec2(0.f, 0.f); // bottom-right corner
				tile_array[vindex+3].position = vec2(0.f, 0.f); // bottom-left corner
			}

			float alpha = mTileData[tile_index] == 0 ? alpha = 0.f : alpha = 1.f;

			tile_array[vindex].color = vec4(1.f, 1.f, 1.f, alpha);
			tile_array[vindex+1].color = vec4(1.f, 1.f, 1.f, alpha);
			tile_array[vindex+2].color = vec4(1.f, 1.f, 1.f, alpha);
			tile_array[vindex+3].color = vec4(1.f, 1.f, 1.f, alpha);

			int tile_id = mTileData[tile_index];

			float texture_width = 265.f;
			float texture_height = 199.f;

			float u = 0.f;
			float v = 0.f;
			for(int k = 1; k < tile_id; ++k)
			{
				// get the actual uv

				//Log("Tile id %d, COORDS %f, %f", k, u, v);

				u += 32.f;
				if(u >= 256.f)
				{
					u = 0.f;
					v += 32.f;
				}
			}

			float u2 = u + 32.f;
			float v2 = v + 32.f;

			u /= texture_width;
			v /= texture_height;
			u2 /= texture_width;
			v2 /= texture_height;

			//Log("Tile uses gid %d", mTileData[tile_index]);

			tile_array[vindex]  .uv = vec2(u, v);
			tile_array[vindex+1].uv = vec2(u2, v);
			tile_array[vindex+2].uv = vec2(u2, v2);
			tile_array[vindex+3].uv = vec2(u, v2);

			mIndexData.indices[iindex] = vindex+1;
			mIndexData.indices[iindex+1] = vindex+2;
			mIndexData.indices[iindex+2] = vindex+3;
			mIndexData.indices[iindex+3] = vindex+1;
			mIndexData.indices[iindex+4] = vindex+3;
			mIndexData.indices[iindex+5] = vindex;

			tile_index ++;
			vindex += 4;
			iindex += 6;
		}
	}
}

// Debug only
void ComponentTilemap2D::getTileShape(int index, float& x, float &y, float& w, float& h)
{
	/*if(mLayers[0].mTileData[index] == 0)
	{
		//no where

	}
	else
	{
		int tile_index = 0;
		for(int j = 0; j < mLayers[0].mHeight; ++j)
		{
			for(int i = 0; i < mLayers[0].mWidth; ++i)
			{

				if(tile_index == index)
				{
					x = i * 32.f + 16.f;
					y = j * 32.f + 16.f;
					w = 32.f;
					h = 32.f;
				}
				tile_index ++;
			}
		}
	}*/
}


};
NEPHILIM_NS_END