#ifndef VECTOR_HPP
# define VECTOR_HPP


#include <memory>
#include "iterators/reverse_iterator.hpp"
#include "utils/utils.hpp"
#include <iostream>

namespace ft
{
	template <class T, class Allocator = std::allocator<T>>
	class vector
	{		

	protected: //protected typedefs

		typedef Allocator										allocator_type;
		typedef unsigned long									size_type;
		typedef T												value_type;
		typedef long											difference_type;
		typedef value_type&										reference;
		typedef const value_type&								const_reference;
		typedef typename Allocator::pointer						pointer;
		typedef typename Allocator::const_pointer				const_pointer;
		typedef ft::iterator<T>									iterator;
		typedef ft::iterator<T, const_pointer, const_reference>	const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

	private:
		value_type*												_array;
		allocator_type											_alloc;
		size_type												_alloc_size;
		size_type												_size;

		void					increaseAllocSize(size_type n)
		{
			if (n < _alloc_size)
				return ;
			_alloc_size = n;
			value_type* _temp = _alloc.allocate(_alloc_size);
			for (size_type i = 0; i < _size; i++)
			{
				_alloc.construct(&_temp[i], _array[i]);
				_alloc.destroy(&_array[i]);
			}
			_alloc.deallocate(_array, _alloc_size);
			_array = _temp;
		}

	public:

		explicit				vector(const allocator_type& alloc = allocator_type())
									: _array(NULL), _alloc(alloc), _alloc_size(0), _size(0) {} // default    //done

		explicit				vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator())
									: _array(NULL), _alloc(alloc), _alloc_size(count), _size(count) // fill //done
								{
									_alloc.allocate(_alloc_size);
									for (size_type i = 0; i < _size; i++)
										_alloc.construct(_array[i], value);
								}

		template <class InputIt>	vector(InputIt first, InputIt last, const Allocator& alloc = Allocator(),
									typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = true)
									: _array(NULL), _alloc(alloc), _alloc_size(0), _size(0) // range //done
								{
									size_type	size;
									for (Input it = first; it != last; it++, size++);
									_alloc_size = size;
									_size = _alloc_size;
									_alloc.allocate(_alloc_size);
									size_type	i = 0;
									for (Input it = first; it != last; it++, i++)
										_alloc.construct(&_array[i], *it);
								}

								vector(const vector& other) {*this = other;} // copy //done
		
								~vector() //done
								{
									if (_array != NULL)
									{
										clear();
										_alloc.deallocate(_array, _alloc_size);
									}
								}

		template <class InputIt>
		typename ft::enable_if<!ft::is_integral<InputIt>::value,void>::type assign(InputIt first, InputIt last) //done
		{
			clear();
			increaseAllocSize(std::distance(first, last));
			for (iterator it = first; it != last; it++)
				push_back(*it);
		} //done
		void 					assign(size_type count, const T& value) //done
		{
			clear();
			increaseAllocSize(count);
			for (size_t i = 0; i < count; i++)
				push_back(value);
		}
		allocator_type			get_allocator() const {return _alloc;} //done
		vector& 				operator=(const vector& other) //done
								{
									for (size_type i = 0; i < _size; i++)
										_alloc.destroy(&_array[i]);
									_alloc.deallocate(_array, _alloc_size);
									_size = other._size;
									_alloc_size = other._alloc_size;
									_array = _alloc.allocate(_alloc_size);
									_alloc = other._alloc;
									for (size_type i = 0; i < _size; i++)
										_alloc.construct(&other._array[i]);
									return *this;
								}

		// Element Access
		reference 				at(size_type pos) //done
		{
			if (pos > size()) 
				throw(std::out_of_range("vector"));
			return _array[pos];
		}
		const_reference			at(size_type pos) const //done
		{
			if (pos > size()) 
				throw(std::out_of_range("vector"));
			return _array[pos];
		}
		reference 				operator[](size_type pos) //done
		{
			if (pos > size()) 
				throw(std::out_of_range("vector"));
			return _array[pos];
		}
		const_reference 		operator[](size_type pos) const //done
		{
			if (pos > size()) 
				throw(std::out_of_range("vector"));
			return _array[pos];
		}
		reference				front() {return *_array[0];} //done
		const_reference			front() const {return *_array[0];} //done
		reference				back() {return *_array[_size - 1];} //done
		const_reference			back() const {return *_array[_size - 1];} //done
		T*						data() {return _array;} //done
		const T*				data() const {return _array;} //done

