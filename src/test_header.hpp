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
	#include <stack>
	namespace ft = std;
	std::string	output = "out_std.log";
#else
	#include "../includes/containers/vector.hpp"
	#include "../includes/containers/map.hpp"
	#include "../includes/containers/set.hpp"
	#include "../includes/containers/stack.hpp"
	std::string	output = "out_ft.log";
#endif

#endif
