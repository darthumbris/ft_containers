#ifndef MAP_HPP
# define MAP_HPP

# include <memory> //for std::allocator
# include "../iterators/reverse_iterator.hpp" //for all the iterator stuff
# include "../utils/utils.hpp" //for enable if and other util functions
# include "../utils/redblacktree.hpp"
# include "../iterators/bidirectional_iterator.hpp"

namespace ft
{
	template< class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{

	public: //typedefs

		typedef Key								key_type;
		typedef T								mapped_type;
		typedef pair<const Key, T>				value_type;
		typedef unsigned long					size_type;
		typedef long							difference_type;
		typedef Compare							key_compare;
		typedef Alloc							allocator_type;
		typedef typename Alloc::reference		reference;
		typedef typename Alloc::const_reference	const_reference;
		typedef typename Alloc::pointer			pointer;
		typedef typename Alloc::const_pointer	const_pointer;

	private:

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

		typedef redblacktree<value_type, allocator_type, value_compare>	tree_type;

		//Exception
		class out_of_range: public std::exception {
		private:
			const char* _msg;
		public:
			out_of_range(const char* msg) : _msg(msg) {}
			virtual const char* what() const throw() {return _msg;}
		};

		//variables
		tree_type		_tree;
		allocator_type	_alloc;
		key_compare		_cmp;

	public:

		typedef bidirectional_iterator<value_type, value_compare, Alloc>									iterator;
		typedef bidirectional_iterator<value_type, value_compare, Alloc, const_pointer, const_reference>	const_iterator;
		typedef ft::reverse_iterator<iterator>																reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>														const_reverse_iterator;

	public: // Member Functions

		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) // empty
		: _tree(alloc, value_compare(comp)), _alloc(alloc), _cmp(comp) {}

		template <class InputIt>
		map (InputIt first, InputIt last, const key_compare& comp = key_compare(), 
			const allocator_type& alloc = allocator_type(), 
			typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = true) // range
			: _tree(alloc, value_compare(comp)), _alloc(alloc), _cmp(comp)
		{insert(first, last);}

		map (const map& other) : _tree(other._alloc, value_compare(other._cmp))
		{*this = other;} // copy

		~map() {_tree.clear();}

		map&			operator=(const map& other)
		{
			_cmp = other._cmp;
			_tree.clear();
			insert(other.begin(), other.end());
			return *this;
		}
		allocator_type	get_allocator() const {return _alloc;}

		// element access
		T&				at(const Key& key)
		{
			ft::node<value_type>* child = _tree.find(ft::make_pair(key, mapped_type()));
			if (child == NULL)
				throw out_of_range("map::at:  key not found");
			return child->data->second;
		}
		const T&		at(const Key& key) const
		{
			ft::node<value_type>* child = _tree.find(ft::make_pair(key, mapped_type()));
			if (child == NULL)
				throw out_of_range("map::at:  key not found");
			return child->data->second;
		}
		T&				operator[](const Key& key)
		{
			value_type	value = ft::make_pair(key, mapped_type());
			_tree.insert(value);
			return _tree.find(value)->data->second;
		}

		// iterators
		iterator				begin() {return iterator(_tree.findSmallest() ? _tree.findSmallest()->data : NULL, &_tree);}
		const_iterator			begin() const {return const_iterator(_tree.findSmallest() ? _tree.findSmallest()->data : NULL, &_tree);}
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
		void					clear() {_tree.clear();}

		ft::pair<iterator, bool>	insert(const value_type& value)
		{
			bool	succes = _tree.insert(value);
			ft::node<value_type>*	node = _tree.find(value);
			return ft::make_pair<iterator, bool>(iterator(node->data, &_tree), succes);
		}
		iterator					insert(iterator hint, const value_type& value)
		{
			if(hint != end() && hint->first == value.first)
				return hint;
			return insert(value).first;
		}
		template<class InputIt>
		void						insert(InputIt first, InputIt last)
		{
			for (InputIt it = first; it != last; it++)
				insert(*it);
		}
		void						erase(iterator pos) _NOEXCEPT
		{
			// iterator it = find(pos->first);
			// if (it == pos)
			// 	erase(pos->first);
			_tree.erase(*pos);
		}
		void						erase(iterator first, iterator last)
		{
			for (iterator it = first; it != last; it++)
			{
				erase(it->first);
			}
		}
		size_type					erase(const Key& key)
		{
			if (_tree.find(ft::make_pair(key, mapped_type())) != NULL)
			{
				_tree.erase(ft::make_pair(key, mapped_type()));
				return 1;
			}
			return 0;
		}
		void						swap(map& other)
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
		size_type									count(const Key& key) const
		{
			if (_tree.find(ft::make_pair(key, mapped_type())) != NULL)
				return 1;
			return 0;
		}
		iterator									find(const Key& key)
		{
			return iterator(_tree.find(ft::make_pair(key, mapped_type())) ? _tree.find(ft::make_pair(key, mapped_type()))->data : NULL, &_tree);
		}
		const_iterator								find(const Key& key) const
		{
			return const_iterator(_tree.find(ft::make_pair(key, mapped_type())) ? _tree.find(ft::make_pair(key, mapped_type()))->data : NULL, &_tree);
		}
		ft::pair<iterator,iterator>					equal_range(const Key& key)
		{
			return ft::make_pair(lower_bound(key), upper_bound(key));
		}
		ft::pair<const_iterator,const_iterator>		equal_range(const Key& key) const
		{
			return ft::make_pair(lower_bound(key), upper_bound(key));
		}
		iterator									lower_bound(const Key& key)
		{
			ft::node<value_type>*	node = _tree.root();
			ft::node<value_type>*	temp = node;

			while (node != NULL)
			{
				if (!_cmp(node->data->first, key))
				{
					temp = node;
					node = node->left;
				}
				else
					node = node->right;
			}
			return iterator(temp ? temp->data : NULL, &_tree);
		}
		const_iterator								lower_bound(const Key& key) const
		{
			ft::node<value_type>*	node = _tree.root();
			ft::node<value_type>*	temp = node;

			while (node != NULL)
			{
				if (!_cmp(node->data->first, key))
				{
					temp = node;
					node = node->left;
				}
				else
					node = node->right;
			}
			return const_iterator(temp ? temp->data : NULL, &_tree);
		}
		iterator									upper_bound(const Key& key)
		{
			iterator it = lower_bound(key);

			if (it != end() && key == it->first)
				return ++it;
			return it;
		}
		const_iterator								upper_bound(const Key& key) const
		{
			const_iterator it = lower_bound(key);

			if (it != end() && key == it->first)
				return ++it;
			return it;
		}

		// Observers
		key_compare									key_comp() const {return _cmp;}
		value_compare								value_comp() const {return value_compare(_cmp);}
	};
}

template<class Key, class T, class Compare, class Alloc>
bool	operator==(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template<class Key, class T, class Compare, class Alloc>
bool	operator!=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
{
	return !(lhs == rhs);
}

template<class Key, class T, class Compare, class Alloc>
bool	operator< (const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) //done
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<class Key, class T, class Compare, class Alloc>
bool	operator<=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
{
	return (!(rhs < lhs));
}

template<class Key, class T, class Compare, class Alloc>
bool	operator> (const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
{
	return (rhs < lhs);
}

template<class Key, class T, class Compare, class Alloc>
bool	operator>=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
{
	return (!(lhs < rhs));
}

template<class Key, class T, class Compare, class Alloc>
void	swap(ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs)
{
	lhs.swap(rhs);
}

#endif
