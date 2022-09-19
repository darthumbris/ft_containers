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
	#include "../containers/vector.hpp"
	#include "../containers/map.hpp"
	#include "../containers/set.hpp"
	#include "../containers/stack.hpp"
	std::string	output = "test/out_ft";
#endif

#endif