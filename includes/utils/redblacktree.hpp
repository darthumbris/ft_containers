#ifndef REDBLACKTREE_HPP
# define REDBLACKTREE_HPP

# include "node.hpp"

namespace ft
{
	template<class T, class Allocator, class Compare>
	class redblacktree
	{
		public:
			typedef T													value_type;
			typedef Allocator											allocator_type;
			typedef typename ft::node<value_type>						node;
			typedef	unsigned long										size_type;
			typedef typename Allocator::template rebind<node>::other	node_allocator_type;

		private:
			node*				_root;
			allocator_type		_alloc;
			node_allocator_type	_node_alloc;
			size_type			_size;
			Compare				_comp;

		public: // Member functions
			redblacktree() : _root(NULL), _alloc(NULL), _node_alloc(NULL), _size(0), _comp() {}
			~redblacktree() {}

			redblacktree&	operator=(const redblacktree& other)
			{
				_root = other._root;
				_alloc = other._alloc;
				_node_alloc = other._node_alloc;
				_size = other._size;
				_comp = other._comp;
				return *this;
			}

			const node*	getRoot() const (return _root;)
			
			// Capacity
			size_type	size() const {return _size;}

			// Modifiers
			bool	insert(value_type value) {return insertLeaf(_root, value);}
			void	clear() //eraseTree
			{
				eraseTree()
				_root = NULL;
				_size = 0;
			}
			void	erase(const value_type& value) {eraseNode(value, _root);} //erase single node in tree
			void	swap();

			// Lookup
			node* find(node* root, T value)
			{
				if (root == NULL || root->data == value)
					return root;
				if (_comp(value, *(root->data)))
					return find(root->right, key);
				return find(root->left, key);
			}
			node* findSmallest();
			node* findLargest();

		private: // Member functions

			// Insertions
			node*	newLeaf(node* root, value_type& value)
			{
				node* new_node = _node_alloc.allocate(1);
				_node_alloc.construct(new_node, node(root));
				new_node->data = _alloc.allocate(1);
				_alloc.construct(new_node->data, value);
				_size++;
				return new_node;
			}

			bool	insertLeaf(node* root, value_type& value)
			{
				if (_root == NULL)
				{
					_root = newLeaf(NULL, value);
					_root->colour = BLACK;
				}
				if (_comp(value, *(root->data)))
				{
					if (root->left == NULL)
					{
						root->left = newLeaf(root, value);
						recolourInsert(root->left);
					}
					else
						return insert(root->left, value);
				}
				else if (_comp(*(root->data), value))
				{
					if (root->right == NULL)
					{
						root->right = newLeaf(root, value);
						recolourInsert(root->right);
					}
					else
						return insert(root->right, value);
				}
				else
					return false
				return true;
			}

			// Deletions
			void	eraseNode(const value_type& value, node* parent) //done
			{
				if (!_root)
					return ;
				if (isEqual(value, *(parent->data)))
					eraseMatch(NULL, _root);
				else
				{
					if (_comp(*(parent->data), value) && parent->right)
					{
						if (isEqual(parent->right->data, value))
							eraseMatch(parent, parent->right);
						else
							eraseNode(value, parent->right);
					}
					else if (_comp(value, *(parent->data)) && parent->left)
					{
						if (isEqual(parent->left->data, value))
							eraseMatch(parent, parent->left);
						else
							eraseNode(value, parent->left);
					}
				}
			}

			void	eraseMatch(node *parent, node *remov) //done
			{
				bool	node_is_nil = false;
				node*	node_to_move = remov;
				node*	nil_node = NULL;
				colour	erase_colour = remov->colour;

				switch (countChildren(remov))
				{
					case 0: // 0 children
						nil_node = remov;
						node_is_nil = true;
						break;
					case 1: // 1 child
						if (remov->right != NULL)
							node_to_move = remov->right;
						else
							node_to_move = remov->left;
						updateParentChild(parent, remove, node_to_move);
						node_to_move->parent = remov->parent;
						removeNode(remov);
						break;
					case 2: // 2 children
						node* smallestright = findSmallest(remov->right);
						if (smallestright->right)
							node_to_move = smallestright->right;
						else
						{
							node_is_nil = true;
							value_type nil_data = value_type();
							nil_node = newLeaf(NULL, nil_data);
							nil_node->colour = BLACK;
							updateParentChild(smallestright->parent, smallestright, nil_node);
							node_to_move = nil_node;
						}			
						if (smallestright->parent == remov)
						{
							updateParentChild(remov->parent, remov, smallestright);
							smallestright->left = remov->left;
							remov->left->parent = smallestright;
							if (!smallestright->right)
							{
								smallestright->right = nil_node;
								nil_node->parent = smallestright;
							}
						}
						else
						{
							if (smallestright->right)
							{
								smallestright->right->parent = smallestright->parent;
								smallestright->parent->left = smallestright->right;
							}
							updateParentChild(remov->parent, remov, smallestright);
							smallestright->left = remov->left;
							remov->left->parent = smallestright;
							smallestright->right = remov->right;
							remov->right->parent = smallestright;
						}
						erase_colour = smallestright->colour;
						smallestright->colour = remov->colour;
						removeNode(remov);
						break;
				}
				if (erase_colour == BLACK)
					recolourErase(node_to_move);
				if (nil_node)
				{
					updateParentChild(nil_node->parent, nil_node, NULL);
					removeNode(nil_node);
				}
			}

			void	removeNode(node *remov) //done
			{
				_alloc.destroy(remov->data);
				_alloc.deallocate(remov->data, 1);
				_node_alloc.destroy(remov);
				_node_alloc.deallocate(remov->data, 1);
				_size--;
			}

			void	eraseTree(node* root) //done
			{
				if (root)
				{
					if (root->left)
						eraseTree(root->left);
					if (root->right)
						eraseTree(root->right);
					_alloc.destroy(root->data);
					_alloc.deallocate(root->data, 1);
					_node_alloc.destroy(root);
					_node_alloc.deallocate(root->data, 1);
				}
			}

			// Reordering
			void	updateParentChild(node* parent, node* old_child, node* new_child) //done
			{
				if (parent == NULL)
					_root = new_child;
				else if (parent->right == old_child)
					parent->right = new_child;
				else if (parent->left == old_child)
					parent->left = new_child;
				if (new_child)
					new_child->parent = parent;
			}

			void	recolourInsert(node* root)
			{
				
			}

			void	recolourErase(node* root)
			{

			}

			void	rotateLeft(node* root)
			{

			}

			void	rotateRight(node* root)
			{

			}

			

			// Lookup
			isEqual(const value_type& a, const value_type& b) //done
			{
				if (_comp(a, b))
					return false;
				else if (_comp(b, a))
					return false;
				return true;
			}

			size_type	countChildren(node *root)
			{
				if (root->left == NULL && root->right == NULL)
					return 0;
				else if (root->left == NULL || root->right == NULL)
					return 1;
				return 2;
			}

			node*	getUncle(node* parent)
			{

			}

			node* getSibling(node* root)
			{

			}
	};
}

#endif
