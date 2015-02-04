#ifndef AssimpModelLoader_h__
#define AssimpModelLoader_h__

#include <Nephilim/Model/ModelLoader.h>
#include <Nephilim/Graphics/StaticMesh.h>
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
class AssimpModelLoader : public ModelLoader
{
public:

	/// Interface: asks the loader to retrieve its set of mesh data to our storage container
	virtual ModelLoaderResult load(const ModelLoaderParams& params)
	{
		Assimp::Importer importer;

		// And have it read the given file with some example postprocessing
		// Usually - if speed is not the most important aspect for you - you'll 
		// propably to request more postprocessing than we do in this example.
		const aiScene* scene = importer.ReadFile(params.filename,
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType);

		if (scene)
		{
			Log("Model loaded %s\nHas %d meshes", params.filename.c_str(), scene->mNumMeshes);
			

			VertexArray& vertexArray = params.mesh->_vertexArray;
			IndexArray& indexArray = params.mesh->_indexArray;

			vertexArray.addAttribute(sizeof(float), 3, VertexFormat::Position);
			vertexArray.addAttribute(sizeof(float), 4, VertexFormat::Color);
			vertexArray.addAttribute(sizeof(float), 2, VertexFormat::TexCoord);


			for (size_t i = 0; i < scene->mNumMeshes; ++i)
			{
				aiMesh* mesh = scene->mMeshes[i];
				
				Log("Mesh has %d channels", mesh->GetNumUVChannels());

				// Extract faces
				indexArray.indices.resize(mesh->mNumFaces * 3);
				for (std::size_t j = 0; j < mesh->mNumFaces; ++j)
				{
					indexArray.indices[j * 3 + 0] = mesh->mFaces[j].mIndices[0];
					indexArray.indices[j * 3 + 1] = mesh->mFaces[j].mIndices[1];
					indexArray.indices[j * 3 + 2] = mesh->mFaces[j].mIndices[2];
				}

				// Extract vertices
				vertexArray.allocateData(mesh->mNumVertices);

				struct vstruct
				{
					vec3 pv;
					vec4 cv;
					vec2 uv;
				};

				vstruct* vv = reinterpret_cast<vstruct*>(&vertexArray._data[0]);

				for (std::size_t j = 0; j < mesh->mNumVertices; ++j)
				{
					vec3 v(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z);
					vec4 cv(1.f, 1.f, 1.f, 1.f);

					aiVector3D* uvList = mesh->mTextureCoords[0];
					if (uvList)
					{
						//Log("Found tex coord channel 0");
						//Log("uv : %f %f", mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y);

						aiVector3D texCoord0 = *(uvList + j);
						//Log("pTex.x %f", texCoord0.x);
					}

					vv[j].pv = v;
					vv[j].cv = cv;
					vv[j].uv = vec2(uvList[j].x, 1.f - uvList[j].y);

				}
				
			}

			Log("Done loading");
		}
		else
		{
			Log("Failed load!");
		}

		return ModelLoaderResult(); 
	}

	/// Check if the loader supports this format for reading
	virtual bool supportsFormat(const String& extension)
	{ 
		return extension == "obj" || extension == "3ds";
	}
};

#endif // AssimpModelLoader_h__
