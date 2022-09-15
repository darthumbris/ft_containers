#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

namespace ft
{
	template <class T, class Compare, class Alloc, class Pointer = T*, class Reference = T&>
	class bidirectional_iterator
	{

	public: // typedefs
		typedef T													value_type;
		typedef std::bidirectional_iterator_tag						iterator_category;
		typedef long												difference_type;
		typedef Pointer												pointer;
		typedef Reference											reference;
		typedef bidirectional_iterator<T, Compare, Alloc, const T*, const T&>	const_iterator_type;

	private: // Variables
		pointer 												_ptr;
		const	redblacktree<value_type, Alloc, Compare>*		_tree;

	public: // Member Functions

		bidirectional_iterator() : _ptr(NULL) {} //default
		bidirectional_iterator(pointer ptr, const redblacktree<value_type, Alloc, Compare>* rbtree = NULL) : _ptr(ptr), _tree(rbtree) {} 
		bidirectional_iterator(const bidirectional_iterator& src) : _ptr(src._ptr), _tree(src._tree) {} //copy
		~bidirectional_iterator() {}

		operator const_iterator_type() const {return const_iterator_type(_ptr, _tree);}

		bidirectional_iterator&		operator=(const bidirectional_iterator& rhs)
		{
			_ptr = rhs._ptr;
			_tree = rhs._tree;
			return *this;
		}

		//friend keyword for a couple of these functions because they are nonmember overloads
		friend bool					operator==(const bidirectional_iterator& lhs, const bidirectional_iterator& rhs) {return lhs._ptr == rhs._ptr;}
		friend bool					operator!=(const bidirectional_iterator& lhs, const bidirectional_iterator& rhs) {return !(lhs._ptr == rhs._ptr);}

		bidirectional_iterator&		operator++(void)
		{
			ft::node<value_type>	*node = _tree->find(*_ptr);
			if (node)
			{
				ft::node<value_type>	*successor = _tree->lower_bound(*_ptr);
				if (successor)
					_ptr = successor->data;
				else
					_ptr =  NULL;
			}
			return *this;
		}
		bidirectional_iterator		operator++(int)	{bidirectional_iterator	copy(*this); ++(*this); return copy;}
		bidirectional_iterator&		operator--(void)
		{
			ft::node<value_type>	*node = NULL;
			if (!_ptr)
			{
				node = _tree->findLargest();
				if (node)
					_ptr =  node->data;
				return *this;
			}
			node = _tree->find(*_ptr);
			if (node)
			{
				ft::node<value_type>	*pred = _tree->upper_bound(*_ptr);
				if (pred)
					_ptr =  pred->data;
				else
					_ptr =  NULL;
			}
			return *this;
		}
		bidirectional_iterator		operator--(int) {bidirectional_iterator	copy(*this); --(*this); return copy;}

		reference					operator*() const {return *_ptr;}
		reference					operator*() {return *_ptr;}

		pointer						operator->() const {return _ptr;}
		pointer						operator->() {return _ptr;}

	};
}

#endif