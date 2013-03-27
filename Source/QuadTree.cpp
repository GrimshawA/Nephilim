#ifndef MINIMAL_BUILD
#include "Nephilim/QuadTree.h"

PARABOLA_NAMESPACE_BEGIN
/// Create a yet empty quad tree
QuadTree::QuadTree(){

};

/// Returns the count of all nodes in the tree
int QuadTree::nodeCount(){
	return 0;
};

/// Returns the count of nodes that are not leafs.
/// Sector Node: any node that contains two child nodes,
/// being them leaf or sector too.
int QuadTree::sectorCount() {
	return 0;
};

/// Returns the count of nodes that are leafs.
/// Leaf Node: any node that contains drawables.
int QuadTree::leafCount(){
	return 0;
};

PARABOLA_NAMESPACE_END

	#endif