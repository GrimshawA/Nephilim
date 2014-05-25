#include <Nephilim/Razer/ComponentMesh.h>
#include <Nephilim/Tilemap.h>
#include <Nephilim/Logger.h>

NEPHILIM_NS_BEGIN

namespace rzr
{

ComponentMesh::ComponentMesh()
{
}

/// here i assemble the cube data from a single tilemap
bool ComponentMesh::loadCubesFromTilemap(Tilemap* tilemap)
{
	Tilemap::Layer* tileLayer = tilemap->getLayerByName("LevelData");

	if(!tileLayer)
		return false;
	
	// lets make the vertices
	int cubeCount = 0;

	for(size_t i = 0; i < tileLayer->getTileCount(); ++i)
	{
		if(tileLayer->mTileData[i] != 0)
			cubeCount ++;
	}

	Log("=> Loading %d cubes for the map", cubeCount);

	mVertexArray.format.attributes.push_back(VertexFormat::Attribute(sizeof(float), 3, VertexFormat::Position)); // vec3 position
	mVertexArray.format.attributes.push_back(VertexFormat::Attribute(sizeof(float), 4, VertexFormat::Color));    // vec4 color
	mVertexArray.format.attributes.push_back(VertexFormat::Attribute(sizeof(float), 2, VertexFormat::TexCoord));    // vec2 uv

	mVertexArray.allocateData(cubeCount * 8);
	mIndexArray.indices.resize(cubeCount * 30);

	struct VertexFormatDesc
	{
		vec3 p;
		vec4 c;
		vec2 uv;
	};

	VertexFormatDesc* vertexArray = reinterpret_cast<VertexFormatDesc*>(&mVertexArray.data[0]);

	// Search the cubes and start filling the geometry
	int cubeIndex = 0;
	for(size_t i = 0; i < tileLayer->getTileCount(); ++i)
	{
		// Create a cube for this solid block
		if(tileLayer->mTileData[i] != 0)
		{
			vec2i tileCoordinate(i % tileLayer->mWidth, i / tileLayer->mWidth);

			// 4 vertices
			vec3 v1(tileCoordinate.x * 32.f, -tileCoordinate.y * 32.f, 16.f); // top left, closer
			vec3 v2(tileCoordinate.x * 32.f + 32.f, -tileCoordinate.y * 32.f, 16.f); // top right, closer
			vec3 v3(tileCoordinate.x * 32.f + 32.f, -tileCoordinate.y * 32.f - 32.f, 16.f); // bottom right, closer
			vec3 v4(tileCoordinate.x * 32.f, -tileCoordinate.y * 32.f - 32.f, 16.f); // bottom left, closer
		
			vec3 v5(tileCoordinate.x * 32.f, -tileCoordinate.y * 32.f, -16.f); // top left, farther
			vec3 v6(tileCoordinate.x * 32.f + 32.f, -tileCoordinate.y * 32.f, -16.f); // top right, farther
			vec3 v7(tileCoordinate.x * 32.f + 32.f, -tileCoordinate.y * 32.f - 32.f, -16.f); // bottom right, farther
			vec3 v8(tileCoordinate.x * 32.f, -tileCoordinate.y * 32.f - 32.f, -16.f); // bottom left, farther

			vertexArray[cubeIndex*8 + 0].p = v1;
			vertexArray[cubeIndex*8 + 1].p = v2;
			vertexArray[cubeIndex*8 + 2].p = v3;
			vertexArray[cubeIndex*8 + 3].p = v4;
			vertexArray[cubeIndex*8 + 4].p = v5;
			vertexArray[cubeIndex*8 + 5].p = v6;
			vertexArray[cubeIndex*8 + 6].p = v7;
			vertexArray[cubeIndex*8 + 7].p = v8;

			//uv
			vertexArray[cubeIndex*8 + 0].uv = vec2(0.f, 0.f);
			vertexArray[cubeIndex*8 + 1].uv = vec2(1.f, 0.f);
			vertexArray[cubeIndex*8 + 2].uv = vec2(1.f, 1.f);
			vertexArray[cubeIndex*8 + 3].uv = vec2(0.f, 1.f);

			vertexArray[cubeIndex*8 + 4].uv = vec2(1.f, 1.f);
			vertexArray[cubeIndex*8 + 5].uv = vec2(0.f, 1.f);
			vertexArray[cubeIndex*8 + 6].uv = vec2(0.f, 0.f);
			vertexArray[cubeIndex*8 + 7].uv = vec2(1.f, 0.f);

			vertexArray[cubeIndex*8 + 0].c = vec4(1.f, 1.f, 1.f, 1.f);
			vertexArray[cubeIndex*8 + 1].c = vec4(1.f, 1.f, 1.f, 1.f);
			vertexArray[cubeIndex*8 + 2].c = vec4(1.f, 1.f, 1.f, 1.f);
			vertexArray[cubeIndex*8 + 3].c = vec4(1.f, 1.f, 1.f, 1.f);
			vertexArray[cubeIndex*8 + 4].c = vec4(1.f, 1.f, 1.f, 1.f);
			vertexArray[cubeIndex*8 + 5].c = vec4(1.f, 1.f, 1.f, 1.f);
			vertexArray[cubeIndex*8 + 6].c = vec4(1.f, 1.f, 1.f, 1.f);
			vertexArray[cubeIndex*8 + 7].c = vec4(1.f, 1.f, 1.f, 1.f);

			// Front face
			mIndexArray.indices[cubeIndex*30 + 0] = (cubeIndex * 8) + 1;
			mIndexArray.indices[cubeIndex*30 + 1] = (cubeIndex * 8) + 2;
			mIndexArray.indices[cubeIndex*30 + 2] = (cubeIndex * 8) + 0;
			mIndexArray.indices[cubeIndex*30 + 3] = (cubeIndex * 8) + 0;
			mIndexArray.indices[cubeIndex*30 + 4] = (cubeIndex * 8) + 2;
			mIndexArray.indices[cubeIndex*30 + 5] = (cubeIndex * 8) + 3;

			// Left Face
			mIndexArray.indices[cubeIndex*30 + 6] = (cubeIndex * 8) + 0;
			mIndexArray.indices[cubeIndex*30 + 7] = (cubeIndex * 8) + 3;
			mIndexArray.indices[cubeIndex*30 + 8] = (cubeIndex * 8) + 4;
			mIndexArray.indices[cubeIndex*30 + 9] = (cubeIndex * 8) + 4;
			mIndexArray.indices[cubeIndex*30 + 10] = (cubeIndex * 8) + 3;
			mIndexArray.indices[cubeIndex*30 + 11] = (cubeIndex * 8) + 7;

			// right face
			mIndexArray.indices[cubeIndex*30 + 12] = (cubeIndex * 8) + 5;
			mIndexArray.indices[cubeIndex*30 + 13] = (cubeIndex * 8) + 6;
			mIndexArray.indices[cubeIndex*30 + 14] = (cubeIndex * 8) + 2;
			mIndexArray.indices[cubeIndex*30 + 15] = (cubeIndex * 8) + 5;
			mIndexArray.indices[cubeIndex*30 + 16] = (cubeIndex * 8) + 2;
			mIndexArray.indices[cubeIndex*30 + 17] = (cubeIndex * 8) + 1;

			// top face
			mIndexArray.indices[cubeIndex*30 + 18] = (cubeIndex * 8) + 5;
			mIndexArray.indices[cubeIndex*30 + 19] = (cubeIndex * 8) + 1;
			mIndexArray.indices[cubeIndex*30 + 20] = (cubeIndex * 8) + 0;
			mIndexArray.indices[cubeIndex*30 + 21] = (cubeIndex * 8) + 5;
			mIndexArray.indices[cubeIndex*30 + 22] = (cubeIndex * 8) + 0;
			mIndexArray.indices[cubeIndex*30 + 23] = (cubeIndex * 8) + 4;

			mIndexArray.indices[cubeIndex*30 + 24] = (cubeIndex * 8) + 0;
			mIndexArray.indices[cubeIndex*30 + 25] = (cubeIndex * 8) + 0;
			mIndexArray.indices[cubeIndex*30 + 26] = (cubeIndex * 8) + 0;
			mIndexArray.indices[cubeIndex*30 + 27] = (cubeIndex * 8) + 0;
			mIndexArray.indices[cubeIndex*30 + 28] = (cubeIndex * 8) + 0;
			mIndexArray.indices[cubeIndex*30 + 29] = (cubeIndex * 8) + 0;

			cubeIndex ++;
		}
	}

	// Print arrays for debugging
	for(size_t j = 0; j < mIndexArray.indices.size(); ++j)
	{
		vec3 p = *reinterpret_cast<vec3*>(mVertexArray.getAttribute(0, mIndexArray.indices[j]));
		//Log("Index at %d is %d Vertex(%f, %f, %f)", j, mIndexArray.indices[j], p.x, p.y, p.z);
	}
	
	return true;
}

};
NEPHILIM_NS_END