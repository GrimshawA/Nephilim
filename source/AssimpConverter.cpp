#include <Nephilim/AssimpConverter.h>
#include <Nephilim/Geometry.h>
#include <Nephilim/Logger.h>

#ifndef NEPHILIM_NOASSIMP

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

NEPHILIM_NS_BEGIN

AssimpImport::AssimpImport()
{
	m_importer = new Assimp::Importer();
}

AssimpImport::~AssimpImport()
{
	delete m_importer;
}

bool AssimpImport::load(const String& filename)
{

	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll 
	// propably to request more postprocessing than we do in this example.
	const aiScene* scene = m_importer->ReadFile( filename, 
		aiProcess_CalcTangentSpace       | 
		aiProcess_Triangulate            |
		aiProcess_JoinIdenticalVertices  |
		aiProcess_SortByPType);

	

	// If the import failed, report it
	if( !scene)
	{
		Log("AssimImport: Failed to load '%s'. Reason: %s", filename.c_str(), m_importer->GetErrorString());
		return false;
	}
	else
	{
		Log("AssimpImport: Loaded '%s'", filename.c_str());
	}

}

/// Returns the scene containing all data for the loaded asset
const aiScene* AssimpImport::getScene()
{
	return m_importer->GetScene();
}

AssimpGeometry::AssimpGeometry(GeometryData& data, AssimpImport& importer)
{
	const aiScene& scene = *importer.getScene();

	Log("Meshes: %s", scene.HasMeshes() ? "yes" : "no");
	Log("Meshes: %d", scene.mNumMeshes);


	for(int i = 0; i < scene.mNumMeshes; ++i)
	{
		aiMesh* mesh = scene.mMeshes[i];
		Log("Mesh vertex count: %d", mesh->mNumVertices);
		//Log("Mesh texture0 count: %d", mesh->m);
		Log("Expected vertex count: %d", mesh->mNumFaces * 3);


		for(int j = 0; j < mesh->mNumFaces; ++j)
		{
			aiFace face = mesh->mFaces[j];
			for(int f = 0; f < face.mNumIndices; ++f)
			{
				// Triangle
				data.m_vertices.push_back(vec3(mesh->mVertices[face.mIndices[f]].x, mesh->mVertices[face.mIndices[f]].y, mesh->mVertices[face.mIndices[f]].z));
				if(mesh->HasTextureCoords(0))
				{
					vec2 uv = vec2(mesh->mTextureCoords[0][face.mIndices[f]].x, mesh->mTextureCoords[0][face.mIndices[f]].y);
					data.m_texCoords.push_back(uv);
				}			
				if(mesh->HasNormals())
				{
					vec3 normal = vec3(mesh->mNormals[face.mIndices[f]].x, mesh->mNormals[face.mIndices[f]].y, mesh->mNormals[face.mIndices[f]].z);
					data.m_normals.push_back(normal);
				}
			}
		}
	}

	Log("Mesh vertices: %d", data.m_vertices.size());
}


NEPHILIM_NS_END
#endif