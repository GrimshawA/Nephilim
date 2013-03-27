#ifndef PARABOLA_QUADTREE_H
#define PARABOLA_QUADTREE_H

#include "Platform.h"

PARABOLA_NAMESPACE_BEGIN


/**
	\ingroup Graphics
	\class QuadTreeNode
	\brief Represents a node in a quad tree structure.

	All nodes are a QuadTreeNode, being them a root, 
	intermediate or a leaf node.
*/
class PARABOLA_API QuadTreeNode{
public:
	/// Creates an empty node
	QuadTreeNode();

private:
	QuadTreeNode *left, *right;
};


/**
	\ingroup Graphics
	\class QuadTree
	\brief Holds and interacts with a QuadTree structure

	A quad tree is a uneven binary tree, to put it simple.
	That means there is a tree that subdivides space, into
	smaller containers.

	This tree is able to adapt to new global sizes.
	If the root node stretches, all nodes will adapt.

	Lets say you have a world of width 1000, and ignore height for simplicity.
	Lets say you're drawable is a little dot, in a coordinate from 0 to 1000.

	When you render your objects, normally you would just draw all the dots.
	For optimizing, you are told to check if a dot is within the screen,
	before telling it to draw, to avoid unnecessary calls.

	That would still require you to check all objects in the scene,
	losing performance, possibly.

	This tree would divide that 1000 width space into two, then each of those two,
	in two more, and this recursively.

	Each subdivision would split as soon as there are more than N drawables in it.
	When splitting, those drawables would be assigned to the newly generated containers,
	according to position.

	This is great because it allows to skip all nodes outside the current camera, and potentially skipping plenty of verifications.

	It is also useful for locating objects faster than normal.
	Just like if you wish to know all objects within a box.

*/
class PARABOLA_API QuadTree{
public:
	/// Create a yet empty quad tree
	QuadTree();

	/// Returns the count of all nodes in the tree
	int nodeCount();

	/// Returns the count of nodes that are not leafs.
	/// Sector Node: any node that contains two child nodes,
	/// being them leaf or sector too.
	int sectorCount();

	/// Returns the count of nodes that are leafs.
	/// Leaf Node: any node that contains drawables.
	int leafCount();

private:
	QuadTreeNode root;
};

PARABOLA_NAMESPACE_END
#endif