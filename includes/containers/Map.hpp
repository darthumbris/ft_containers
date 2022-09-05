#ifndef MAP_HPP
# define MAP_HPP


# include <memory> //for std::allocator
# include "iterators/reverse_iterator.hpp" //for all the iterator stuff
# include "utils/utils.hpp" //for enable if and other util functions
# include <algorithm> //for std::min

namespace ft
{
	template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T>>>
	class map
	{

	public: //typedefs

		typedef Key										key_type;
		typedef T										mapped_type;
		typedef ft::pair<const Key, T>					value_type;
		typedef unsigned long							size_type;
		typedef long									difference_type;
		typedef Compare									key_compare;
		typedef Allocator								allocator_type;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;
		typedef ft::iterator<pointer>					iterator;
		typedef ft::iterator<const_pointer>				const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	private:
		value_type*												_array;
		allocator_type											_alloc;
		size_type												_alloc_size;
		size_type												_size;

		class value_compare
		{
			friend class map;
			protected:
				key_compare	_comp;
				value_compare (key_compare c) : _comp(c) {}
			public:
				typedef bool		result_type;
				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;
			public:
				bool operator() (const value_type& x, const value_type& y) const {return _comp(x.first, y.first);}
		};

	public:

		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) // empty
		{

		}

		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) // range
		{

		}

	   map (const map& x) // copy
	   {
		
	   }
		
	};
}

#endif
