#ifndef SET_HPP
# define SET_HPP

# include <memory>
# include "../iterators/reverse_iterator.hpp" //for all the iterator stuff
# include "../utils/utils.hpp" //for enable if and other util functions
# include "../utils/redblacktree.hpp"
# include "../iterators/bidirectional_iterator.hpp"

namespace ft
{
	template< class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
	class set
	{

	public: // Typedefs

		typedef Key 																key_type;
		typedef Key																	value_type;
		typedef unsigned long														size_type;
		typedef long																difference_type;
		typedef Compare																key_compare;
		typedef Compare																value_compare;
		typedef Allocator															allocator_type;
		typedef value_type&															reference;
		typedef const value_type&													const_reference;
		typedef typename Allocator::pointer											pointer;
		typedef typename Allocator::const_pointer									const_pointer;
		typedef bidirectional_iterator<value_type, const_pointer, const_reference>	iterator;
		typedef bidirectional_iterator<value_type, const_pointer, const_reference>	const_iterator;
		typedef ft::reverse_iterator<iterator>										reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>								const_reverse_iterator;

	private:

		typedef redblacktree<value_type, allocator_type, value_compare>	tree_type;
		typedef ft::node<value_type>									node_;

		//variables
		tree_type		_tree;
		allocator_type	_alloc;
		key_compare		_cmp;

	public: // Member Functions

		explicit set(const key_compare& comp = key_compare(), const Allocator& alloc = Allocator())
			: _tree(alloc, comp), _alloc(alloc), _cmp(comp) {}
		
		template <class InputIt>
		set(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator(),
			typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = true)
			: _tree(alloc, comp), _alloc(alloc), _cmp(comp) {insert(first, last);}

		set(const set& other) : _tree(other._alloc, value_compare(other._cmp)) {*this = other;}

		~set() {_tree.clear();}

		set&	operator=(const set& other)
		{
			_tree = other._tree;
			_cmp = other._cmp;
			_tree.clear();
			insert(other.begin(), other.end());
			return *this;
		}

		allocator_type			get_allocator() const {return _alloc;}

		// iterators
		iterator				begin() {return iterator(_tree.findSmallest(), &_tree);}
		const_iterator			begin() const {return const_iterator(_tree.findSmallest(), &_tree);}
		iterator				end() {return iterator(NULL, &_tree);}
		const_iterator			end() const {return const_iterator(NULL, &_tree);}
		reverse_iterator		rbegin() {return reverse_iterator(end());}
		const_reverse_iterator 	rbegin() const {return const_reverse_iterator(end());}
		reverse_iterator		rend() {return reverse_iterator(begin());}
		const_reverse_iterator	rend() const {return const_reverse_iterator(begin());}

		// Capacity
		bool					empty() const {return (_tree.size() == 0);}
		size_type				size() const {return _tree.size();}
		size_type				max_size() const {return _tree.max_size();}

		// Modifiers
		void						clear() {_tree.clear();}
		ft::pair<iterator, bool>	insert(const value_type& value)
		{
			bool	succes = _tree.insert(value);
			node_*	node = _tree.find(value);
			return ft::make_pair<iterator, bool>(iterator(node, &_tree), succes);
		}
		iterator				insert(iterator hint, const value_type& value)
			{return (hint != end() && *hint == value) ? hint : insert(value).first;}
		template<class InputIt>
		void					insert(InputIt first, InputIt last)
		{
			for (InputIt it = first; it != last; it++)
				insert(*it);
		}
		void					erase(iterator pos) {erase(*pos);}
		void					erase(iterator first, iterator last)
		{
			for (iterator it = first; it != last; it++)
				_tree.erase(*it);
		}
		size_type				erase(const Key& key)
		{
			if (_tree.find(key) == NULL)
				return 0;
			_tree.erase(key);
			return 1;
		}
		void					swap(set& other)
		{
			_tree.swap(other._tree);
			key_compare	temp_comp = _cmp;
			_cmp = other._cmp;
			other._cmp = temp_comp;
			allocator_type	temp_alloc = _alloc;
			_alloc = other._alloc;
			other._alloc = temp_alloc;
		}

		// Lookup
		size_type								count(const Key& key) const {return _tree.find(key) ? 1 : 0;}
		iterator								find(const Key& key) {return iterator(_tree.find(key), &_tree);}
		const_iterator							find(const Key& key) const{return const_iterator(find(key));}
		ft::pair<iterator,iterator>				equal_range(const Key& key) {return ft::make_pair(lower_bound(key), upper_bound(key));}
		ft::pair<const_iterator,const_iterator>	equal_range(const Key& key) const {return ft::make_pair(lower_bound(key), upper_bound(key));}
		iterator								lower_bound(const Key& key)
		{
			node_*	node = _tree.root();
			node_*	temp = node;

			while (node != NULL)
			{
				if (!_cmp(*node->data, key))
				{
					temp = node;
					node = node->left;
				}
				else
					node = node->right;
			}
			return iterator(temp, &_tree);
		}
		const_iterator			lower_bound(const Key& key) const {return const_iterator(lower_bound(key));}
		iterator				upper_bound(const Key& key)
		{
			iterator it = lower_bound(key);
			return (it != end() && key == *it) ? ++it : it;
		}
		const_iterator			upper_bound(const Key& key) const {return const_iterator(upper_bound(key));}

		// Observers
		key_compare				key_comp() const {return _cmp;}
		value_compare			value_comp() const {return value_compare(_cmp);}

	};

	template<class Key, class Compare, class Alloc>
	bool	operator==(const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template<class Key, class Compare, class Alloc>
	bool	operator!=(const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs) {return !(lhs == rhs);}

	template<class Key, class Compare, class Alloc>
	bool	operator< (const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs) //done
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<class Key, class Compare, class Alloc>
	bool	operator<=(const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs) {return (!(rhs < lhs));}

	template<class Key, class Compare, class Alloc>
	bool	operator> (const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs) {return (rhs < lhs);}

	template<class Key, class Compare, class Alloc>
	bool	operator>=(const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs) {return (!(lhs < rhs));}

	template<class Key, class Compare, class Alloc>
	void	swap(set<Key,Compare,Alloc>& lhs, set<Key,Compare,Alloc>& rhs) {lhs.swap(rhs);}
}

#endif
