#include <Nephilim/World/ComponentTilemap2D.h>
#include <Nephilim/Foundation/String.h>
#include <Nephilim/Foundation/Vector.h>
#include <Nephilim/World/Tilemap.h>
#include <Nephilim/Foundation/Logging.h>
#include <Nephilim/Foundation/Path.h>
#include <Nephilim/Foundation/Math.h>

#include <pugixml/pugixml.hpp>

NEPHILIM_NS_BEGIN
namespace rzr
{

void ComponentTilemap2D::generateTiles(Tilemap::Layer* tileLayer, const String& destLayer)
{
	Log("=> Preparing a layer of tiles");

	// Chunk by chunk, generate its data for the specified layer
	for(std::size_t i = 0; i < mChunks.size(); ++i)
	{		
		int tileCount = 0;
		
		std::vector<int> tileCounts(mTilemapData.mTilesets.size());

		// Iterate all tiles in this chunk in order to count how many tiles are needed.
		for(int tx = 0; tx < mChunkSize.x; ++tx)
		{
			for(int ty = 0; ty < mChunkSize.y; ++ty)
			{
				int tileIndex1D = 0;

				vec2i chunkIndex2D = vec2i(i % mNumChunks.x, i / mNumChunks.x);

				vec2i chunkFirstTileIndex2D(chunkIndex2D.x * mChunkSize.x, chunkIndex2D.y * mChunkSize.y);
				vec2i globalTileIndex2D = chunkFirstTileIndex2D + vec2i(tx,ty);
				tileIndex1D = globalTileIndex2D.y * (mLevelSizeInTiles.x) + globalTileIndex2D.x;

				if(tileLayer->isValidCoordinate2D(globalTileIndex2D) && tileLayer->getTile(tileIndex1D) > 0)
				{
					tileCount++;
					tileCounts[mTilemapData.getTilesetIndexOfGid(tileLayer->getTile(tileIndex1D))]++;
				}
			}
		}

		Log("Chunk %d has %d tiles.", i, tileCount);
		for(std::size_t j = 0; j < tileCounts.size(); ++j)
		{
			Log("Tileset %d has %d tiles.", j, tileCounts[j]);
		}

		// Generate the vertex array for this chunk and layer
		Tilemap2DLayer& dl = mChunks[i].getLayer(destLayer);
		dl.mVertexSets.resize(tileCounts.size());
		dl.mTextureSets.resize(tileCounts.size());
		dl.mIndexSets.resize(tileCounts.size());
		for(std::size_t j = 0; j < tileCounts.size(); ++j)
		{
			if(tileCounts[j] > 0)
			{
				dl.mVertexSets[j].addAttribute(sizeof(float), 2, VertexFormat::Position);
				dl.mVertexSets[j].addAttribute(sizeof(float), 4, VertexFormat::Color);
				dl.mVertexSets[j].addAttribute(sizeof(float), 2, VertexFormat::TexCoord);

				dl.mVertexSets[j].allocateData(tileCounts[j] * 4);

				dl.mIndexSets[j].indices.resize(tileCounts[j] * 6);

				struct v_format
				{
					vec2 p;
					vec4 c;
					vec2 uv;
				};

				v_format* vbuff = reinterpret_cast<v_format*>(&dl.mVertexSets[j]._data[0]);

				int tc = 0;

				// Fill in the vertex data
				for(int tx = 0; tx < mChunkSize.x; ++tx)
				{
					for(int ty = 0; ty < mChunkSize.y; ++ty)
					{
						int tileIndex1D = 0;

						vec2i chunkIndex2D = vec2i(i % mNumChunks.x, i / mNumChunks.x);
						vec2i chunkFirstTileIndex2D(chunkIndex2D.x * mChunkSize.x, chunkIndex2D.y * mChunkSize.y);
						vec2i globalTileIndex2D = chunkFirstTileIndex2D + vec2i(tx,ty);
						tileIndex1D = globalTileIndex2D.y * (mLevelSizeInTiles.x) + globalTileIndex2D.x;

						if(tileLayer->isValidCoordinate2D(globalTileIndex2D) && tileLayer->getTile(tileIndex1D) > 0)
						{
							// Here we have a valid tile index that needs to be built
							/*vbuff[tc*4+0].p = vec2(globalTileIndex2D.x * mTileSize.x + mTileSize.x, -globalTileIndex2D.y * mTileSize.y);
							vbuff[tc*4+1].p = vec2(globalTileIndex2D.x * mTileSize.x + mTileSize.x, -globalTileIndex2D.y * mTileSize.y - mTileSize.y);
							vbuff[tc*4+2].p = vec2(globalTileIndex2D.x * mTileSize.x              , -globalTileIndex2D.y * mTileSize.y - mTileSize.y);
							vbuff[tc*4+3].p = vec2(globalTileIndex2D.x * mTileSize.x              , -globalTileIndex2D.y * mTileSize.y);*/

							vbuff[tc*4+0].p = vec2((globalTileIndex2D.x + 1) * mTileSize.x, -(globalTileIndex2D.y + 0) * mTileSize.y);
							vbuff[tc*4+1].p = vec2((globalTileIndex2D.x + 1) * mTileSize.x, -(globalTileIndex2D.y + 1) * mTileSize.y);
							vbuff[tc*4+2].p = vec2((globalTileIndex2D.x + 0) * mTileSize.x, -(globalTileIndex2D.y + 1) * mTileSize.y);
							vbuff[tc*4+3].p = vec2((globalTileIndex2D.x + 0) * mTileSize.x, -(globalTileIndex2D.y + 0) * mTileSize.y);

							Log("Tile %d is at (%f,%f), (%f,%f), (%f,%f), (%f,%f)", tc, vbuff[tc*4+0].p.x, vbuff[tc*4+0].p.y, vbuff[tc*4+1].p.x, vbuff[tc*4+1].p.y, vbuff[tc*4+2].p.x, vbuff[tc*4+2].p.y, vbuff[tc*4+3].p.x, vbuff[tc*4+3].p.y);

							vbuff[tc*4+0].c = vec4(1.f, 1.f, 1.f, 1.f);
							vbuff[tc*4+1].c = vec4(1.f, 1.f, 1.f, 1.f);
							vbuff[tc*4+2].c = vec4(1.f, 1.f, 1.f, 1.f);
							vbuff[tc*4+3].c = vec4(1.f, 1.f, 1.f, 1.f);

							//vec4 rc(math::random(0.f, 1.f), math::random(0.f, 1.f), math::random(0.f, 1.f), 1.f);
							//vbuff[tc*4+0].c = rc;
							//vbuff[tc*4+1].c = rc;
							//vbuff[tc*4+2].c = rc;
							//vbuff[tc*4+3].c = rc;

							FloatRect r = mTilemapData.getTileUV(destLayer, tileIndex1D);
							vbuff[tc*4+0].uv = vec2(r.width, r.top);
							vbuff[tc*4+1].uv = vec2(r.width, r.height);
							vbuff[tc*4+2].uv = vec2(r.left, r.height);
							vbuff[tc*4+3].uv = vec2(r.left, r.top);

							dl.mIndexSets[j].indices[tc*6+0] = tc*4+0;
							dl.mIndexSets[j].indices[tc*6+1] = tc*4+1;
							dl.mIndexSets[j].indices[tc*6+2] = tc*4+2;
							dl.mIndexSets[j].indices[tc*6+3] = tc*4+0;
							dl.mIndexSets[j].indices[tc*6+4] = tc*4+2;
							dl.mIndexSets[j].indices[tc*6+5] = tc*4+3;

							tc++;
						}
					}
				}
			}
		}
	}
}


/// Takes the input data from tileLayer and generates the geometry for rendering as cubes
void ComponentTilemap2D::generateCubes(Tilemap::Layer* tileLayer, const String& destLayer)
{
		Log("=> Cube generation start");

		// Check how many cubes will be needed
		int cubesNeeded = 0;
		for(std::size_t i = 0; i < tileLayer->mTileData.size(); ++i)
		{
			if(tileLayer->mTileData[i] > 0)
			{
				cubesNeeded ++;
			}
		}

		// Chunk by chunk, generate its data for the specified layer
		for(std::size_t i = 0; i < mChunks.size(); ++i)
		{
			Chunk& c = mChunks[i];
			Tilemap2DLayer& cl = c.getLayer(destLayer);

			
		}

		Log("=> Cube generation end");
}


};
NEPHILIM_NS_END