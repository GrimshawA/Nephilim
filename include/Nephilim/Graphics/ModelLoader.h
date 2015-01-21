#ifndef NephilimIModelLoader_h__
#define NephilimIModelLoader_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>

NEPHILIM_NS_BEGIN

class StaticMesh;

/**
	\struct ModelLoaderParams
	\brief Passed into the loaders to give them instructions of how to import
*/
struct ModelLoaderParams
{
	StaticMesh* mesh;
	String filename; ///< The filename to be loaded in the operation
};

/**
	\struct ModelLoaderResult
	\brief Return of the loading operation, to make sure all went well
*/
struct ModelLoaderResult
{

};

/**
	\class ModelLoader
	\brief Interface for implementing third party model loaders

	This is the base class for implementing different model loaders.
	Usually, different loaders will be implemented as plugins,
	which have a C API to do some basic operations. This can be enough,
	but its good if all model loaders follow a protocol so they can
	be compiled in the engine or app directly and be able to be registered 
	within the content manager, to load their formats dynamically.

	This class works by attaching implementations to the content manager, so it can understand new formats.
*/
class NEPHILIM_API ModelLoader
{
public:
	/// Interface: asks the loader to retrieve its set of mesh data to our storage container
	virtual ModelLoaderResult load(const ModelLoaderParams& params){ return ModelLoaderResult(); }

	/// Check if the loader supports this format for reading
	virtual bool supportsFormat(const String& extension){ return false; }
};

NEPHILIM_NS_END
#endif // NephilimIModelLoader_h__
