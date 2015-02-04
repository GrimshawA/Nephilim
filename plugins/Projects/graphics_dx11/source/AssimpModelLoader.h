#ifndef AssimpModelLoader_h__
#define AssimpModelLoader_h__

#include <Nephilim/Logger.h>
#include <Nephilim/Vectors.h>
#include <Nephilim/VertexArray.h>
#include <Nephilim/IndexArray.h>
using namespace nx;

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

/**
	\class AssimpModelLoader

	This class is part of the official plugin that loads models from Assimp

	It is used to open up a model file and then export the data to the engine structures.
*/
class AssimpModelLoader
{
public:

	void open(const char* filename, VertexArray& vertexArray, IndexArray& indexArray)
	{
		Assimp::Importer importer;

		// And have it read the given file with some example postprocessing
		// Usually - if speed is not the most important aspect for you - you'll 
		// propably to request more postprocessing than we do in this example.
		const aiScene* scene = importer.ReadFile(filename,
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType);

		if (scene)
		{
			Log("Model loaded %s\nHas %d meshes", filename, scene->mNumMeshes);

			vertexArray.addAttribute(sizeof(float), 3, VertexFormat::Position);
			vertexArray.addAttribute(sizeof(float), 4, VertexFormat::Color);


			for (size_t i = 0; i < scene->mNumMeshes; ++i)
			{
				aiMesh* mesh = scene->mMeshes[i];
				
				// Extract faces
				indexArray.indices.resize(mesh->mNumFaces * 3);
				for (size_t i = 0; i < mesh->mNumFaces; ++i)
				{
					indexArray.indices[i * 3 + 0] = mesh->mFaces[i].mIndices[0];
					indexArray.indices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
					indexArray.indices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];				
				}

				// Extract vertices
				vertexArray.allocateData(mesh->mNumVertices);
				
				struct vstruct
				{
					vec3 pv;
					vec4 cv;
				};

				vstruct* vv = reinterpret_cast<vstruct*>(&vertexArray.data[0]);

				for (size_t i = 0; i < mesh->mNumVertices; ++i)
				{
					vec3 v(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
					vec4 cv(1.f, 1.f, 1.f, 1.f);
				
					vv[i].pv = v;
					vv[i].cv = cv;
				}
			}

		}
		else
		{
			Log("Failed load!");
		}
	}
};

#endif // AssimpModelLoader_h__
