#ifndef ForgeLayer_h__
#define ForgeLayer_h__

#include "Platform.h"
#include "Strings.h"
#include "Renderer.h"
#include "ForgeNode.h"

#include <list>

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Forge
	\class ForgeWorldLayer
	\brief Subdividision of the world by layers
*/
class PARABOLA_API ForgeWorldLayer{
public:
	/// Constructs the layer
	ForgeWorldLayer();

	/// Construct directly with a name
	ForgeWorldLayer(const String &name);

	/// Attach a node as a child
	void attachNode(ForgeWorldNode* node);

	/// Destroy a child node
	void destroyNode(ForgeWorldNode* node);

	/// Get the name of this layer
	String getName();

	/// Render the layer of the world
	void draw(Renderer* renderer);

private:
	/// Hidden flag: sets visibility of this layer.
	bool m_hidden;
	/// Layer name
	String m_name;

	std::list<ForgeWorldNode*> m_nodes;
};

PARABOLA_NAMESPACE_END
#endif // ForgeLayer_h__
