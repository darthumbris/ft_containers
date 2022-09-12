#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

// # include "iterator_traits.hpp"
# include "utils/Tree.hpp"

namespace ft
{
	template <class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&, class Category = std::bidirectional_iterator_tag>
	class bidirectional_iterator
	{

	public: // typedefs
		typedef T												value_type;
		typedef Category										iterator_category;
		typedef Distance										difference_type;
		typedef Pointer											pointer;
		typedef Reference										reference;
		typedef bidirectional_iterator<T, const T*, const T&>	const_iterator_type;
		typedef ft::node<value_type>							node;

	private: // Variables
		node* 								_ptr;
		const	ft::Tree<value_type>*		_tree;

	private:

		node* previous(node *ptr)
		{
			if(ptr == NULL)	//end node
				return _tree->findLargest();
			if (ptr->left)
			{
				ptr = ptr->left;
				while (ptr->right)
					ptr = ptr->right;
			}
			else
			{
				node* tmp = ptr;
				ptr = ptr->parent;
				while (ptr && ptr->right != tmp)
				{
					tmp = ptr;
					ptr = ptr->parent;
				}
			}
			return ptr;
		}

		node* next(node *ptr)
		{
			if(ptr == NULL)	//rend node
				return _tree->findSmallest();
			if (ptr->right)
			{
				ptr = ptr->right;
				while (ptr->left)
					ptr = ptr->left;
			}
			else
			{
				node* tmp = ptr;
				ptr = ptr->parent;
				while (ptr && ptr->left != tmp)
				{
					tmp = ptr;
					ptr = ptr->parent;
				}
			}
			return ptr;
		}

	public: // Member Functions
		bidirectional_iterator() : _ptr(NULL), _tree(NULL) {} //default
		bidirectional_iterator(node* ptr) : _ptr(ptr), _tree(NULL) {} //default
		bidirectional_iterator(node* ptr, const Tree<value_type>* tree) : _ptr(ptr), _tree(tree) {} 
		bidirectional_iterator(const bidirectional_iterator& src) : _ptr(src._ptr), _tree(src._tree) {} //copy

		~bidirectional_iterator() {}

		operator const_iterator_type() const {return const_iterator_type(_ptr, _tree);}

		bidirectional_iterator&		operator=(const bidirectional_iterator& rhs) {_ptr = rhs._ptr; _tree = rhs._tree; return *this;}

		//friend keyword for a couple of these functions because they are nonmember overloads
		friend bool					operator==(const bidirectional_iterator& lhs, const bidirectional_iterator& rhs) {return lhs.base() == rhs.base();}
		friend bool					operator!=(const bidirectional_iterator& lhs, const bidirectional_iterator& rhs) {return !(lhs.base() == rhs.base());}


		bidirectional_iterator&		operator++(void) {_ptr = next(_ptr); return *this;}
		bidirectional_iterator		operator++(int)	{bidirectional_iterator	copy(*this); _ptr = next(_ptr); return copy;}
		bidirectional_iterator&		operator--(void) {_ptr = previous(_ptr); return *this;}
		bidirectional_iterator		operator--(int) {bidirectional_iterator	copy(*this); _ptr = previous(_ptr); return copy;}

		reference					operator*() const {return *(_ptr->data);}
		reference					operator*() {return *(_ptr->data);}

		pointer						operator->() const {return _ptr->data;}
		pointer						operator->() {return _ptr->data;}

		node*						base() const {return _ptr;}

	};
}

#endif