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

#ifndef QUADTREENODE_H
#define QUADTREENODE_H

#include "QuadTreeOccupant.h"
#include <vector>
#include <unordered_set>

using namespace ltbl;

namespace qdt
{
	const unsigned int maximumOccupants = 3;
	const unsigned int minimumOccupants = 1;
	const float oversizedMultiplier = 1.2f;

	const unsigned int maxLevels = 20;

	class QuadTree;

	class QuadTreeNode
	{
	private:
		AABB region;
		Vec2f center;

		QuadTreeNode* pParentNode;
		QuadTree* pQuadTree;

		std::unordered_set<QuadTreeOccupant*> occupants;

		QuadTreeNode* children[2][2];
		bool hasChildren;

		unsigned int numOccupants;

		unsigned int level;

		void Partition();

		void DestroyChildren();

		void Merge();
		void GetOccupants(std::unordered_set<QuadTreeOccupant*> &upperOccupants, QuadTreeNode* newNode);
		void GetOccupants(std::vector<QuadTreeOccupant*> &queryResult);
		Point2i GetPossibleOccupantPos(QuadTreeOccupant* pOc);

	public:
		QuadTreeNode(const AABB &newRegion, unsigned int numLevels, QuadTreeNode* pParent = NULL, QuadTree* pContainer = NULL);
		~QuadTreeNode();

		void AddOccupant(QuadTreeOccupant* pOc);
		void Query(const AABB &queryRegion, std::vector<QuadTreeOccupant*> &queryResult);
		void QueryToDepth(const AABB &queryRegion, std::vector<QuadTreeOccupant*> &queryResult, int depth);

		void DebugRender();

		friend class QuadTreeNode;
		friend class QuadTreeOccupant;
		friend class QuadTree;
	};
}

#endif
