/*
	Let There Be Light
	Copyright (C) 2012 Eric Laukien

	This software is provided 'as-is', without any express or implied
	warranty.  In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1. The origin of this software must not be misrepresented; you must not
		claim that you wrote the original software. If you use this software
		in a product, an acknowledgment in the product documentation would be
		appreciated but is not required.
	2. Altered source versions must be plainly marked as such, and must not be
		misrepresented as being the original software.
	3. This notice may not be removed or altered from any source distribution.
*/

#ifndef QUADTREEOCCUPANT_H
#define QUADTREEOCCUPANT_H

#include "Constructs.h"

using namespace ltbl;

namespace qdt
{
	class QuadTreeNode;
	class QuadTree;

	class QuadTreeOccupant
	{
	private:
		QuadTreeNode* pQuadTreeNode;
		QuadTree* pQuadTree;

	public:
		AABB aabb;

		QuadTreeOccupant();
		virtual ~QuadTreeOccupant();

		// Call this whenever the AABB is modified or else stuff will break!
		void UpdateTreeStatus();
		void RemoveFromTree();

		friend class QuadTreeNode;
		friend class QuadTree;
	};
}

#endif