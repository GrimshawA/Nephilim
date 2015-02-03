#ifndef NephilimGeometryFormat_h__
#define NephilimGeometryFormat_h__

#include <Nephilim/Platform.h>

#include <stdint.h>

NEPHILIM_NS_BEGIN

struct FAssetHeader
{
	uint32_t id; /// The asset type identifier
	uint32_t version; /// The asset format version
};

struct FGeomFmtHeader
{
	uint32_t numObjects; /// amount of meshes in the file
	uint32_t flags;      /// Global flags for this asset
};

struct FGeomObjHeader
{
	char name[64];
	uint8_t interleaved; /// Is the data interleaved or in individual segments?
	uint8_t objectType; /// What kind of object this is, skeletal, static or something else
};

/**
	\class GeomFmt
	\brief Loader for the native geometry files (NGF)

	This class is exclusively a loader, its sole responsibility is to get data
	into and from NGF files. This is used by other parts of the engine to get runtime data
	and then use it for rendering etc.
*/
class NEPHILIM_API GeomFmt
{
public:

};

NEPHILIM_NS_END
#endif // NephilimGeometryFormat_h__
