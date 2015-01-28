#include <Nephilim/World/CVoxelChunk.h>

NEPHILIM_NS_BEGIN

/// Resize the voxel chunk to a new size
void CVoxelChunk::resize(int w, int h, int d)
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
Vec3i CVoxelChunk::translate1Dto3D(std::size_t index)
{
	Vec3i v;
	v.x = index % width;
	v.y = (index / width) % height;
	v.z = ((index / width) / height) % depth;
	return v;
}

/// Number of voxels in the 3D grid
std::size_t CVoxelChunk::size()
{
	return voxelData.size();
}

NEPHILIM_NS_END