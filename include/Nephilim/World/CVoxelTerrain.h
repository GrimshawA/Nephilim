#ifndef NephilimRazerComponentVoxelTerrain_h__
#define NephilimRazerComponentVoxelTerrain_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/Component.h>

#include <stdint.h>

NEPHILIM_NS_BEGIN

/**
	\class CVoxelTerrain
	\brief A chunk of voxels to make tile-based 3D terrains

*/
class NEPHILIM_API CVoxelTerrain : public Component
{
public:
	
	struct Voxel
	{
		int id;
	};

	/// Dimensions of the voxel chunk
	int32_t width, height, depth;

	/// Size of each voxel
	int32_t tile_size;
};

NEPHILIM_NS_END
#endif // NephilimRazerComponentVoxelTerrain_h__
