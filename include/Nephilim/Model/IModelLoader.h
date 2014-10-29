#ifndef NephilimIModelLoader_h__
#define NephilimIModelLoader_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Model/Mesh.h>

#include <vector>

NEPHILIM_NS_BEGIN


/**
	\class IModelLoader
	\brief Interface for implementing model loaders

	This is the base class for implementing different model loaders.
	Usually, different loaders will be implemented as plugins,
	which have a C API to do some basic operations. This can be enough,
	but its good if all model loaders follow a protocol so they can
	be compiled in the engine or app directly and be able to be registered 
	within the content manager, to load their formats dynamically.
*/
class NEPHILIM_API IModelLoader
{
public:
	/// Interface: asks the loader to retrieve its set of mesh data to our storage container
	virtual bool loadStaticModel(std::vector<Mesh>& storage){}
};

NEPHILIM_NS_END
#endif // NephilimIModelLoader_h__
