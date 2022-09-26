#include "test_header.hpp"

#ifndef TEST_RANDOM_VALUE_HPP
# define TEST_RANDOM_VALUE_HPP

# define KEY	512

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
    std::string default_val[41] =
    {
        "This was a triumph.",
        "I'm making a note here: HUGE SUCCESS.",
        "It's hard to overstate my satisfaction.",
        "Aperture Science",
        "We do what we must because we can.",
        "For the good of all of us.",
        "Except the ones who are dead.",
        "But there's no sense crying over every mistake.",
        "You just keep on trying till you run out of cake.",
        "And the Science gets done.",
        "And you make a neat gun.",
        "For the people who are still alive.",
        "I'm not even angry.",
        "I'm being so sincere right now.",
        "Even though you broke my heart. And killed me. And tore me to pieces.",
        "And threw every piece into a fire.",
        "As they burned it hurt because I was so happy for you!",
        "Now these points of data make a beautiful line.",
        "And we're out of beta.",
        "We're releasing on time.",
        "So I'm GLaD. I got burned.",
        "Think of all the things we learned",
        "Go ahead and leave me.",
        "I think I prefer to stay inside.",
		"Maybe you'll find someone else to help you.",
		"Maybe Black Mesa",
		"THAT WAS A JOKE. HAHA. FAT CHANCE.",
		"Anyway, this cake is great.",
		"It's so delicious and moist.",
		"Look at me still talking when there's Science to do.",
		"When I look out there, it makes me GLaD I'm not you.",
		"I've experiments to run.",
		"There is research to be done.",
		"On the people who are still alive.",
		"And believe me I am still alive.",
		"I'm doing Science and I'm still alive.",
		"I feel FANTASTIC and I'm still alive.",
		"While you're dying I'll be still alive.",
		"And when you're dead I will be still alive.",
		"STILL ALIVE",
		"STILL ALIVE"
    };
    return (std::string(default_val[std::rand() % 20]));
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
