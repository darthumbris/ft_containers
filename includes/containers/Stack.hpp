#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T>>
	class stack
	{

	public: //typedefs

		typedef Container					container_type;
		typedef Container::value_type		value_type;
		typedef Container::size_type		size_type;
		typedef Container::reference		reference;
		typedef Container::const_reference	const_reference;

	protected:
		Container	c;

	public:

		explicit	stack(const Container& cont = Container()) {}

					stack(const stack& other) {*this = other;} // copy //done
		
					~stack() {}

		stack& 		operator=(const stack& other) //done
		{
			c = other.c;
			return *this;
		}

		// Element access
		reference		top() {return c.back();}
		const_reference	top() const {return c.back();}

		// Capacity
		bool			empty() const {return (c.size() == 0);}
		size_type		size() const {return c.size();}

		void			push(const value_type& value) {c.push_back(value);}
		void			pop() {c.pop_back();}

	};
}

template <class T, class Allocator> bool operator==(const ft::stack<T,Allocator>& lhs, const ft::stack<T,Allocator>& rhs) //done
{
	if (lhs._size != rhs._size)
		return false;
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}
template <class T, class Allocator> bool operator!=(const ft::stack<T,Allocator>& lhs, const ft::stack<T,Allocator>& rhs) {return !(lhs == rhs);} //done
template <class T, class Allocator> bool operator< (const ft::stack<T,Allocator>& lhs, const ft::stack<T,Allocator>& rhs) //done
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
template <class T, class Allocator> bool operator<=(const ft::stack<T,Allocator>& lhs, const ft::stack<T,Allocator>& rhs) {return (!(rhs < lhs));} //done
template <class T, class Allocator> bool operator> (const ft::stack<T,Allocator>& lhs, const ft::stack<T,Allocator>& rhs) {return (rhs < lhs);} //done
template <class T, class Allocator> bool operator>=(const ft::stack<T,Allocator>& lhs, const ft::stack<T,Allocator>& rhs) {return (!(lhs < rhs));} //done

#endif
