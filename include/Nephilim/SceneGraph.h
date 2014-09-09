#ifndef NephilimSceneGraph_h__
#define NephilimSceneGraph_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

/**
	\ingroup Core
	\class SceneGraph2D
	\brief Base class for all 2D scene management structures
*/	
class NEPHILIM_API SceneGraph2D
{
public:

};


/**
	\ingroup Core
	\class SceneGraph3D
	\brief Base class for scene management structures for 3D worlds
*/
class NEPHILIM_API SceneGraph3D
{
public:

	class Node
	{
	public:
		
	};

	SceneGraph3D()
	{
		m_root = new Node();
	}


	Node* m_root;
};

NEPHILIM_NS_END
#endif // NephilimSceneGraph_h__
