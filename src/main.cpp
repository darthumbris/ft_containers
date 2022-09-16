#include "containers/vector.hpp"
#include <vector>
#include <iostream>
#include <map>
#include <set>
// #include "containers/map.hpp"
#include "containers/set.hpp"
#include "utils/redblacktree.hpp"
#include <iterator>

template <typename _Type>
_Type rdm_val()
{
    return (_Type());
}
/**
 * @brief Generate a random string
 */
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


/**
 * @brief Generate a random UINT
 *
 */
template <>
int rdm_val<int>()
{
    return (int(std::rand() % 1024));
}

template <>
std::pair<const int, std::string>
rdm_val<std::pair<const int, std::string> >()
{
    return std::pair<const int, std::string>(rdm_val<int>(), rdm_val<std::string>());
}

template <>
ft::pair<const int, std::string>
rdm_val<ft::pair<const int, std::string> >()
{
    return ft::pair<const int, std::string>(rdm_val<int>(), rdm_val<std::string>());
}


//TODO make some proper tests
int main(void)
{
	
	return 0;
}