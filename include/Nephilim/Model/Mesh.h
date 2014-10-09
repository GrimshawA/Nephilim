#ifndef NephilimMesh_h__
#define NephilimMesh_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

/**
	\class Mesh
	\brief Generic geometry class

	This is the class used by the engine to actually store meshes
	in memory. Each mesh is a collection of triangles that use
	a single material (or layered material).

	Some 3D models will contain a single mesh, while others
	may be a complex collection of meshes to render its individual parts.
*/
class NEPHILIM_API Mesh
{
public:

};

NEPHILIM_NS_END
#endif // NephilimMesh_h__
