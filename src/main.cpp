#include "containers/vector.hpp"
#include <vector>
#include <iostream>
#include <map>
#include "containers/map.hpp"
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

// template <>
// ft::_const_test<int>
// rdm_val<ft::_const_test<int> >()
// {
//     return (ft::_const_test<int>(rdm_val<int>()));
// }

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

// template <>
// ft::pair<const ft::_const_test<int>, ft::_const_test<std::string> >
// rdm_val<ft::pair<const ft::_const_test<int>, ft::_const_test<std::string> > >()
// {
//     return ft::pair<const ft::_const_test<int>, std::string>(rdm_val<int>(), rdm_val<std::string>());
// }

// template <>
// std::pair<const ft::_const_test<int>, ft::_const_test<std::string> >
// rdm_val<std::pair<const ft::_const_test<int>,ft::_const_test<std::string> > >()
// {
//     return std::pair<const ft::_const_test<int>, std::string>(rdm_val<int>(), rdm_val<std::string>());
// }


//TODO make some proper tests
int main(void)
{
	std::srand(42);


	ft::map<int, std::string>	ft_x;
	ft::map<int, std::string>	ft_y;
	ft::map<int, std::string>	ft_z;
	// ft::map<int, std::string>	ft_w;
	// ft::map<int, std::string>	ft_y;
	std::map<int, std::string>	std_x;
	std::map<int, std::string>	std_y;
	std::map<int, std::string>	std_z;
	// std::map<int, std::string>	std_w;
	// std::map<int, std::string>	std_u;

	// std::cout << "max_size map: " << ft_map_int_int.max_size() << std::endl;
	// std::cout << "max_size map: " << std_map_int_int.max_size() << std::endl;

	for (int i = 0; i < 512; i++)
	{
		ft::pair<const int, std::string> ft_value = rdm_val<typename ft::map<int, std::string>::value_type>();
		ft_z.insert(ft_value);
		std_z.insert(std::make_pair(ft_value.first, ft_value.second));
	}
	ft::map<int, std::string> ft_w(ft_z.begin(), ft_z.end());
	ft::map<int, std::string>	ft_u(ft_z);
	// for (int i = 0; i < 512; i++)
	// 	std_x.insert(rdm_val<typename std::map<int, std::string>::value_type>());
	std::map<int, std::string> std_w(std_z.begin(), std_z.end());
	std::map<int, std::string>	std_u(std_z);

	ft_x = ft_u;
	ft_y = ft_w;
	std_x = std_u;
	std_y = std_w;

	ft::map<int, std::string>::iterator ft_it = ft_y.begin();
	std::map<int, std::string>::iterator std_it = std_y.begin();
	for (; std_it != std_y.end(); std_it++, ft_it++)
	{
		// std::cout << std_it->first << " => " << std_it->second << std::endl;
		std::cout << ft_it->first << " => " << ft_it->second << std::endl;
		// if (std_it->first != ft_it->first)
		// {
		// 	std::cout << "difference found" << std::endl;
		// 	break ;
		// }
	}

	// ft_it = ft_y.begin();
	// std_it = std_y.begin();
	// for (; std_it != std_y.end(); std_it++, ft_it++)
	// {
	// 	// std::cout << std_it->second << " == " << ft_it->second << std::endl;
	// 	if (std_it->second != ft_it->second)
	// 	{
	// 		std::cout << "difference found" << std::endl;
	// 		break ;
	// 	}
	// }

	ft_it = ft_y.begin();
	std_it = std_y.begin();

	int	erase_pos = 3;

	if (!ft_y.empty() && ft_y.size() > 5)
	{
		for (int i = 0; i < erase_pos; i++)
		{
			ft_it++;
			std_it++;
		}
	}
	ft_y.erase(ft_it);
	std_y.erase(std_it);

	

	std::cout << "\n=============Erasing==========" << std::endl;

	ft_it = ft_y.begin();
	std_it = std_y.begin();
	for (; std_it != std_y.end(); std_it++, ft_it++)
	{
		// std::cout << std_it->first << " => " << std_it->second << std::endl;
		std::cout << ft_it->first << " => " << ft_it->second << std::endl;
		// if (std_it->first != ft_it->first)
		// {
		// 	std::cout << "difference found" << std::endl;
		// 	break ;
		// }
	}


	// ft_it = ft_y.begin();
	// std_it = std_y.begin();
	// for (; std_it != std_y.end(); std_it++, ft_it++)
	// {
	// 	// std::cout << std_it->second << " == " << ft_it->second << std::endl;
	// 	if (std_it->second != ft_it->second)
	// 	{
	// 		std::cout << "difference found" << std::endl;
	// 		break ;
	// 	}
	// }

	// std_it = std_y.begin();
	// for (auto it = ft_y.begin(); it != ft_y.end() && std_it != std_y.end(); it++, std_it++)
	// {
	// 	std::cout << it->first << "\t=> " << it->second << "\t\tstd: " << std_it->first << "\t=> " << std_it->second << std::endl;
	// }


	// std::cout << "\n=============" << std::endl;

	// for (auto it = std_map_str.begin(); it != std_map_str.end(); it++)
	// 	std::cout << it->first << " => " << it->second << std::endl;

	// // std::map<int, std::string>::iterator it;
	// auto it2 = std_map_str.begin();
	// for (int i = 0; i < iterate; i++)
	// 	it2++;
	// std_map_str.erase(it2);

	// for (auto it = std_map_str.begin(); it != std_map_str.end(); it++)
	// 	std::cout << it->first << " => " << it->second << std::endl;

	// ft_map_str

	// ft::map<int, std::string>	ft_map_copy(ft_map_str);

	// if (ft_map_str < ft_map_copy)
	// 	std::cout << "ok" << std::endl;

	// ft_vector_int.push_back(12);
	// ft_vector_int.push_back(13);
	// ft_vector_int.push_back(14);
	// ft_vector_int.push_back(15);
	// ft_vector_int.push_back(16);
	// ft_vector_int.push_back(17);
	// ft_vector_int.push_back(18);

	// vector_int_z = ft_vector_int;

	// ft_vector_int_copy.resize(10);

	// ft_vector_int_copy.assign(vector_int_z.begin(), vector_int_z.end() - 2);

	// for (size_t i = 0; i < ft_vector_int_copy.size(); i++)
	// 	ft_vector_int_copy.pop_back();
	// ft_vector_int_copy.pop_back();
	// ft_vector_int_copy.pop_back();
	// ft_vector_int_copy.pop_back();
	// std::cout << "popppp" << std::endl;
	// ft_vector_int_copy.pop_back();
	// for (auto it = ft_map_int_int.begin(); it != ft_map_int_int.end(); it++)
	// 	std::cout << "ft: key of map: " << it->first << "and corresponding value: " << it->second << std::endl;

	// std_map_int_int.insert(std::make_pair(12, 24));
	// std_map_int_int.insert(std::make_pair(13, 26));
	// std_map_int_int.insert(std::make_pair(14, 28));
	// std_map_int_int.insert(std::make_pair(15, 30));

	// for (auto it = std_map_int_int.begin(); it != std_map_int_int.end(); it++)
	// 	std::cout << "std: key of map: " << it->first << "and corresponding value: " << it->second << std::endl;

	// std::cout << "size of ft map now: " << ft_map_int_int.size() << " and size of std map now: " << std_map_int_int.size() << std::endl;

	// ft_vector_int.push_back(123);
	// ft_vector_int.push_back(456);
	// ft_vector_int.push_back(789);

	// std_vector_int.push_back(123);
	// std_vector_int.push_back(456);
	// std_vector_int.push_back(789);

	// for (ft::vector<int>::iterator	ft_it = ft_vector_int.begin(); ft_it != ft_vector_int.end(); ft_it++)
	// 	std::cout << *ft_it << std::endl;

	// for (std::vector<int>::iterator	std_it = std_vector_int.begin(); std_it != std_vector_int.end(); std_it++)
	// 	std::cout << *std_it << std::endl;

	// std::cout << "int_vector.size(): " << ft_vector_int.size() << std::endl;
	// std::cout << "int_vector.size(): " << std_vector_int.size() << std::endl;
	// std::cout << "ft::vector<int> max_size(): " << ft_vector_int.max_size() << std::endl;
	// std::cout << "std::vector<int> max_size(): " << std_vector_int.max_size() << std::endl;
	return 0;
}