#ifndef ForgeContext_h__
#define ForgeContext_h__

#include "Platform.h"
#include "Vectors.h"

namespace Forge
{
	/// FPoint is a global coordinate
	typedef struct 
	{
		bool isLocal; ///< If true, cell id is ignored and this is a local coordinate
		Vec2<Int64> cell; ///< CELL ID
		float x; ///< Horizontal coordinate within the cell
		float y; ///< Vertical coordinate within the cell
	}FPoint;
};

#endif // ForgeContext_h__
