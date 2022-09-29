#include "test_header.hpp"
#include "test_vector.cpp"
#include "test_map.cpp"
#include "test_stack.cpp"
#include "test_set.cpp"

// #include "../includes/containers/vector.hpp"
// #include "../includes/containers/map.hpp"
// #include "../includes/utils/utils.hpp"
// # define MAX_SEED 1

// #include <array>
// #include <vector>
// #include <map>
// #include <set>
// #include <stack>
// #include <deque>
// #include <fstream>
// #include <execinfo.h>
// #include <iomanip>
// #include <sys/time.h>
// #include <sstream>
// #include <unistd.h>
// #include <iostream>
// #include <csignal>
// #include <unistd.h>
// #include <fcntl.h>

// const std::string GREEN = "\x1B[1;32m";
// const std::string REDD = "\x1B[1;31m";
// const std::string YELLOW = "\x1B[1;33m";
// const std::string WHITE = "\x1B[1;39m";
// const std::string RESET = "\033[0m";

// volatile static time_t g_start1;
// volatile static time_t g_start2;
// volatile static time_t g_end1;
// volatile static time_t g_end2;

// int _ratio = 1000;

// int _test_passed_cnt = 0;

// time_t timer() {
// 	struct timeval start = {};
// 	gettimeofday(&start, nullptr);
// 	time_t msecs_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
// 	return msecs_time;
// }

// std::string get_leak_string(std::string s) {
// 	std::string tmp;
// 	int idx = s.find("total leaked bytes");
// 	for (; s[idx] != '\n' ; --idx) {}
// 	int edx = idx + 1;
// 	for (; s[edx] != '\n' ; ++edx) {}

// 	return s.substr(++idx, edx - 101);
// }

// std::string exec(const char* cmd) {
// 	char buffer[128];
// 	std::string result = "";
// 	FILE* pipe = popen(cmd, "r");
// 	if (!pipe) throw std::runtime_error("popen() failed!");
// 	try {
// 		while (fgets(buffer, sizeof buffer, pipe) != NULL) {
// 			result += buffer;
// 		}
// 	} catch (...) { pclose(pipe); throw; }
// 	pclose(pipe);
// 	return result;
// }

// void printElement(std::string t)
// {
// 	if (t == "OK")
// 	    t = GREEN + t + RESET;
// 	else if (t == "FAILED") t = REDD + t + RESET;
// 	std::cout << std::left << std::setw(30) << std::setfill(' ') << t;
// }

// int leaks_test(pid_t pid) {
// 	std::string a = "leaks ";
// 	a += std::to_string(static_cast<int>(pid));
// 	usleep(50);
// 	std::string s = get_leak_string(exec(a.c_str()));

// 	if (s.find("0 leaks for 0 total leaked bytes") != std::string::npos) {
// 		printElement(GREEN + "CLEAR" + RESET);
// 		return (0);
// 	}
// 	else {
// 	    printElement(REDD + "LEAKS" + RESET);
// 	    return (1);
// 	}
// }

// void outputCurrentResult(std::string test_name, int num_tests) {
//     std::cout << std::endl <<  YELLOW + test_name << " RESULT: " << _test_passed_cnt << "/" << num_tests << RESET << std::endl;
// }

// void outputTotalResult(int num_passed, int num_tests) {
//     std::cout << std::endl <<  YELLOW << "TOTAL RESULT: " << num_passed << "/" << num_tests << RESET << std::endl;
// }

// int run_bool_unit_test(std::string test_name, bool (func1)()) {
//     int ret = 0;
//     time_t t1;
//     time_t t2;
//     bool res;

// 	printElement(test_name);
// 	res = func1();
// 	if (res) {
// 	    printElement("OK");
// 	    ret = 0;
// 	}
// 	else {
// 	    printElement("FAILED");
// 	    ret = 1;
// 	}
// 	t1 = g_end1 - g_start1, t2 = g_end2 - g_start2;
// 	(t1 >= t2) ? printElement(GREEN + std::to_string(t2) + "ms" + RESET) : printElement(REDD + std::to_string(t2) + "ms" + RESET);
// 	(t1 > t2) ? printElement(REDD + std::to_string(t1) + "ms" + RESET) : printElement(GREEN + std::to_string(t1) + "ms" + RESET);
// 	std::cout << std::endl;

//     return ret;
// }

// bool iterator_traits_test()
// {
// 	std::cout << std::endl;
// 	std::vector<std::string> res;
// 	std::vector<std::string> res2;
// 	g_start1 = g_end1 = timer();

