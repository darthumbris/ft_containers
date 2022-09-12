#ifndef MAP_HPP
# define MAP_HPP


# include <memory> //for std::allocator
# include "iterators/reverse_iterator.hpp" //for all the iterator stuff
# include "utils/utils.hpp" //for enable if and other util functions
# include <algorithm> //for std::min
# include "utils/redblacktree.hpp"
# include "iterators/bidirectional_iterator.hpp"

namespace ft
{
	template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T>>>
	class map
	{

	public: //typedefs

		typedef Key																		key_type;
		typedef T																		mapped_type;
		typedef ft::pair<const Key, T>													value_type;
		typedef unsigned long															size_type;
		typedef long																	difference_type;
		typedef Compare																	key_compare;
		typedef Allocator																allocator_type;
		typedef value_type&																reference;
		typedef const value_type&														const_reference;
		typedef typename Allocator::pointer												pointer;
		typedef typename Allocator::const_pointer										const_pointer;
		typedef ft::bidirectional_iterator<value_type>									iterator;
		typedef ft::bidirectional_iterator<value_type, const_pointer, const_reference>	const_iterator;
		typedef ft::reverse_iterator<iterator>											reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>									const_reverse_iterator;
		

	private: //typedefs

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

		//Exception
		class out_of_range: public std::exception {
		private:
			const char* _msg;
		public:
			out_of_range(const char* msg) : _msg(msg) {}
			virtual const char* what() const throw() {
				return _msg;
			}
		};

		typedef ft::redblacktree<value_type, Allocator, value_compare>	tree_type;

	private: //variables

		tree_type										_tree;
		allocator_type									_alloc;
		key_compare										_cmp;

	public:

		// map() :_alloc(NULL), ,_cmp(NULL), _size(0) {} //default

		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) // empty
		: _tree(alloc, value_compare(comp)), _alloc(alloc), _cmp(comp) {}

		template <class InputIt>
		map (InputIt first, InputIt last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),
		typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = true) // range
		: _tree(alloc, value_compare(comp)), _alloc(alloc), _cmp(comp) {insert(first, last);}

		map (const map& other) :_tree(other._alloc, value_compare(other._cmp)) {*this = other;} // copy

		~map() {_tree.clear();} //done

		map&										operator=(const map& other) //done
		{
			_cmp = other._cmp;
			_tree.clear();
			insert(other.begin(), other.end());
			return *this;
		}
		allocator_type								get_allocator() const {return _alloc;} //done

		// element access
		T&											at(const Key& key) //done
		{
			ft::node<value_type>* child = _tree.find(ft::make_pair(key, mapped_type()));
			if (child == NULL)
				throw out_of_range("map::at:  key not found");
			return child->data->second;
		}
		const T&									at(const Key& key) const //done
		{
			ft::node<value_type>* child = _tree.find(ft::make_pair(key, mapped_type()));
			if (child == NULL)
				throw out_of_range("map::at:  key not found");
			return child->data->second;
		}
		T&											operator[]( const Key& key )
		{
			value_type	value = ft::make_pair(key, mapped_type());
			_tree.insert(value);
			return _tree.find(value)->data->second;
		} //done


		// iterators
		iterator									begin() {return iterator(_tree.findSmallest(), &_tree);} //done
		const_iterator								begin() const {return const_iterator(_tree.findSmallest(), &_tree);} //done
		iterator									end() {return iterator(NULL, &_tree);} //done
		const_iterator								end() const {return const_iterator(NULL, &_tree);} //done
		reverse_iterator							rbegin() {return reverse_iterator(end());} //done
		const_reverse_iterator 						rbegin() const {return const_reverse_iterator(end());} //done
		reverse_iterator							rend() {return reverse_iterator(begin());} //done
		const_reverse_iterator						rend() const {return const_reverse_iterator(begin());} //done

		// Capacity
		bool										empty() const {return (_tree.size() == 0);} //done
		size_type									size() const {return _tree.size();} //done
		size_type									max_size() const {return _tree.max_size();} //done

		// Modifiers
		void										clear() {_tree.clear();} //done

		ft::pair<iterator, bool>					insert(const value_type& value) //done
		{
			bool	succes = _tree.insert(value);
			return ft::make_pair(iterator(_tree.find(value), &_tree), succes);
		}
		iterator									insert(iterator hint, const value_type& value) //done
		{
			if(hint != end() && hint->first == value.first)
				return hint;
			return insert(value).first;
		}
		template<class InputIt>
		void										insert(InputIt first, InputIt last) //done
		{
			for (InputIt it = first; it != last; it++)
				insert(*it);
		}
		void										erase(iterator pos) //done
		{
			iterator it = find(pos->first);
			if (it == pos)
				erase(pos->first);
		}
		void										erase(iterator first, iterator last)
		{
			for (iterator it = first; it != last; it++)
			{
				erase(it->first);
			}
		}
		size_type									erase(const Key& key) //done
		{
			if (_tree.find(ft::make_pair(key, mapped_type())) != NULL)
			{
				_tree.erase(ft::make_pair(key, mapped_type()));
				return 1;
			}
			return 0;
		}
		void										swap(map& other) //done
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
		size_type									count(const Key& key) const //done
		{
			if (_tree.find(ft::make_pair(key, mapped_type())) != NULL)
				return 1;
			return 0;
		}
		iterator									find(const Key& key) {return iterator(_tree.find(ft::make_pair(key, mapped_type())), &_tree);} //done
		const_iterator								find(const Key& key) const {return const_iterator(_tree.find(ft::make_pair(key, mapped_type())), &_tree);} //done
		ft::pair<iterator,iterator>					equal_range(const Key& key) {return ft::make_pair(lower_bound(key), upper_bound(key));} //done
		ft::pair<const_iterator,const_iterator>		equal_range(const Key& key) const {return ft::make_pair(lower_bound(key), upper_bound(key));} //done
		iterator									lower_bound(const Key& key) {return iterator(_tree.lower_bound(key), &_tree);} //done
		const_iterator								lower_bound(const Key& key) const {return const_iterator(_tree.lower_bound(key), &_tree);} //done
		iterator									upper_bound(const Key& key) {return iterator(_tree.upper_bound(key), &_tree);} //done
		const_iterator								upper_bound(const Key& key) const {return const_iterator(_tree.upper_bound(key), &_tree);} //done

		// Observers
		key_compare									key_comp() const {return _cmp;} //done
		value_compare								value_comp() const {return value_compare(_cmp);} //done
	};
}

template<class Key, class T, class Compare, class Alloc> bool	operator==(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) //done
{
	if (lhs._size != rhs._size)
		return false;
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}
template<class Key, class T, class Compare, class Alloc> bool	operator!=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) {return !(lhs == rhs);} //done
template<class Key, class T, class Compare, class Alloc> bool	operator< (const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) //done
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
template<class Key, class T, class Compare, class Alloc> bool	operator<=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) {return (!(rhs < lhs));} //done
template<class Key, class T, class Compare, class Alloc> bool	operator> (const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) {return (rhs < lhs);} //done
template<class Key, class T, class Compare, class Alloc> bool	operator>=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) {return (!(lhs < rhs));} //done

template<class Key, class T, class Compare, class Alloc>
void	swap(ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs) {lhs.swap(rhs);} //done

#endif
