#ifndef PARABOLA_TREE_H
#define PARABOLA_TREE_H

#include "Platform.h"
#include "Strings.h"

PARABOLA_NAMESPACE_BEGIN

	/**
		\ingroup Foundation
		\class Tree
		\brief A tree structure utility
	*/
	class PARABOLA_API Tree{
	public:
		
		/// Get the name of the node
		String name();

	private:
		String node_name;
	};

	/**
		\ingroup Foundation
		\class TreeContainerNode
		\brief Custom node to hold an object of type T
	*/
	template<class T>
	class PARABOLA_API TreeContainerNode : Tree{
	public:
		T value;
	};

PARABOLA_NAMESPACE_END
#endif