#ifndef ForgeWorldRegion_h__
#define ForgeWorldRegion_h__

#include "Platform.h"
#include "Vectors.h"

//#include "SceneGraph.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Forge
	\class ForgeCell

	A forge cell is a big container of a region of the world. It is meant to be loaded and unloaded at demand, for a map without loadings.
*/
class PARABOLA_API ForgeCell{
public:
	ForgeCell();
	
private:
	//SceneGraph m_graph; ///< The scene contained in this cell

	Vec2f m_basePosition; ///< The base position of the cell. Can be invalid when the cell is too far off bounds.
	Vec2f m_size; ///< The size of this cell

	ForgeCell* m_left; ///< The cell at the left
	ForgeCell* m_right; ///< The cell at the right
	ForgeCell* m_up; ///< The cell at the top
	ForgeCell* m_down; ///< The cell at the bottom
};

PARABOLA_NAMESPACE_END
#endif // ForgeWorldRegion_h__
