#include "containers/vector.hpp"
#include <vector>
#include <iostream>
#include <iterator>

int main(void)
{
	ft::vector<int>     ft_vector_int;
	std::vector<int>    std_vector_int;

	ft_vector_int.push_back(123);
	ft_vector_int.push_back(456);
	ft_vector_int.push_back(789);

	std_vector_int.push_back(123);
	std_vector_int.push_back(456);
	std_vector_int.push_back(789);

	// ft::vector<int>::iterator	ft_it = int_vector.begin();
	// std::vector<int>::iterator	std_it = std_vector_int.begin();

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