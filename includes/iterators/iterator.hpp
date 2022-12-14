#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft
{
	template <class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&, class Category = std::random_access_iterator_tag>
	class iterator
	{

	public: // typedefs

		typedef T								value_type;
		typedef T*								iterator_type;
		typedef Category						iterator_category;
		typedef Distance						difference_type;
		typedef Pointer							pointer;
		typedef Reference						reference;
		typedef iterator<T, const T*, const T&>	const_iterator_type;

	private: // Variables

		value_type* 	_ptr;

	public: // Member Functions

		iterator(void) : _ptr(NULL) {} //default
		iterator(value_type* ptr) : _ptr(ptr) {} 
		iterator(const iterator& src) : _ptr(src._ptr) {} //copy

		~iterator() {}

		operator	const_iterator_type() const {return const_iterator_type(_ptr);}

		iterator&				operator=(const iterator& rhs) {_ptr = rhs._ptr; return *this;}

		//friend keyword for a couple of these functions because they are nonmember overloads
		friend bool		operator> (const iterator& lhs, const iterator& rhs) {return lhs.base() > rhs.base();}
		friend bool		operator>=(const iterator& lhs, const iterator& rhs) {return !(rhs.base() > lhs.base());}
		friend bool		operator< (const iterator& lhs, const iterator& rhs) {return rhs.base() < lhs.base();}
		friend bool		operator<=(const iterator& lhs, const iterator& rhs) {return !(lhs.base() > rhs.base());}
		friend bool		operator==(const iterator& lhs, const iterator& rhs) {return lhs.base() == rhs.base();}
		friend bool		operator!=(const iterator& lhs, const iterator& rhs) {return !(lhs.base() == rhs.base());}

		iterator				operator+(const int& n) const {iterator copy(*this); copy._ptr += n; return copy;}
		friend iterator			operator+(const int& n, const iterator& a) {return a + n;}
		iterator				operator-(const int& n) const {return (iterator(_ptr - n));}
		friend difference_type	operator-(const iterator& a, const iterator& b) {return a.base() - b.base();}

		iterator&	operator++(void) {_ptr++; return *this;}
		iterator	operator++(int)	{iterator	copy(*this); _ptr++; return copy;}
		iterator&	operator--(void) {_ptr--; return *this;}
		iterator	operator--(int) {iterator	copy(*this); _ptr--; return copy;}

		iterator&	operator+=(const int& n) {_ptr += n; return *this;}
		iterator&	operator-=(const int& n) {_ptr -= n; return *this;}

		reference	operator*() const {return *(_ptr);}
		reference	operator*() {return *(_ptr);}

		pointer		operator->() const {return &(*_ptr);}
		pointer		operator->() {return &(*_ptr);}

		reference	operator[](difference_type index) {*_ptr[index];}

		value_type*	base() const {return _ptr;}
	};
}
#endif
