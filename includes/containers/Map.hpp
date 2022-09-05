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
		// tree_type										_tree;
		allocator_type									_alloc;

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

		map() :_alloc(NULL) {} //default

		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) // empty
		: _alloc(alloc)
		{
			value_compare._comp = comp;
		}

		template <class InputIt>
		map (InputIt first, InputIt last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) // range
		{

		}

		map (const map& x) // copy
		{
		
		}

		~map() {}

		map&										operator=(const map& __m) {}
		allocator_type								get_allocator() const {}

		// element access
		T&											at(const Key& key) {}
		const T&									at(const Key& key) const {}
		T&											operator[]( const Key& key ) {}


		// iterators
		iterator									begin() {}
		const_iterator								begin() const {}
		iterator									end() {}
		const_iterator								end() const {}
		reverse_iterator							rbegin() {}
		const_reverse_iterator 						rbegin() const {}
		reverse_iterator							rend() {}
		const_reverse_iterator						rend() const {}

		// Capacity
		bool										empty() const {}
		size_type									size() const {}
		size_type									max_size() const {}

		// Modifiers
		void										clear() {}

		ft::pair<iterator, bool>					insert(const value_type& value) {}
		iterator									insert(iterator hint, const value_type& value) {}
		template<class InputIt>
		void										insert(InputIt first, InputIt last) {}
		void										erase(iterator pos) {}
		void										erase(iterator first, iterator last) {}
		size_type									erase(const Key& key) {}
		void										swap(map& other) {}

		// Lookup
		size_type									count(const Key& key) const {}
		iterator									find(const Key& key) {}
		const_iterator								find(const Key& key) const {}
		ft::pair<iterator,iterator>					equal_range(const Key& key) {}
		ft::pair<const_iterator,const_iterator>		equal_range(const Key& key) const {}
		iterator									lower_bound(const Key& key) {}
		const_iterator								lower_bound(const Key& key) const {}
		iterator									upper_bound(const Key& key) {}
		const_iterator								upper_bound(const Key& key) const {}

		// Observers
		key_compare									key_comp() const {}
		ft::map::value_compare						value_comp() const {}
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
