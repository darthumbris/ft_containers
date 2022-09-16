#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template <class T, class Container = vector<T> >
	class stack
	{

	public: //typedefs

		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;

	protected: // variables

		Container	c;

	public: // member functions

		explicit	stack(const Container& cont = Container()) : c(cont) {}
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
		bool			empty() const {return c.empty();}
		size_type		size() const {return c.size();}

		void			push(const value_type& value) {c.push_back(value);}
		void			pop() {c.pop_back();}

		template <class T2, class Container_>
		friend bool operator==(const stack<T2,Container_>& lhs, const stack<T2,Container_>& rhs);

		template <class T2, class Container_>
		friend bool operator<(const stack<T2,Container_>& lhs, const stack<T2,Container_>& rhs);
	};

	template <class T, class C> bool operator==(const stack<T,C>& lhs, const stack<T,C>& rhs) {return lhs.c == rhs.c;}
	template <class T, class C> bool operator!=(const stack<T,C>& lhs, const stack<T,C>& rhs) {return !(lhs == rhs);}
	template <class T, class C> bool operator< (const stack<T,C>& lhs, const stack<T,C>& rhs) {return lhs.c < rhs.c;}
	template <class T, class C> bool operator<=(const stack<T,C>& lhs, const stack<T,C>& rhs) {return (!(rhs < lhs));}
	template <class T, class C> bool operator> (const stack<T,C>& lhs, const stack<T,C>& rhs) {return (rhs < lhs);}
	template <class T, class C> bool operator>=(const stack<T,C>& lhs, const stack<T,C>& rhs) {return (!(lhs < rhs));}
}
#endif
