#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

# include "../utils/redblacktree.hpp"

namespace ft
{
	template <class T, class Pointer = T*, class Reference = T&>
	class bidirectional_iterator
	{

	public: // typedefs

		typedef T													value_type;
		typedef std::bidirectional_iterator_tag						iterator_category;
		typedef long												difference_type;
		typedef Pointer												pointer;
		typedef Reference											reference;
		typedef bidirectional_iterator<T, const T*, const T&>		const_iterator_type;
		typedef ft::node<value_type>								node;

	private: // Variables

		node* 									_ptr;
		const	ft::tree<value_type>*			_tree;

	public: // Member Functions

		bidirectional_iterator() : _ptr(NULL) {} //default
		bidirectional_iterator(node* ptr, const ft::tree<value_type>* tree = NULL) : _ptr(ptr), _tree(tree) {} 
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
		friend bool				operator==(const bidirectional_iterator& lhs, const bidirectional_iterator& rhs) {return lhs._ptr == rhs._ptr;}
		friend bool				operator!=(const bidirectional_iterator& lhs, const bidirectional_iterator& rhs) {return !(lhs._ptr == rhs._ptr);}

		bidirectional_iterator&	operator++(void)
		{
			// node*	node = _ptr;
			if (_ptr == NULL)
			{
				_ptr = _tree->findSmallest();
				return *this;
			}
			if (_ptr->right)
			{
				_ptr = _ptr->right;
				while (_ptr->left)
					_ptr = _ptr->left;
			}
			else
			{
				ft::node<value_type>* temp = _ptr;
				_ptr = _ptr->parent;
				while (_ptr && _ptr->left != temp)
				{
					temp = _ptr;
					_ptr = _ptr->parent;
				}
			}
			return *this;
		}
		bidirectional_iterator	operator++(int)	{bidirectional_iterator	copy(*this); ++(*this); return copy;}
		bidirectional_iterator&	operator--(void)
		{
			node*	node = _ptr;
			if (_ptr == NULL)
			{
				_ptr = _tree->findLargest();
				return *this;
			}
			if (node->left)
			{
				node = node->left;
				while (node->right)
					node = node->right;
			}
			else
			{
				ft::node<value_type>* temp = node;
				node = node->parent;
				while (node && node->right != temp)
				{
					temp = node;
					node = node->parent;
				}
			}
			_ptr = node;
			return *this;
		}
		bidirectional_iterator	operator--(int) {bidirectional_iterator	copy(*this); --(*this); return copy;}

		reference				operator*() const {return *_ptr->data;}
		reference				operator*() {return *_ptr->data;}

		pointer					operator->() const {return _ptr->data;}
		pointer					operator->() {return _ptr->data;}
	};
}
#endif
