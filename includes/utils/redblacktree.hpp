#ifndef REDBLACKTREE_HPP
# define REDBLACKTREE_HPP

// # include "node.hpp"
// # include "Tree.hpp"

/*
 * notes: 
 * - https://www.codesdope.com/course/data-structures-red-black-trees-insertion/
 * - https://www.geeksforgeeks.org/red-black-tree-set-2-insert/
 * - https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/
 * - https://www.youtube.com/watch?v=_c30ot0Kcis&list=PLwyTr3n29dXRDviK2r4fcF_9lr8pL1tlr
*/

namespace ft
{
	enum colour
    {
        BLACK,
        RED
    };

    template<typename value_type>
    struct node
    {
        // Constructor for node, default colour is RED and NIL leaves are also set
        node(node* parent) : colour(RED), parent(parent), left(NULL), right(NULL) {}

        value_type* data;
        colour      colour;
        node*       parent;
        node*       left;
        node*       right;
    };


	template<class T, class Alloc, class Compare>
	class redblacktree
	{
	public: //typedefs

		typedef Alloc											allocator_type;
		typedef	unsigned long									size_type;
		typedef long											difference_type;
		typedef T												value_type;
		typedef ft::node<value_type>							node;
		typedef typename Alloc::template rebind<node>::other	node_allocator_type;

	private:
		node*				_root; //root of the tree
		allocator_type		_alloc; //alloc for the data of the nodes
		node_allocator_type	_node_alloc; //alloc for the nodes itself
		size_type			_size; //size of the tree
		Compare				_comp; //Compare class used to compare values

	public:

		redblacktree(Alloc alloc, Compare compare) : _root(NULL), _alloc(alloc), _size(0), _comp(compare) {}
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

		node*		root() {return _root;}
		
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
		void	swap(redblacktree& tree)
		{
			node*				temp_root = _root;
			size_type			temp_size = _size;
			Compare 			temp_comp = _comp;
			allocator_type		temp_alloc= _alloc;
			node_allocator_type	temp_node_alloc = _node_alloc;

			_root = tree._root;
			tree._root = temp_root;
			_size = tree._size;
			tree._size = temp_size;
			_comp = tree._comp;
			tree._comp = temp_comp;
			_alloc = tree._alloc;
			tree._alloc = temp_alloc;
			_node_alloc = tree._node_alloc;
			tree._node_alloc = temp_node_alloc;
		}

