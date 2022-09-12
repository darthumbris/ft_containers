#ifndef REDBLACKTREE_HPP
# define REDBLACKTREE_HPP

# include "node.hpp"
# include "Tree.hpp"

/*
 * notes: 
 * - https://www.codesdope.com/course/data-structures-red-black-trees-insertion/
 * - https://www.geeksforgeeks.org/red-black-tree-set-2-insert/
 * - https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/
 * - https://www.youtube.com/watch?v=_c30ot0Kcis&list=PLwyTr3n29dXRDviK2r4fcF_9lr8pL1tlr
*/

namespace ft
{
	template<class T, class Allocator, class Compare>
	class redblacktree : public Tree<T>
	{
	public: //typedefs

		// typedef Compare												value_compare;
		typedef Allocator											allocator_type;
		typedef	unsigned long										size_type;
		typedef long												difference_type;
		typedef Tree<T>												Tree;
		typedef typename Tree::value_type							value_type;
		typedef typename Tree::node									node;
		typedef typename Allocator::template rebind<node>::other	node_allocator_type;

	private:
		node*				_root; //root of the tree
		allocator_type		_alloc; //alloc for the data of the nodes
		node_allocator_type	_node_alloc; //alloc for the nodes itself
		size_type			_size; //size of the tree
		Compare				_comp; //Compare class used to compare values

	public:

		redblacktree(allocator_type alloc, Compare compare) : _root(NULL), _alloc(alloc), _size(0), _comp(compare) {}
		redblacktree() : _root(NULL), _alloc(), _size(0), _comp() {}
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

		const node*		root() const {return _root;}
		
		// Capacity
		size_type	size() const {return _size;}
		size_type	max_size() const {return std::min<size_type>(_node_alloc.max_size(), std::numeric_limits<difference_type>::max());}

		// Modifiers
		bool	insert(value_type value) {return insertLeaf(_root, value);}
		void	clear() //eraseTree
		{
			eraseTree(_root);
			_root = NULL;
			_size = 0;
		}
		void	erase(const value_type& value) {eraseNode(value, _root);} //erase single node in tree
		void	swap() {}

		// Lookup
		node* find(const value_type& value) const {return findNode(_root, value);} //searches from root of the tree for the value
		node* findLargest() const {return findLargest(_root);}
		node* findSmallest() const {return findSmallest(_root);}
		node* lower_bound(const value_type& value) const
		{
			node*	lower = findNode(_root, value);
			if (lower != NULL)
				return lower;
			return findLargest(_root);
		}
		node* upper_bound(const value_type& value)
		{
			node*	upper = findNode(_root, value);
			if (upper != NULL && upper->right != NULL)
				return upper;
			return findLargest(_root);
		}

	private:

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
			if (_root == NULL) //case 0 for inserting nodes
			{
				_root = newLeaf(NULL, value);
				_root->colour = BLACK;
			}
			else if (_comp(value, *(root->data))) //smaller than node
			{
				if (root->left == NULL) //leaf
				{
					root->left = newLeaf(root, value);
					fixViolationInsert(root->left);
				}
				else
					return insertLeaf(root->left, value); //not yet reached a leaf
			}
			else if (_comp(*(root->data), value)) // bigger than node
			{
				if (root->right == NULL) //leaf
				{
					root->right = newLeaf(root, value);
					fixViolationInsert(root->right);
				}
				else
					return insertLeaf(root->right, value); //not yet reached a leaf
			}
			else
				return false; // failed to insert new node
			return true;
		}

		// Deletions
		// Function for erasing a node in the tree
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

