#ifndef TREE_HPP
# define TREE_HPP

# include "node.hpp"

namespace ft
{
	template <class T>
	class Tree
	{
		public: //typedefs

			typedef T						value_type;
			typedef unsigned long			size_type;
			typedef ft::node<value_type>	node;

		public: //member functions

			virtual	~Tree() {}
			virtual node*	findSmallest() const = 0;
			virtual node*	findLargest() const = 0;
	};
}

#endif
