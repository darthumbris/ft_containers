#ifndef TEST_HEADER_HPP
# define TEST_HEADER_HPP

#include <string>
#include <iostream>
#include <fstream>

# define MAX_SEED 8

#if STD_TEST
	#include <vector>
	#include <map>
	#include <set>
	namespace ft = std;
	std::string	output = "test/out_std";
#else
	#include "../includes/containers/vector.hpp"
	#include "../includes/containers/map.hpp"
	#include "../includes/containers/set.hpp"
	#include "../includes/containers/stack.hpp"
	std::string	output = "test/out_ft";
#endif

#endif