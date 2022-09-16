#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "../iterators/reverse_iterator.hpp"
# include "../utils/utils.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{		

	public: //typedefs

		typedef Allocator										allocator_type;
		typedef unsigned long									size_type;
		typedef T												value_type;
		typedef long											difference_type;
		typedef value_type&										reference;
		typedef const value_type&								const_reference;
		typedef typename Allocator::pointer						pointer;
		typedef typename Allocator::const_pointer				const_pointer;
		typedef ft::iterator<T>									iterator;
		typedef ft::iterator<const T, const_pointer, const_reference>	const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

	private: // variables

		value_type*												_array;
		allocator_type											_alloc;
		size_type												_alloc_size;
		size_type												_size;

	private: // private member functions
		//Exception
		class length_error: public std::exception {
		private:
			const char* _msg;
		public:
			length_error(const char* msg) : _msg(msg) {}
			virtual const char* what() const throw() {return _msg;}
		};

		//Exception
		class out_of_range: public std::exception {
		private:
			const char* _msg;
		public:
			out_of_range(const char* msg) : _msg(msg) {}
			virtual const char* what() const throw() {return _msg;}
		};

		void					increaseAllocSize(size_type n)
		{
			if (n < _alloc_size)
				return ;
			if (n > max_size())
				throw length_error("Reserver error .");
			value_type* temp = _alloc.allocate(n);
			for (size_type i = 0; i < _size; i++)
			{
				_alloc.construct(temp + i, _array[i]);
				_alloc.destroy(_array + i);
			}
			if (_alloc_size)
				_alloc.deallocate(_array, _alloc_size);
			_alloc_size = n;
			_array = temp;
		}

		template<class InputIt, class OutputIt>
		OutputIt copy_erase (InputIt first, InputIt last, OutputIt result)
		{
			while (first!=last)
			{
				*result = *first;
				result++;
				first++;
			}
			return result;
		}

		template<class InputIt>
		size_type	distance(InputIt& first, InputIt& last)
		{
			size_type	count = 0;
			for (InputIt it = first; it != last; it++)
				count++;
			return count;
		}

	public: //public member functions

		explicit	vector(const allocator_type& alloc = allocator_type()) // default    
						: _array(NULL), _alloc(alloc), _alloc_size(0), _size(0) {} 

		explicit	vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator()) // fill
		{
			_size = count;
			_alloc_size = count;
			_alloc = alloc;
			_array = _alloc.allocate(count);
			for (size_type i = 0; i < count; i++)
				_alloc.construct(_array + i, value);
		}

		template <class InputIt>
		vector(InputIt first, InputIt last, const Allocator& alloc = Allocator(),
			typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = true) // range 
		{
			size_type	diff = last - first;
			_array = _alloc.allocate(diff);
			for (size_type i = 0; i < diff; i++)
			{
				_alloc.construct(_array + i, *first);
				first++;
			}
			_size = diff;
			_alloc_size = diff;
			_alloc = alloc;
		}

		vector(const vector& other)// copy 
		{
			_size = 0;
			_alloc_size = 0;
			*this = other;
		}
		
		~vector() 
		{
			for(size_type i = 0; i < _size; i++)
				_alloc.destroy(_array + i);
			if (_alloc_size)
				_alloc.deallocate(_array, _alloc_size);
		}

		template <class InputIt>
		typename ft::enable_if<!ft::is_integral<InputIt>::value,void>::type
								assign(InputIt first, InputIt last) 
		{
			size_type	diff = distance(first, last);
			clear();
			increaseAllocSize(diff);
			while (first != last)
				push_back(*first++);
		}
		void 					assign(size_type count, const T& value) 
		{
			clear();
			increaseAllocSize(count);
			for (size_t i = 0; i < count; i++)
				push_back(value);
		}
		allocator_type			get_allocator() const {return _alloc;} 
		vector& 				operator=(const vector& other) 
		{
			if (this != &other)
			{
				clear();
				if (_alloc_size)
					_alloc.deallocate(_array, _alloc_size);
				_size = other._size;
				_alloc_size = other._alloc_size;
				_alloc = other._alloc;
				if (_alloc_size)
					_array = _alloc.allocate(other._alloc_size);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(_array + i, other._array[i]);
			}
			return *this;
		}

		// Element Access
		reference 				at(size_type pos)
		{
			if (pos > size()) 
				throw(out_of_range("vector"));
			return _array[pos];
		}
		const_reference			at(size_type pos) const {return at(pos);}
		reference 				operator[](size_type pos)
		{
			if (pos > size()) 
				throw(out_of_range("vector [] index out of bounds"));
			return _array[pos];
		}
		const_reference 		operator[](size_type pos) const {return operator[](pos);}
		reference				front() {return _array[0];}
		const_reference			front() const {return _array[0];}
		reference				back() {return _array[_size - 1];}
		const_reference			back() const {return _array[_size - 1];}
		T*						data() {return _array;}
		const T*				data() const {return _array;}

		// Iterators
		iterator				begin() _NOEXCEPT {return iterator(&_array[0]);}
		const_iterator			begin() const _NOEXCEPT {return const_iterator(&_array[0]);}
		iterator				end() _NOEXCEPT {return iterator(&_array[_size]);}
		const_iterator			end() const _NOEXCEPT {return const_iterator(&_array[_size]);}
		reverse_iterator		rbegin() _NOEXCEPT {return reverse_iterator(end());}
		const_reverse_iterator	rbegin() const _NOEXCEPT {return const_reverse_iterator(end());}
		reverse_iterator		rend() _NOEXCEPT {return reverse_iterator(begin());}
		const_reverse_iterator	rend() const _NOEXCEPT {return const_reverse_iterator(begin());}

		// Capacity
		bool					empty() const {return _size == 0;}
		size_type				size() const {return _size;}
		size_type				max_size() const {return std::min<size_type>(_alloc.max_size(), std::numeric_limits<difference_type>::max());}
		void					reserve(size_type new_cap) {increaseAllocSize(new_cap);}
		size_type				capacity() const {return _alloc_size;}
		
		// Modifiers
		template <class InputIt>
		typename ft::enable_if<!ft::is_integral<InputIt>::value,void>::type
								insert(iterator pos, InputIt first, InputIt last)
		{
			for (iterator it = first; it != last; it++)
			{
				pos = insert(pos, *it);
				pos++;
			}
		}
		iterator				insert(iterator pos, const T& value)
		{
			vector		tmp;
			size_type	index_pos = pos - begin();
			size_type	end_elem = end() - pos;

			tmp.assign(pos, end());
			_size = index_pos;
			push_back(value);
			for (size_type i = 0; i < end_elem; i++)
				push_back(tmp[i]);
			return (begin() + index_pos); 
		}
		void					insert(iterator pos, size_type count, const T& value)
		{
			for (size_type i = 0; i < count; i++)
			{
				pos = insert(pos, value);
				pos++;
			}
		}
		void					clear()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_array + i);
			_size = 0;
		}
		iterator				erase(iterator pos)
		{
			iterator p_pos = pos;

			if (pos + 1 == end())
				_alloc.destroy(&(*pos));
			else
			{
				for (int i = 0; i < end() - pos - 1; i++)
				{
					size_type j = pos - begin();
					_alloc.construct(&_array[j + i], _array[j + i + 1]);
					_alloc.destroy(&_array[j + i + 1]);
				}
			}
			_size--;
			return (p_pos);
		}
		iterator				erase(iterator first, iterator last)
		{
			copy_erase(last, end(), first);
			_size -= last - first;
			return first;
		}
		void					push_back(const T& value)
		{
			if (_alloc_size == 0)
				increaseAllocSize(1);
			else if (_size + 1 > _alloc_size)
				increaseAllocSize(_alloc_size * 2);
			_alloc.construct(_array + _size, value);
			_size++;
		}
		void					pop_back()
		{
			if (_size > 0)
			{
				_alloc.destroy(&back());
				_size--;
			}
		}
		void					resize(size_type count, T value = T())
		{
			if (count <= _size)
			{
				for (size_type i = count; i < _size; i++)
					_alloc.destroy(_array + i);
			}
			if (count > _size)
			{
				increaseAllocSize(count);
				for (size_type i = _size; i < count; i++)
					_alloc.construct(_array + i, value);
			}
			_size = count;
		}
		void					swap(vector& other)
		{
			value_type*		temp_array = _array;
			allocator_type	temp_alloc = _alloc;
			size_type		temp_alloc_size = _alloc_size;
			size_type		temp_size = _size;

			_array = other._array;
			_alloc = other._alloc;
			_alloc_size = other._alloc_size;
			_size = other._size;
			other._array = temp_array;
			other._alloc = temp_alloc;
			other._alloc_size = temp_alloc_size;
			other._size = temp_size;
		}
	};

	template <class T, class Alloc>
	bool	operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	template <class T, class Alloc>
	bool	operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return !(lhs == rhs);}
	template <class T, class Alloc>
	bool	operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template <class T, class Alloc>
	bool	operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return (!(rhs < lhs));}
	template <class T, class Alloc>
	bool	operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return (rhs < lhs);}
	template <class T, class Alloc>
	bool	operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return (!(lhs < rhs));}

	template <class T, class Alloc>
	void	swap(vector<T, Alloc>& lhs, vector<T,Alloc>& rhs) {lhs.swap(rhs);}
};
#endif