		/*
			* 2 cases:
			* 0. 0 and 1 child simple deletion
			* 1. 2 children: find inorder predecessor R of remov interchange them and delete the node at R
			* the inorder predecessor R always has at most one child. This reduces this deletion to case 0.
			*/
		// This erases the node found in the eraseNode function
		void	eraseMatch(node *parent, node *remov) //done
		{
			node*	replacer = getNodeReplacer(remov);
			bool	both_black = ((replacer == NULL || replacer->colour == BLACK) && remov->colour == BLACK);

			//case 0 - 0 child
			if (replacer == NULL)
			{
				if (remov == _root)
					_root = NULL;
				else
				{
					if (both_black)
						fixViolationErase(remov);
					else
					{
						if (getSibling(remov) != NULL)
							getSibling(remov)->colour = RED;
						if (isLeftNode(remov))
							parent->left = NULL;
						else
							parent->right = NULL;
					}
				}
				removeNode(remov);
				return ;
			}
			//case 0 - 1 child
			if (remov->left == NULL || remov->right == NULL)
			{
				if (remov == _root)
				{
					remov->data = replacer->data;
					remov->left = NULL;
					remov->right = NULL;
					removeNode(replacer);
				}
				else
				{
					if (isLeftNode(remov))
						parent->left = replacer;
					else
						parent->right = replacer;
					removeNode(remov);
					replacer->parent = parent;
					if (both_black)
						fixViolationErase(replacer);
					else
						replacer->colour = BLACK;
				}
				return ;
			}

			//case 1 - 2 children
			swapValues(replacer, remov);
			eraseMatch(replacer->parent, replacer);
		}

		// This actually deallocates the node
		void	removeNode(node *remov) //done
		{
			_alloc.destroy(remov->data);
			_alloc.deallocate(remov->data, 1);
			_node_alloc.destroy(remov);
			_node_alloc.deallocate(remov->data, 1);
			_size--;
		}

		// This function deallocates the whole tree
		void	eraseTree(node* root) //done
		{
			if (root != NULL)
			{
				if (root->left != NULL)
					eraseTree(root->left);
				if (root->right != NULL)
					eraseTree(root->right);
				_alloc.destroy(root->data);
				_alloc.deallocate(root->data, 1);
				_node_alloc.destroy(root);
				_node_alloc.deallocate(root, 1);
			}
		}

		// Reordering
		// Swaps the data of the two nodes
		void	swapValues(node* a, node* b)
		{
			value_type	temp = a->data;
			a->data = b->data;
			b->data = temp;
		}

		// Function updates the parent of the old_child with the new_child
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

		/*After inserting recolour and rotate tree to fix violations
		* 4 scenarios:
		* 0. node added is root this case is already handled in the insertleaf function
		* 1. node added's uncle is red -> recolour parent, grandparent and uncle
		* 2. node added's uncle is black (triangle) -> rotate parent
		* 3. node added's uncle is black (line) -> rotate grandparent and recolour grandparent and parent after rotation
		*/
		void	fixViolationInsert(node* root) //done
		{
			if (root->parent && root->parent->colour == BLACK) // no fixing needed
				return;
			if (root->parent == NULL) // case 0
			{
				root->colour = BLACK;
				return;
			}

			node*	original_parent = root->parent;
			node*	uncle = getUncle(root);
			node*	original_grand_parent = getGrandParent(root);
			if (uncle != NULL && uncle->colour == RED) //case 1
			{
				original_parent->colour = BLACK;
				original_grand_parent->colour = RED;
				uncle->colour = BLACK;
				fixViolationInsert(original_grand_parent);
			}
			else // case 2 and 3
			{
				if (original_parent == original_grand_parent->left)
				{
					if (root == original_parent->right)
					{
						rotateLeft(original_parent); //case 2 triangle
						original_parent = root; //case 2 triangle
					}
					rotateRight(original_grand_parent); //case 3 line
				}
				else
				{
					if (root == original_parent->left) 
					{
						rotateRight(original_parent); //case 2 triangle
						original_parent = root;		//case 2 triangle
					}
					rotateLeft(original_grand_parent); //case 3 line
				}
				original_parent->colour = BLACK; //case 3 line
				original_grand_parent->colour = RED; //case 3 line
			}
		}

