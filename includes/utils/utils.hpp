#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{
	template<bool Cond, class T = void> struct enable_if {};

	template<class T>
	struct enable_if<true, T> {typedef T type;};

	template <class T> struct is_integral					{ static const bool value = false;};
	template <> struct is_integral<bool>					{ static const bool value = true;};
	template <> struct is_integral<char>					{ static const bool value = true;};
	template <> struct is_integral<char16_t>				{ static const bool value = true;};
	template <> struct is_integral<char32_t>				{ static const bool value = true;};
	template <> struct is_integral<wchar_t>					{ static const bool value = true;};
	template <> struct is_integral<signed char>				{ static const bool value = true;};
	template <> struct is_integral<short int>				{ static const bool value = true;};
	template <> struct is_integral<int>						{ static const bool value = true;};
	template <> struct is_integral<long int>				{ static const bool value = true;};
	template <> struct is_integral<long long int>			{ static const bool value = true;};
	template <> struct is_integral<unsigned char>			{ static const bool value = true;};
	template <> struct is_integral<unsigned short int>		{ static const bool value = true;};
	template <> struct is_integral<unsigned int>			{ static const bool value = true;};
	template <> struct is_integral<unsigned long int>		{ static const bool value = true;};
	template <> struct is_integral<unsigned long long int>	{ static const bool value = true;};


	template <class InputIt1, class InputIt2>
  	bool lexicographical_compare (InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template <class InputIt1, class InputIt2, class Compare>
  	bool lexicographical_compare (InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2,*first1))
				return false;
			else if (comp(*first1, *first2))
				return true;
			first1++;
			first2++;
		}
		return (first2 != last2);
	}

	template <class InputIt1, class InputIt2>
	bool equal (InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		while (first1!=last1)
		{
			if (!(*first1 == *first2))
     			return false;
			first1++;
			first2++;
 		}
		return true;
	}

	template <class InputIt1, class InputIt2, class BinaryPredicate>
	bool equal (InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate pred)
	{
		while (first1!=last1)
		{
			if (!pred(*first1,*first2))
     			return false;
			++first1;
			++first2;
 		}
		return true;
	}

	template <class T1, class T2> struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;
		
		T1			first;
		T2			second;
	
		pair() : first(), second() {} //default
	
		template<class U, class V>
		pair (const pair<U, V>& pr) : first(pr.first), second(pr.second) {} //copy
		pair (const first_type& a, const second_type& b) : first(a), second(b) {} //initialization

		pair& operator= (const pair& pr) {first = pr.first; second = pr.second; return *this;}
	};

	template <class T1, class T2>
	pair<T1,T2> make_pair(T1 t, T2 u) {return pair<T1, T2>(t, u);}

	template <class T1, class T2>
	bool operator==(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template <class T1, class T2>
	bool operator!=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {return !(lhs == rhs);}

	template <class T1, class T2>
	bool operator< (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

	template <class T1, class T2>
	bool operator<=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {return (!(rhs < lhs));}

	template <class T1, class T2>
	bool operator> (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {return (rhs < lhs);}

	template <class T1, class T2>
	bool operator>=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {return (!(lhs < rhs));}
}

#endif
