#include "containers/vector.hpp"
#include <vector>
#include <iostream>
#include <map>
#include "containers/map.hpp"
#include "utils/redblacktree.hpp"
// #include <iterator>


//TODO make some proper tests
int main(void)
{
	ft::vector<int>     ft_vector_int;
	ft::vector<int>		ft_vector_int_copy;
	ft::vector<int>		vector_int_z;
	std::vector<int>    std_vector_int;

	ft::map<int, int>	ft_map_int_int;
	std::map<int, int>	std_map_int_int;

	// std::cout << "max_size map: " << ft_map_int_int.max_size() << std::endl;
	// std::cout << "max_size map: " << std_map_int_int.max_size() << std::endl;

	ft_map_int_int.insert(ft::make_pair(12, 24));
	ft_map_int_int.insert(ft::make_pair(13, 26));
	ft_map_int_int.insert(ft::make_pair(14, 28));
	ft_map_int_int.insert(ft::make_pair(15, 30));

	ft_vector_int.push_back(12);
	ft_vector_int.push_back(13);
	ft_vector_int.push_back(14);
	ft_vector_int.push_back(15);
	ft_vector_int.push_back(16);
	ft_vector_int.push_back(17);
	ft_vector_int.push_back(18);

	vector_int_z = ft_vector_int;

	ft_vector_int_copy.resize(10);

	ft_vector_int_copy.assign(vector_int_z.begin(), vector_int_z.end() - 2);

	for (size_t i = 0; i < ft_vector_int_copy.size(); i++)
		ft_vector_int_copy.pop_back();
	ft_vector_int_copy.pop_back();
	ft_vector_int_copy.pop_back();
	ft_vector_int_copy.pop_back();
	std::cout << "popppp" << std::endl;
	ft_vector_int_copy.pop_back();
	// for (auto it = ft_map_int_int.begin(); it != ft_map_int_int.end(); it++)
	// 	std::cout << "ft: key of map: " << it->first << "and corresponding value: " << it->second << std::endl;

	// std_map_int_int.insert(std::make_pair(12, 24));
	// std_map_int_int.insert(std::make_pair(13, 26));
	// std_map_int_int.insert(std::make_pair(14, 28));
	// std_map_int_int.insert(std::make_pair(15, 30));

	// for (auto it = std_map_int_int.begin(); it != std_map_int_int.end(); it++)
	// 	std::cout << "std: key of map: " << it->first << "and corresponding value: " << it->second << std::endl;

	// std::cout << "size of ft map now: " << ft_map_int_int.size() << " and size of std map now: " << std_map_int_int.size() << std::endl;

	ft_vector_int.push_back(123);
	ft_vector_int.push_back(456);
	ft_vector_int.push_back(789);

	std_vector_int.push_back(123);
	std_vector_int.push_back(456);
	std_vector_int.push_back(789);

	for (ft::vector<int>::iterator	ft_it = ft_vector_int.begin(); ft_it != ft_vector_int.end(); ft_it++)
		std::cout << *ft_it << std::endl;

	for (std::vector<int>::iterator	std_it = std_vector_int.begin(); std_it != std_vector_int.end(); std_it++)
		std::cout << *std_it << std::endl;

	std::cout << "int_vector.size(): " << ft_vector_int.size() << std::endl;
	std::cout << "int_vector.size(): " << std_vector_int.size() << std::endl;
	std::cout << "ft::vector<int> max_size(): " << ft_vector_int.max_size() << std::endl;
	std::cout << "std::vector<int> max_size(): " << std_vector_int.max_size() << std::endl;
	return 0;
}