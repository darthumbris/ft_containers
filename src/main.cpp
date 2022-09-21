#include "test_header.hpp"
#include "test_vector.cpp"


// void	test_map(int seed, std::ofstream& test_file);
// void	test_stack(int seed, std::ofstream& test_file);
// void	test_set(int seed, std::ofstream& test_file);

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

	std::ofstream	test_file(output, std::ios_base::trunc);

	int	current_seed = seed;
	for (int i = 0; i < MAX_SEED; i++)
	{
		switch (get_container(container))
		{
		case VECTOR:
			// if (i % 2 == 0)
			// {
				std::cout << "Testing string vector" << std::endl;
				test_vector<ft::vector<std::string> >(current_seed, test_file);
			// }
			// else
			// {
				std::cout << "Testing int vector" << std::endl;
				test_vector<ft::vector<int> >(current_seed, test_file);
			// }
			break;
		// case MAP:
		// 	test_map(current_seed, test_file);
		// 	break;
		// case STACK:
		// 	test_stack(current_seed, test_file);
		// 	break;
		// case SET:
		// 	test_set(current_seed, test_file);
		// 	break;
		default:
			std::cerr << "container should be: vector, map, stack or set. Instead got: " << container << std::endl;
			return 1;
		}
		current_seed++;
	}
	return 0;
}