// 	res.push_back(typeid(std::vector<int>::iterator::iterator_category).name());
// 	res.push_back(typeid(std::vector<int>::iterator::value_type).name());
// 	res.push_back(typeid(std::vector<int>::iterator::difference_type).name());
// 	res.push_back(typeid(std::vector<int>::iterator::iterator_type).name());
// 	res.push_back(typeid(std::vector<int>::iterator::pointer).name());
// 	res.push_back(typeid(std::vector<int>::iterator::reference).name());
// 	res.push_back(typeid(std::vector<int>::reverse_iterator::iterator_category).name());
// 	res.push_back(typeid(std::vector<int>::reverse_iterator::value_type).name());
// 	res.push_back(typeid(std::vector<int>::reverse_iterator::difference_type).name());
// 	res.push_back(typeid(std::vector<int>::reverse_iterator::pointer).name());
// 	res.push_back(typeid(std::vector<int>::reverse_iterator::reference).name());

// 	res2.push_back(typeid(ft::vector<int>::iterator::iterator_category).name());
// 	res2.push_back(typeid(ft::vector<int>::iterator::value_type).name());
// 	res2.push_back(typeid(ft::vector<int>::iterator::difference_type).name());
// 	res2.push_back(typeid(ft::vector<int>::iterator::iterator_type).name()); //here
// 	res2.push_back(typeid(ft::vector<int>::iterator::pointer).name());
// 	res2.push_back(typeid(ft::vector<int>::iterator::reference).name());
// 	res2.push_back(typeid(ft::vector<int>::reverse_iterator::iterator_category).name());
// 	res2.push_back(typeid(ft::vector<int>::reverse_iterator::value_type).name());
// 	res2.push_back(typeid(ft::vector<int>::reverse_iterator::difference_type).name());
// 	res2.push_back(typeid(ft::vector<int>::reverse_iterator::pointer).name());
// 	res2.push_back(typeid(ft::vector<int>::reverse_iterator::reference).name());

// 	std::vector<std::string>::iterator it;
// 	std::vector<std::string>::iterator it2 = res2.begin();
// 	int i = 0;
// 	for (it = res.begin(); it != res.end(); it++, i++, it2++)
// 	{
// 		std::cout << "std: " << *it << " ft: " << *it2 << std::endl;
// 		if (*it != *it2)
// 			std::cout << "i: " << i << " std: " << *it << " ft: " << *it2 << std::endl;
// 	}
// 	// std::cout << std::endl;
// 	// for (std::vector<std::string>::iterator it = res2.begin(); it != res2.end(); it++)
// 	// 	std::cout << "res2: " << *it << std::endl;
// 	return res == res2;
// }

class Timer
{
public:

	typedef std::chrono::high_resolution_clock		clock;
	typedef std::chrono::microseconds				us;

	Timer() {_start_time = clock::now();}
	~Timer() {}

	void stop()
	{
		std::chrono::time_point<clock>	end_time = clock::now();
		long long start = std::chrono::time_point_cast<us>(_start_time).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<us>(end_time).time_since_epoch().count();
		double ms = (end - start) * 0.001;
		std::cout << ms << std::endl;
	}

private:
	std::chrono::time_point<clock> _start_time;
};

enum	containers
{
	VECTOR,
	MAP,
	STACK,
	SET,
	INVALID
};

int get_container(std::string& container)
{
	if (container == "vector")
		return VECTOR;
	else if (container == "map")
		return MAP;
	else if (container == "stack")
		return STACK;
	else if (container == "set")
		return SET;
	return INVALID;
}

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		std::cerr << "Usage: ./test seed container" << std::endl;
		std::cerr << "Provide a seed and container please" << std::endl;
		return 1;
	}
	int	seed = atoi(argv[1]);
	std::string	container = argv[2];

	std::string output_file = "test/" + container +  "/" + output;
	std::ofstream	test_file(output_file, std::ios_base::trunc);

	Timer timer;

	test_file << "seed: " << seed << std::endl;
	// seed = 2265;
	// seed = 4198;
	int	current_seed = seed;
	for (int i = 0; i < MAX_SEED; i++)
	{
		switch (get_container(container))
		{
		case VECTOR:
			if (i % 2 == 0)
				test_vector<ft::vector<std::string> >(current_seed, test_file);
			else
				test_vector<ft::vector<int> >(current_seed, test_file);
			break;
		case MAP:
			test_map<ft::map<int, std::string> >(current_seed, test_file);
			break;
		case STACK:
			test_stack<ft::stack<int > >(current_seed, test_file);
			break;
		case SET:
			test_set<ft::set<int> >(current_seed, test_file);
			break;
		default:
			std::cerr << "container should be: vector, map, stack or set. Instead got: " << container << std::endl;
			return 1;
			break;
		}
		current_seed++;
	}
	// timer.stop();
	// system ("leaks -q ft_containers");
	return 0;
}
