#ifndef AssimpConverter_h__
#define AssimpConverter_h__

#include "Platform.h"
#include "Strings.h"

struct aiScene;
namespace Assimp
{
	class Importer;
}

NEPHILIM_NS_BEGIN

class GeometryData;

/**
	\ingroup Core
	\class AssimpImport
	\brief Imports a model using assimp to an intermediate format
*/
class NEPHILIM_API AssimpImport
{
public:
	AssimpImport();

	~AssimpImport();

	bool load(const String& filename);

	/// Returns the scene containing all data for the loaded asset
	const aiScene* getScene();

private:
	Assimp::Importer* m_importer;
};

/**
	\ingroup Core
	\class AssimpGeometry
	\brief Transfers data from aiScene to GeometryData
*/
class NEPHILIM_API AssimpGeometry
{
public:
	AssimpGeometry(GeometryData& data, AssimpImport& importer);
};

NEPHILIM_NS_END

#endif // AssimpConverter_h__
