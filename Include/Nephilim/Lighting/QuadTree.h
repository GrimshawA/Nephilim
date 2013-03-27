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

#ifndef QUADTREE_H
#define QUADTREE_H

#include "QuadTreeNode.h"
#include "QuadTreeOccupant.h"

#include <unordered_set>

using namespace ltbl;

namespace qdt
{
	class QuadTree
	{
	private:
		std::unordered_set<QuadTreeOccupant*> outsideRoot;

		QuadTreeNode* rootNode;

	public:
		QuadTree(const AABB &startRegion);
		~QuadTree();

		void AddOccupant(QuadTreeOccupant* pOc);
		void ClearTree(const AABB &newStartRegion);

		void Query(const AABB &queryRegion, std::vector<QuadTreeOccupant*> &queryResult);
		void QueryToDepth(const AABB &queryRegion, std::vector<QuadTreeOccupant*> &queryResult, int depth);

		unsigned int GetNumOccupants();

		AABB GetRootAABB();

		void DebugRender();

		friend class QuadTreeNode;
		friend class QuadTreeOccupant;
	};
}

#endif