		// Lookup
		node* find(const value_type& value) const {return findNode(_root, value);} //searches from root of the tree for the value
		node* findLargest() const {return findLargest(_root);}
		node* findSmallest() const {return findSmallest(_root);}
		node* lower_bound(const value_type& value) const
		{
			node*	lower = findNode(_root, value);
			if (lower == NULL)
				return NULL;
			if (lower->right != NULL)
				return findSmallest(lower->right);
			node* successor = lower->parent;
			while (successor != NULL && lower == successor->right)
			{
				lower = successor;
				successor = successor->parent;
			}
			lower = successor;
			return lower;
		}
		node* upper_bound(const value_type& value) const
		{
			node*	upper = findNode(_root, value);
			if (upper == NULL)
				return NULL;
			if (upper->left != NULL)
				return findLargest(upper->left);

			node* pred = upper->parent;
			while (pred != NULL && upper == pred->left)
			{
				upper = pred;
				pred = pred->parent;
			}
			upper = pred;
			return upper;
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
		void	eraseNode(const value_type& value, node* node) //done
		{			
			if (_root != NULL)
			{
				if (isEqual(value, *(node->data)))
					eraseMatch(NULL, _root);
				else
				{
					if (_comp(*(node->data), value) && node->right != NULL)
					{
						if (isEqual(*node->right->data, value))
							eraseMatch(node, node->right);
						else
							eraseNode(value, node->right);
					}
					else if (_comp(value, *(node->data)) && node->left != NULL)
					{
						if (isEqual(*node->left->data, value))
							eraseMatch(node, node->left);
						else
							eraseNode(value, node->left);
					}
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
			node*	node_move_up = remov;
			colour	deleted_colour = remov->colour;
			bool	is_nill = false;
			node*	nil_node = NULL;

			if (remov->left == NULL && remov->right == NULL)
			{
				is_nill = true;
				nil_node = remov;
			}
			else if (remov->left == NULL || remov->right == NULL)
			{
				if (remov->right != NULL)
					node_move_up = remov->right;
				else
					node_move_up = remov->left;
				updateParentChild(parent, remov, node_move_up);
				node_move_up->parent = remov->parent;
				removeNode(remov);
			}
			else
			{
				node* smallest = findSmallest(remov->right);
				if (smallest->right)
					node_move_up = smallest->right;
				else
				{
					is_nill = true;
					value_type	nil_data = value_type();
					nil_node = newLeaf(NULL, nil_data);
					nil_node->colour = BLACK;
					updateParentChild(smallest->parent, smallest, nil_node);
					node_move_up = nil_node;
				}
				if (smallest->parent == remov)
				{
					updateParentChild(remov->parent, remov, smallest);
					smallest->left = remov->left;
					remov->left->parent = smallest;
					if (!smallest->right)
					{
						smallest->right = nil_node;
						nil_node->parent = smallest;
					}
				}
				else
				{
					if (smallest->right)
					{
						smallest->right->parent = smallest->parent;
						smallest->parent->left = smallest->right;
					}
					updateParentChild(remov->parent, remov, smallest);
					smallest->left = remov->left;
					remov->left->parent = smallest;
					smallest->right = remov->right;
					remov->right->parent = smallest;
				}
				deleted_colour = smallest->colour;
				smallest->colour = remov->colour;
				removeNode(remov);
			}
			if (deleted_colour == BLACK)
				fixViolationErase(node_move_up);
			if (is_nill)
			{
				updateParentChild(nil_node->parent, nil_node, NULL);
				removeNode(nil_node);
			}
		}

		// This actually deallocates the node
		void	removeNode(node *remov) //done
		{
			_alloc.destroy(remov->data);
			_alloc.deallocate(remov->data, 1);
			_node_alloc.destroy(remov);
			_node_alloc.deallocate(remov, 1);
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

		// Function updates the parent of the old_child with the new_child
		void	updateParentChild(node* parent, node* old_child, node* new_child) //done
		{
			if (parent == NULL)
				_root = new_child;
			else if (parent->left == old_child)
				parent->left = new_child;
			else if (parent->right == old_child)
				parent->right = new_child;
			if (new_child != NULL)
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
		void	fixViolationErase(node* moved) 
		{
			if (moved == _root)
			{
				moved->colour = BLACK;
				return;
			}
			node*	sibling = getSibling(moved);

			if (sibling->colour == RED) //sibling is red
			{
				sibling->colour = BLACK;
				moved->parent->colour = RED;
				if (moved == moved->parent->left)
					rotateLeft(moved->parent);
				else
					rotateRight(moved->parent);	
			}
			if (isNilorBlack(sibling->left) && isNilorBlack(sibling->right))
			{
				sibling->colour = RED;
				if (moved->parent->colour == RED)
					moved->parent->colour = BLACK;
				else
					fixViolationErase(moved->parent);
			}
			else //sibling has red child
			{
				bool	node_left = (moved == moved->parent->left);
				if (node_left && isNilorBlack(sibling->right))
				{
					sibling->left->colour = BLACK;
					sibling->colour = RED;
					rotateRight(sibling);
					sibling = moved->parent->right;
				}
				else if (!node_left && isNilorBlack(sibling->left))
				{
					sibling->right->colour = BLACK;
					sibling->colour = RED;
					rotateLeft(sibling);
					sibling = moved->parent->left;
				}

				sibling->colour = moved->parent->colour;
				moved->parent->colour = BLACK;
				if (node_left)
				{
					sibling->right->colour = BLACK;
					rotateLeft(moved->parent);
				}
				else
				{
					sibling->left->colour = BLACK;
					rotateRight(moved->parent);
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
			node*	current = root;
		
			while (current && current->left != NULL)
				current = current->left;
			return current;
		}

		node*	findLargest(node* root) const //done
		{
			node*	current = root;

			while (current && current->right != NULL)
				current = current->right;
			return current;
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
			node* parent = root->parent;
			if (root == parent->left)
				return parent->right;
			else
				return parent->left;
		}

		bool	isNilorBlack(node* root)
		{
			return (root == NULL || root->colour == BLACK);
		}
	};
}

#endif
