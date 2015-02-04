#include <Nephilim/Model/ModelLoader.h>
using namespace nx;

// The actual worker
#include "AssimpModelLoader.h"

extern "C"
{

ModelLoader __declspec(dllexport) *instanceLoader()
{
	return new AssimpModelLoader;
}

}
