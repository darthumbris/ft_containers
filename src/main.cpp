#include "containers/vector.hpp"
#include <vector>
#include <iostream>

int main(void)
{
    ft::vector<int> int_vector;
    std::vector<int>    std_vector_int;

    int_vector.push_back(123);
    int_vector.push_back(456);
    int_vector.push_back(789);
    std::cout << int_vector.at(0) << std::endl;
    std::cout << int_vector.at(1) << std::endl;
    std::cout << int_vector.at(2) << std::endl;
    std::cout << "ft::vector<char> max_size(): " << int_vector.max_size() << std::endl;
    std::cout << "std::vector<char> max_size(): " << std_vector_int.max_size() << std::endl;
    return 0;
}