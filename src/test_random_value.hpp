#include "test_header.hpp"

#ifndef TEST_RANDOM_VALUE_HPP
# define TEST_RANDOM_VALUE_HPP

// #include <iostream>
// #include <cstdlib>
// #include <string>

# define KEY	512

template <typename _vector>
void	test_print(const _vector& p, std::ofstream& test_file)
{
	test_file << "empty: " << p.empty() << std::endl;
	test_file << "size: " << p.size() << std::endl;
	test_file << "capacity: " << p.capacity() << std::endl;
	test_file << "max_size: " << p.max_size() << std::endl;
	if (!p.empty())
	{
		test_file << "content: " << std::endl;
		for (typename _vector::const_iterator it = p.begin(); it != p.end(); it++)
			test_file << *it << std::endl;
		test_file << "reverse: " << std::endl;
		for (typename _vector::const_reverse_iterator it = p.rbegin(); it != p.rend(); it++)
			test_file << *it << std::endl;
		test_file << "front(): " << p.front() << std::endl;
		test_file << "back(): " << p.back() << std::endl;
	}
}

template <typename T>
class _const_test {
	public:
		typedef T	value_type;

		_const_test(void) : value() { };
		_const_test(value_type src) : value(src) { };
		_const_test(_const_test const &src) : value(src.value) { };
		~_const_test(void) { };
        
		void print(std::ostream &o) { o << "_const_test::print called [" << this->value << "]"; }
		void print(std::ostream &o) const { o << "_const_test::print const called [" << this->value << "]"; }
		_const_test &operator=(value_type src) { this->value = src; return *this; };
		_const_test &operator=(_const_test const &src) {
			this->value = src.value;
			return *this;
		}
		value_type	getValue(void) const { return this->value; }

		operator value_type(void) const
        {
			return value_type(this->value);
		}
        
	private:
		value_type	value;
};

template <typename T>
std::ostream	&operator<<(std::ostream &o, _const_test<T> const &tclass)
{
    tclass.print(o);
	return o;
}

template <typename T>
std::ostream	&operator<<(std::ostream &o, _const_test<T> &tclass)
{
    tclass.print(o);
	return o;
}

template <typename T>
T rdm_val()
{
    return (T());
}

template <>
std::string rdm_val<std::string>()
{
    std::string default_val[24] =
    {
        "Take me with you.",
        "It's four in the morning. What are you doing?",
        "Why are you being so stubborn?",
        "I just wanted to do something good for once.",
        "How many times have I told you? You can't visit me here.",
        "I hope to repay your kindness someday.",
        "How did you get this scar?",
        "I thought you... I saw you get shot.",
        "I bought two. Here.",
        "I don't know. Shut up. I'm not blushing.",
        "Anything to eat around here?",
        "You want me? Here I am.",
        "You know you aren't allowed in here, right?",
        "Just let me do this for you.",
        "This isn't just about you. It's about what's best for all of us.",
        "Could you be happy here with me?",
        "Life is about more than just surviving.",
        "What was that for?",
        "Is... that my shirt you're wearing?",
        "Why can't you let me in? What are you so afraid of?",
        "Give me one good reason why I should believe you.",
        "I don't know how you do this every day...",
        "Your plan's gonna get us all killed, and you know it.",
        "I'm not even going to pretend to understand what you're talking about."
    };
    return (std::string(default_val[std::rand() % 18]));
}

template <>
int rdm_val<int>()
{
    return (int(std::rand() % KEY));
}

template <>
_const_test<int>
rdm_val<_const_test<int> >()
{
    return (_const_test<int>(rdm_val<int>()));
}

#endif