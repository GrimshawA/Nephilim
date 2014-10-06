// The actual worker
#include "AssimpModelLoader.h"

// Engine interfaces
#include <Nephilim/VertexArray.h>
#include <Nephilim/IndexArray.h>
using namespace nx;

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include <stdio.h>

extern "C"
{
	void __declspec(dllexport) dll_hello()
	{
		printf("Hello world\n\n\n");
	}

	void __declspec(dllexport) sup()
	{

	}

void __declspec(dllexport) loadModel(const char* filename, VertexArray& vertexArray, IndexArray& indexArray)
{

	AssimpModelLoader loader;
	loader.open(filename,vertexArray, indexArray);
}

}