		// Iterators
		iterator				begin() {return iterator(&_array[0]);} //done
		const_iterator			begin() const {return const_iterator(&_array[0]);} //done
		iterator				end() {return iterator(&_array[_size - 1]);} //done
		const_iterator			end() const {return const_iterator(&_array[_size - 1]);} //done
		reverse_iterator		rbegin() {return reverse_iterator(end());} //done
		const_reverse_iterator	rbegin() const {return const_reverse_iterator(end());} //done
		reverse_iterator		rend() {return reverse_iterator(begin());} //done
		const_reverse_iterator	rend() const {return const_reverse_iterator(begin());} //done

		// Capacity
		bool					empty() const {return _size == 0;} //done
		size_type				size() const {return _size;} //done
		size_type				max_size() const {return std::min<size_type>(_alloc.max_size(), std::numeric_limits<difference_type>::max());} //done
		void					reserve(size_type new_cap) {increaseAllocSize(new_cap);} //done
		size_type				capacity() const {return _alloc_size;} //done
		
		// Modifiers
		template <class InputIt>
		typename ft::enable_if<!ft::is_integral<InputIt>::value,void>::type
								insert(iterator pos, InputIt first, InputIt last) //done
		{
			for (iterator it = first; it != last; it++)
			{
				pos = insert(pos, *it);
				pos++;
			}
		}
		iterator				insert(iterator pos, const T& value) //done
		{
			size_t start_pos = pos - begin();
			if (start_pos == end())
				push_back(value);
			else
			{
				value_type temp_val = val;
				int cur_pos = pos - begin();
				if (_size == _alloc_size)
				{
					if (_alloc_size == 0)
						increaseAllocSize(1);
					else
						increaseAllocSize(_alloc_size * 2);
					pos = begin() + cur_pos;
				}
				while(pos <= end()) //this moves every value after pos if pos is not at the end.
				{
					value_type temp = _array[cur_pos];
					_alloc.destroy(&_array[cur_pos]);
					_alloc.construct(&_array[cur_pos], temp_val);
					temp_val = temp;
					pos++;
					cur_pos++;
				}
				_size++;
			}
			return (begin() + start_pos);
		}
		void					insert(iterator pos, size_type count, const T& value) //done
		{
			for (size_t i = 0; i < count; i++)
				insert(pos + i, value);
		}
		void					clear() //done
		{
			for (std::size_t i = 0; i < _size; i++)
				_alloc.destroy(&_array[i]);
			_size = 0;
		}
		iterator				erase(iterator pos) //done
		{
			size_t start_pos = pos - begin();
			if (start_pos == end())
				pop_back();
			else
			{
				int cur_pos = pos - begin();
				while(pos <= end()) //this moves every value after pos if pos is not at the end.
				{
					value_type temp = _array[cur_pos + 1];
					_alloc.destroy(&_array[cur_pos]);
					_alloc.construct(&_array[cur_pos], temp);
					pos++;
					cur_pos++;
				}
				_size--;
			}
			return (start_pos);
		}
		iterator				erase(iterator first, iterator last) //done
		{
			for (iterator it = first; it != last; it++)
				erase(it);
			return it;
		}
		void					push_back(const T& value) //done
		{
			if (_size == _alloc_size)
				increaseAllocSize(_size + 1);
			_alloc.construct(&_array[_size], value);
			_size++;
		}
		void					pop_back() //done
		{
			_alloc.destroy(&_array[_size]);
			if (_size > 0)
				size--;
		}
		void					resize(size_type count, T value = T()) //done
		{
			if (count < _size)
			{
				for (size_t i = count; i < _size; i++)
					_alloc.destroy(&_array[i]);
			}
			else
			{
				if (count > _alloc_size)
					increaseAllocSize(count);
				for (size_t i = _size; i < count; i++)
					_alloc.construct(&_array[i], value);
			}
			_size = count;
		}
		void					swap(vector& other) //done
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
};

template <class T, class Allocator> bool operator==(const ft::vector<T,Allocator>& lhs, const ft::vector<T,Allocator>& rhs);
template <class T, class Allocator> bool operator!=(const ft::vector<T,Allocator>& lhs, const ft::vector<T,Allocator>& rhs);
template <class T, class Allocator> bool operator< (const ft::vector<T,Allocator>& lhs, const ft::vector<T,Allocator>& rhs);
template <class T, class Allocator> bool operator<=(const ft::vector<T,Allocator>& lhs, const ft::vector<T,Allocator>& rhs);
template <class T, class Allocator> bool operator> (const ft::vector<T,Allocator>& lhs, const ft::vector<T,Allocator>& rhs);
template <class T, class Allocator> bool operator>=(const ft::vector<T,Allocator>& lhs, const ft::vector<T,Allocator>& rhs);


#endif