		/*After deleting recolour and rotate tree to fix violations
			* 3 scenarios based on the sibling
			* 0. sibling is black and has a red child
			* 1. sibling is black and has a black children -> recursive solve
			* 2. sibling is red -> rotate and recolour , recursive
			*/
		void	fixViolationErase(node* root) 
		{
			if (root == _root)
				return;
			node*	sibling = getSibling(root);
			node*	parent = root->parent;

			if (sibling == NULL) // no siblings case 1.
				fixViolationErase(parent);
			else
			{
				if (sibling->colour == RED) //sibling is red
				{
					parent->colour = RED;
					sibling->colour = BLACK;
					if (isLeftNode(sibling))
						rotateRight(parent);
					else
						rotateLeft(parent);
					fixViolationErase(root);
				}
				else
				{
					if (hasRedChild(sibling))
					{
						if (sibling->left != NULL && sibling->left->colour == RED)
						{
							if (isLeftNode(sibling))
							{
								sibling->left->colour = sibling->colour;
								sibling->colour = parent->colour;
								rotateRight(parent);
							}
							else
							{
								sibling->left->colour = parent->colour;
								rotateRight(sibling);
								rotateLeft(parent);
							}
						}
						else
						{
							if (isLeftNode(sibling))
							{
								sibling->right->colour = parent->colour;
								rotateLeft(sibling);
								rotateRight(parent);
							}
							else
							{
								sibling->right->colour = sibling->colour;
								sibling->colour = parent->colour;
								rotateLeft(parent);
							}
						}
						parent->colour = BLACK;
					}
					else
					{
						sibling->colour = RED;
						if (parent->colour == BLACK)
							fixViolationErase(parent);
						else
							parent->colour = BLACK;
					}
				}
			}
		}

		void	rotateLeft(node* root)
		{
			node*	parent = root->parent;
			node*	right = root->right;

			root->right = right->left;
			if (right->left != NULL)
				right->left->parent = root;
			right->left = root;
			root->parent = right;
			updateParentChild(parent, root, right);
		}

		void	rotateRight(node* root)
		{
			node*	parent = root->parent;
			node*	left = root->left;

			root->left = left->right;
			if (left->right != NULL)
				left->right->parent = root;
			left->right = root;
			root->parent = left;
			updateParentChild(parent, root, left);
		}

		// Lookup
		//searches from a point on the tree for the value
		node*	findNode(node* root, const value_type& value) const //done
		{
			if (root != NULL)
			{
				if (isEqual(*(root->data), value))
					return root;
				else if (_comp(value, *(root->data)))
					return findNode(root->left, value);
				return findNode(root->right, value);
			}
			else
				return NULL;
		}

		// Function to find the inorder_successor (smallest value in right side of the subtree)
		node*	findSmallest(node* root) const //done
		{
			if (root && root->left != NULL)
				return findSmallest(root->left);
			else
				return root;
		}

		node*	findLargest(node* root) const //done
		{
			node*	current = root;

			while (current && current->right != NULL)
				current = current->right;
			return current;
		}

		node*	getNodeReplacer(node* root)
		{
			if (root->left == NULL && root->right == NULL)
				return NULL;
			if (root->left != NULL && root->right != NULL)
				return findSmallest(root->right);
			if (root->left != NULL)
				return root->left;
			return root->right;
		}
		
		// checks if the two values are equal using the compare
		bool	isEqual(const value_type& a, const value_type& b) const //done
		{
			if (_comp(a, b))
				return false;
			else if (_comp(b, a))
				return false;
			return true;
		}

		bool	isLeftNode(node* root)
		{
			if (root->parent->left == _root)
				return true;
			return false;
		}

		bool	hasRedChild(node *root)
		{
			if (root->left && root->left->colour == RED)
				return true;
			if (root->right && root->right->colour == RED)
				return true;
			return false;
		}

		//This is used to check if the node has children
		size_type	countChildren(node *root)
		{
			if (root->left == NULL && root->right == NULL)
				return 0;
			else if (root->left == NULL || root->right == NULL)
				return 1;
			return 2;
		}

		node*	getGrandParent(node *root)
		{
			if (root->parent)
				return root->parent->parent;
			return NULL;
		}

		// find the uncle of the node
		node*	getUncle(node* root)
		{
			node*	grandpa = getGrandParent(root);
			if (grandpa->right == root->parent)
				return grandpa->left;
			return grandpa->right;
		}

		// find the sibling of the current node
		node* getSibling(node* root)
		{
			if (root->parent)
			{
				if (isEqual(root->parent->left->data, root->data))
					return root->parent->right;
				return root->parent->left;
			}
			return NULL;
		}
	};
}

#endif
