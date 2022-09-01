#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft
{
	template <class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&, class Category = std::random_access_iterator_tag>
	class iterator
	{

	public: // typedefs
		typedef Category						iterator_category;
		typedef T								value_type;
		typedef Distance						difference_type;
		typedef Pointer							pointer;
		typedef Reference						reference;
		typedef iterator<T, const T*, const T&>	const_iterator_type;

	public: // Member Functions
		iterator(void) : _ptr(NULL) {}
		iterator(value_type* ptr) : _ptr(ptr) {}
		iterator(const iterator& src) : _ptr(src.getPos()) {}

		~iterator() {}

		operator const_iterator_type() const {return const_iterator_type(_ptr);}

		iterator&		operator=(const iterator& rhs) {_ptr = rhs._ptr; return *this;}

		friend bool		operator>(const iterator& lhs, const iterator& rhs) {return lhs.getPos() > rhs.getPos();}
		friend bool		operator>=(const iterator& lhs, const iterator& rhs) {return !(rhs.getPos() > lhs.getPos());}
		friend bool		operator<(const iterator& lhs, const iterator& rhs) {return rhs.getPos() < lhs.getPos();}
		friend bool		operator<=(const iterator& lhs, const iterator& rhs) {return !(lhs.getPos() > rhs.getPos());}
		friend bool		operator==(const iterator& lhs, const iterator& rhs) {return lhs.getPos() == rhs.getPos();}
		friend bool		operator!=(const iterator& lhs, const iterator& rhs) {return !(lhs.getPos() == rhs.getPos());}

		iterator		operator+(const int& n) const {iterator copy(*this); copy._ptr += n; return copy;}
		iterator		operator-(const int& n) const {iterator copy(*this); copy._ptr -= n; return copy;}

		iterator&		operator++(void) {_ptr++; return *this;}
		iterator		operator++(int)	{iterator	copy(*this); _ptr++; return copy;}
		iterator&		operator--(void) {_ptr--; return *this;}
		iterator		operator--(int) {iterator	copy(*this); _ptr--; return copy;}

		iterator&		operator+=(const int& n) {_ptr += n; return *this;}
		iterator&		operator-=(const int& n) {_ptr -= n; return *this;}

		iterator		operator*() const {return *(_ptr);}
		iterator		operator*() {return *(_ptr);}

		iterator		operator->() const {return _ptr;}
		iterator		operator->() {return _ptr;}

		reference		operator[](difference_type index) {iterator copy(*this); copy._ptr += index; return *copy._ptr;}

		value_type*		getPos() const {return _ptr;}

	private: // Variables
		value_type* 	_ptr;

	};
	
}

#endif