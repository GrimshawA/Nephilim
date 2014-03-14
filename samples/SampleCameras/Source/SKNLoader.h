#ifndef SKNLoader_h__
#define SKNLoader_h__

#include <Nephilim/Strings.h>
#include <Nephilim/Geometry.h>
#include <Nephilim/Logger.h>
#include <Nephilim/File.h>
#include <Nephilim/SkinMesh.h>
#include <Nephilim/DataStream.h>

using namespace nx;

class SKNLoader
{
public:

	static void Load(GeometryData& data, const String& filename)
	{
		File fp(filename, IODevice::BinaryRead);
		if(fp)
		{
			DataStream stream(fp);

			SkinMesh outputMesh;

			Int32 magic;
			Int16 version, numObjects;

			stream >> magic >> version >> numObjects;

			Log("Magic: %d, Version: %d, NumObjects %d", magic, version, numObjects);

			// Parse geometry
			if (version == 1 || version == 2)
			{
				// Contains material headers.
				Int32 numMaterialHeaders;
				stream >> numMaterialHeaders;
				for (int i = 0; i < numMaterialHeaders; ++i)
				{	
					for(int j = 0; j < 64; ++j)
						stream.readChar();

					Int32 startVertex, numVertices, startIndex, numIndices;
					
					stream >> startVertex >> numVertices >> startIndex >> numIndices;
				}

				// Read in model data.
				Int32 numIndices, numVertices;
				stream >> numIndices >> numVertices;

				std::vector<Int16> indices;

				for (int i = 0; i < numIndices; ++i)
				{
					Int16 indice;
					stream >> indice;
					indices.push_back(indice);

					outputMesh.mFaces.push_back(indice);
				}

				std::vector<vec3> vertices;
				std::vector<vec2> uv;
				std::vector<vec4> boneIDs;
				std::vector<vec4> boneWeights;

				for (int i = 0; i < numVertices; ++i)
				{
					//SKNVertex vertex = new SKNVertex();
					vec3 position;
					stream >> position.x >> position.y >> position.z;

					vertices.push_back(position);

					Int8 bonesIDs[4];

					for (int j = 0; j < 4; ++j)
					{
						// Reading bone indexes in the skeleton
						bonesIDs[j] = (Int8)stream.readChar();
					}

					boneIDs.push_back(vec4(bonesIDs[0], bonesIDs[1], bonesIDs[2], bonesIDs[3]));

					float weights[4];

					stream >> weights[0] >> weights[1] >> weights[2] >> weights[3];

					boneWeights.push_back(vec4(weights[0], weights[1], weights[2], weights[3]));

					vec3 normalVec;

					stream >> normalVec.x >> normalVec.y >> normalVec.z;

					vec2 uvCoords;

					stream >> uvCoords.x >> uvCoords.y;

					uv.push_back(uvCoords);

					SkinMesh::SkinMeshVertex vertex;
					vertex.position = position;
					vertex.uv = uvCoords;
					vertex.normal = normalVec;
					memcpy(&vertex.bones, bonesIDs, 4);
					memcpy(&vertex.weights, weights, 4 * sizeof(float));
					outputMesh.mVertices.push_back(vertex);
				}

				// Data exclusive to version two.
				if (version == 2)
				{
					Int32 fckit;
					stream >> fckit;
					stream >> fckit;
					stream >> fckit;
				}

				// ASSIGN GEOMETRY    
				for(size_t i = 0; i < indices.size(); ++i)
				{
					data.m_vertices.push_back(vertices[indices[i]]);
					data.m_texCoords.push_back(uv[indices[i]]);
					data.boneIDs.push_back(boneIDs[indices[i]]); // still need to remap from bone indices to actual bones with the skeleton data
					data.boneWeights.push_back(boneWeights[indices[i]]);
				}
			}

			Log("%s Model Loaded!", filename.c_str());

			if(outputMesh.saveToFile("riven.skin"))
			{
				Log("%s SkinMesh Written to disk!", "riven.skin");
			}
		}
	}
};

#endif // SKNLoader_h__