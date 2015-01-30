#ifndef NephilimWorldAVoxelVolumeComponent_h__
#define NephilimWorldAVoxelVolumeComponent_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/Components/ASceneComponent.h>

#include <Nephilim/Foundation/Vector.h>

#include <stdint.h>
#include <vector>

NEPHILIM_NS_BEGIN

/**
	\class AVoxelVolumeComponent
	\brief Places a chunk of voxels into the world
*/
class NEPHILIM_API AVoxelVolumeComponent : public ASceneComponent
{
public:
	
	struct Voxel
	{
		int id;
	};

	/// The actual array of data
	std::vector<Voxel> voxelData;

	/// Dimensions of the voxel chunk
	int32_t width, height, depth;

	/// Size of each voxel
	int32_t tile_size;

public:

	/// Resize the voxel chunk to a new size
	void resize(int w, int h, int d);

	/// Convert a 1D index into the voxel array to a 3D coordinate of it in local coordinates
	Vec3i translate1Dto3D(std::size_t index);

	/// Number of voxels in the 3D grid
	std::size_t size();
};

NEPHILIM_NS_END
#endif // NephilimWorldAVoxelVolumeComponent_h__
