#include "test_header.hpp"
#include "test_vector.cpp"
#include "test_map.cpp"
#include "test_stack.cpp"
#include "test_set.cpp"

//TODO make a script which will launch all the tests and make diff files

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
		std::cout << "time: " <<  ms << "ms" << std::endl;
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
	const int	seed = atoi(argv[1]);
	std::string	container = argv[2];

	std::string output_file = "test/" + container +  "/" + output;
	std::ofstream	test_file(output_file, std::ios_base::trunc);

	Timer timer;

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
		}
		current_seed++;
	}
	// timer.stop();
	// system ("leaks -q ft_containers");
	return 0;
}
