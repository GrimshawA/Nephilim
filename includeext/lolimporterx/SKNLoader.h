#ifndef SKNLoader_h__
#define SKNLoader_h__

#include <Nephilim/Foundation/String.h>
#include <Nephilim/Foundation/Logging.h>
#include <Nephilim/Foundation/File.h>
#include <Nephilim/Foundation/DataStream.h>

#include <Nephilim/Graphics/Geometry.h>

using namespace nx;

#include "SKLLoader.h"

struct AssetFileHeader
{
	uint32_t id;
	uint8_t version;
};

struct GeometryFileHeader
{
	uint32_t num_meshes;
	uint32_t flags;
};

// nothing in the format is mandatory, instead of forcing an order, we use header + data chunks, supporting additional user data easily.
struct DataChunkHeader
{
	char id[20];
	uint32_t DataCount;
	uint32_t DataSize;
};

class SKNLoader
{
public:

	/// Triangles of the mesh
	std::vector<uint16_t> faces;
	std::vector<Vector3D> vertices;
	std::vector<Vector3D> normals;
	std::vector<Vector4D> boneIDs;
	std::vector<Vector4D> boneWeights;
	std::vector<Vector2D> texCoords;


public:

	/// Write a .ngf file somewhere, with all the geometry and optionally skeletal data too
	/// The skeleton can also be saved to its own .skl file to be shared if needed
	bool write_ngf(const String& filename, SkeletonSKL* skeleton = nullptr)
	{
		File file(filename, IODevice::BinaryWrite);
		if (file)
		{
			DataStream str(file);

			AssetFileHeader fileHeader;
			fileHeader.id = 1;
			fileHeader.version = 1;

			GeometryFileHeader geometryFileHeader;
			geometryFileHeader.num_meshes = 1;

			file.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
			file.write(reinterpret_cast<char*>(&geometryFileHeader), sizeof(geometryFileHeader));

			DataChunkHeader dataChunkHeader;

			// Positions
			strcpy(dataChunkHeader.id, "POSITIONS\0");
			dataChunkHeader.DataCount = vertices.size();
			dataChunkHeader.DataSize = sizeof(Vector3D);
			str.write(&dataChunkHeader, sizeof(DataChunkHeader));
			str.write(vertices.data(), sizeof(Vector3D)* vertices.size());

			// Normals
			strcpy(dataChunkHeader.id, "NORMALS\0");
			dataChunkHeader.DataCount = normals.size();
			dataChunkHeader.DataSize = sizeof(Vector3D);
			str.write(&dataChunkHeader, sizeof(DataChunkHeader));
			str.write(normals.data(), sizeof(Vector3D)* normals.size());

			// TexCoord0
			strcpy(dataChunkHeader.id, "TEXCOORD0\0");
			dataChunkHeader.DataCount = texCoords.size();
			dataChunkHeader.DataSize = sizeof(Vector2D);
			str.write(&dataChunkHeader, sizeof(DataChunkHeader));
			str.write(texCoords.data(), sizeof(Vector2D)* texCoords.size());

			// Bone mapping
			strcpy(dataChunkHeader.id, "BONEINFLUENCES\0");
			dataChunkHeader.DataCount = vertices.size();
			dataChunkHeader.DataSize = sizeof(Vector4D) * 2;
			str.write(&dataChunkHeader, sizeof(DataChunkHeader));
			str.write(boneIDs.data(), sizeof(Vector4D) * vertices.size());
			str.write(boneWeights.data(), sizeof(Vector4D) * vertices.size());

			// Faces
			strcpy(dataChunkHeader.id, "FACES\0");
			dataChunkHeader.DataCount = faces.size();
			dataChunkHeader.DataSize = sizeof(uint32_t);
			str.write(&dataChunkHeader, sizeof(DataChunkHeader));
			str.write(faces.data(), sizeof(uint16_t)* faces.size());
		}


		return true;
	}

	void Load(GeometryObject& data, const String& filename)
	{
		File fp(filename, IODevice::BinaryRead);
		if(fp)
		{
			DataStream stream(fp);

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

					faces.push_back(indice);

					//outputMesh.mFaces.push_back(indice);
				}

				// Vertices

				vertices.resize(numVertices);
				texCoords.resize(numVertices);
				boneIDs.resize(numVertices);
				boneWeights.resize(numVertices);
				normals.resize(numVertices);

				std::vector<vec2> uv;


				for (int i = 0; i < numVertices; ++i)
				{
					//SKNVertex vertex = new SKNVertex();
					vec3 position;
					stream >> position.x >> position.y >> position.z;

					vertices[i] = position;

					Int8 bonesIDs[4];

					for (int j = 0; j < 4; ++j)
					{
						// Reading bone indexes in the skeleton
						bonesIDs[j] = (Int8)stream.readChar();
					}

					boneIDs[i] = (vec4(bonesIDs[0], bonesIDs[1], bonesIDs[2], bonesIDs[3]));

					float weights[4];

					stream >> weights[0] >> weights[1] >> weights[2] >> weights[3];

					boneWeights[i] = (vec4(weights[0], weights[1], weights[2], weights[3]));

					

					vec3 normalVec;

					stream >> normalVec.x >> normalVec.y >> normalVec.z;

					normals[i] = normalVec;

					vec2 uvCoords;

					stream >> uvCoords.x >> uvCoords.y;

					texCoords[i] = uvCoords;

					uv.push_back(uvCoords);

					/*SkinMesh::SkinMeshVertex vertex;
					vertex.position = position;
					vertex.uv = uvCoords;
					vertex.normal = normalVec;
					memcpy(&vertex.bones, bonesIDs, 4);
					memcpy(&vertex.weights, weights, 4 * sizeof(float));
					outputMesh.mVertices.push_back(vertex);*/
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
					data.vertices.push_back(vertices[indices[i]]);
					data.texcoords0.push_back(uv[indices[i]]);
					data.boneIDs.push_back(boneIDs[indices[i]]); // still need to remap from bone indices to actual bones with the skeleton data
					data.boneWeights.push_back(boneWeights[indices[i]]);
				}
			}

			Log("%s Model Loaded!", filename.c_str());

			/*if(outputMesh.saveToFile("riven.skin"))
			{
				Log("%s SkinMesh Written to disk!", "riven.skin");
			}*/
		}
	}
};

#endif // SKNLoader_h__