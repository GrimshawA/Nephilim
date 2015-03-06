#include <Nephilim/World/AVoxelVolumeComponent.h>

NEPHILIM_NS_BEGIN

/// Resize the voxel chunk to a new size
void AVoxelVolumeComponent::resize(int w, int h, int d)
{
	width = w;
	height = h;
	depth = d;

	voxelData.resize(w * h * d);

	for (auto& v : voxelData)
	{
		v.id = 0;
	}
}

/// Convert a 1D index into the voxel array to a 3D coordinate of it in local coordinates
Vector3<int> AVoxelVolumeComponent::translate1Dto3D(std::size_t index)
{
	Vector3<int> v;
	v.x = index % width;
	v.y = (index / width) % height;
	v.z = ((index / width) / height) % depth;
	return v;
}

/// Number of voxels in the 3D grid
std::size_t AVoxelVolumeComponent::size()
{
	return voxelData.size();
}

NEPHILIM_NS_END