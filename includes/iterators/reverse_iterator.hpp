#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft
{
	template <class Iter>
	class reverse_iterator
	{
	public: // typedefs

		typedef Iter													iterator_type;
		typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iter>::value_type			value_type;
		typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iter>::pointer				pointer;
		typedef typename ft::iterator_traits<Iter>::reference			reference;

	public: // Member functions

		reverse_iterator() : _iter() {}
		explicit	reverse_iterator(iterator_type it) : _iter(it) {}
		template <class Iterator>	reverse_iterator(const reverse_iterator<Iterator>& rev_it) : _iter(rev_it) {}

		iterator_type 			base() const {return _iter;}

		reverse_iterator		operator*() const {iterator_type copy(*this); return *(--copy);}
		reverse_iterator		operator*() {iterator_type copy(*this); return *(--copy);}

		reverse_iterator		operator+(difference_type n) const {reverse_iterator copy(*this); copy._iter -= n; return copy;}

		reverse_iterator&		operator++(void) {_iter--; return *this;}
		reverse_iterator		operator++(int)	{reverse_iterator	copy(*this); _iter--; return copy;}

		reverse_iterator&		operator+=(difference_type n) {_iter -= n; return *this;}

		reverse_iterator		operator-(difference_type n) const {reverse_iterator copy(*this); copy._iter += n; return copy;}
		
		reverse_iterator&		operator--(void) {_iter++; return *this;}
		reverse_iterator		operator--(int) {reverse_iterator	copy(*this); _iter++; return copy;}

		reverse_iterator&		operator-=(difference_type n) {_iter += n; return *this;}

		reverse_iterator		operator->() const {reverse_iterator copy(*this); return &(*--copy);}
		reverse_iterator		operator->() {reverse_iterator copy(*this); return &(*--copy);}

		reference				operator[](difference_type n) {reverse_iterator copy(*this); copy._iter -= n; return *(--copy._iter);}

		Iter					getIter() {return _iter;}

	private:
		Iter    _iter;
	};

	// non-member Operator overflows
	template <class Iter>
	bool operator==(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) {return lhs.getIter() == rhs.getIter();}

	template <class Iter>
	bool operator!=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) {return !(lhs.getIter() == rhs.getIter());}

	template <class Iter>
	bool operator< (const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) {return lhs.getIter() < rhs.getIter();}

	template <class Iter>
	bool operator<=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) {return !(rhs.getIter() < lhs.getIter());}

	template <class Iter>
	bool operator> (const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) {return rhs.getIter() < lhs.getIter();}

	template <class Iter>
	bool operator>=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) {return !(lhs.getIter() < rhs.getIter());}


	template <class Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& rev_it) {return rev_it + n;}

	template <class Iter>
	typename reverse_iterator<Iter>::difference_type operator-(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) {
		return rhs.getIter().getPos() - lhs.getIter().getPos();
	}

}

#endif