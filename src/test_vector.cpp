#include "test_header.hpp"

# define VECTOR_TESTS 11
# define MAX_TESTS	128
# define MAX_SIZE	64

static int	vector_test = 0;

enum	vector_tests
{
	BASIC_TEST = 0,
	ASSIGN_OPERATOR_TEST,
	COMPARE_OPERATORS_TEST,
	INSERT_TEST,
	ASSIGN_FUNCTION_TEST,
	PUSH_BACK_TEST,
	POP_BACK_TEST,
	ERASE_TEST,
	RESIZE_TEST,
	SWAP_TEST,
	CLEAR_TEST
};

template <typename _vector>
void	test_print(const _vector& p, std::ofstream& test_file)
{
	test_file << "empty: " << p.empty() << std::endl;
	test_file << "size: " << p.size() << std::endl;
	test_file << "capacity: " << p.capacity() << std::endl;
	test_file << "max_size: " << p.max_size() << std::endl;
	if (!p.empty())
	{
		test_file << "content: " << std::endl;
		for (typename _vector::const_iterator it = p.begin(); it != p.end(); it++)
			test_file << *it << std::endl;
		test_file << "reverse: " << std::endl;
		for (typename _vector::const_reverse_iterator it = p.rbegin(); it != p.rend(); it++)
			test_file << *it << std::endl;
		test_file << "front(): " << p.front() << std::endl;
		test_file << "back(): " << p.back() << std::endl;
	}
}

template <typename _vector>
void	test_compare_op(_vector& x, _vector&y, std::ofstream& test_file)
{
	
}

template <typename _vector>
void	test_assign_operator(_vector& x, _vector&y, std::ofstream& test_file)
{
	test_file << "TEST: " << vector_test++;
	test_file << " - Assignment operator" << std::endl;
	_vector	z = x;
	y = z;
	test_print(z);
	x = _vector(z);
	y = z;
	y = _vector(z);
}

template <typename _vector>
void	test_constructors(_vector& x, _vector&y, std::ofstream& test_file)
{
	test_file << "TEST: " << vector_test++;
	test_file << " (Constructor)" << std::endl;
	x = _vector(std::rand() % MAX_SIZE, rdm_val<typename _vector::value_type>()); //fill constructor
	y = _vector(x.begin(), x.end()); // range constructor
	_vector	z(std::rand() % MAX_SIZE, rdm_val<typename _vector::value_type>());
	test_print(x, test_file);
	test_print(y, test_file);
	test_print(z, test_file);
	std::cout << "Copy Constructor" << std::endl;
	_vector	u(x); //copy constructor
	_vector	w(y); // copy constructor
	test_print(u, test_file);
	test_print(w, test_file);
	test_print(z, test_file);
}

template <typename _vector>
void    test_vector(int seed, std::ofstream& test_file)
{
	std::srand(seed);
	void (*test_vector_func[VECTOR_TESTS])(_vector &, _vector &, std::ofstream&) =
	{
		&test_constructors,
		&test_assign_operator,
		&test_compare_op,
		&test_insert,
		&test_assign,
		&test_push,
		&test_pop,
		&test_erase,
		&test_resize,
		&test_swap,
		&test_clear,
	};

	_vector    vec_x; //default constructor
	_vector    vec_y; //defualt constructor

	int	test_counter = 0;

	for (int i = 0; i < MAX_TESTS; i++, test_counter++)
	{
		test_file << "VECTOR TEST: " << test_counter << std::endl;
		switch (std::rand() % VECTOR_TESTS)
		{
		case BASIC_TEST:
			if (std::rand() % 2)
				test_vector_func[BASIC_TEST](vec_x, vec_y, test_file);
			else
				test_vector_func[BASIC_TEST](vec_y, vec_x, test_file);
			break;
		case ASSIGN_OPERATOR_TEST:
			if (std::rand() % 2)
				test_vector_func[ASSIGN_OPERATOR_TEST](vec_x, vec_y, test_file);
			else
				test_vector_func[ASSIGN_OPERATOR_TEST](vec_y, vec_x, test_file);
			break;		
		case COMPARE_OPERATORS_TEST:
			if (std::rand() % 2)
				test_vector_func[COMPARE_OPERATORS_TEST](vec_x, vec_y, test_file);
			else
				test_vector_func[COMPARE_OPERATORS_TEST](vec_y, vec_x, test_file);
			break;
		case INSERT_TEST:
			if (std::rand() % 2)
				test_vector_func[INSERT_TEST](vec_x, vec_y, test_file);
			else
				test_vector_func[INSERT_TEST](vec_y, vec_x, test_file);
			break;
		case ASSIGN_FUNCTION_TEST:
			if (std::rand() % 2)
				test_vector_func[ASSIGN_FUNCTION_TEST](vec_x, vec_y, test_file);
			else
				test_vector_func[ASSIGN_FUNCTION_TEST](vec_y, vec_x, test_file);
			break;
		case PUSH_BACK_TEST:
			if (std::rand() % 2)
				test_vector_func[PUSH_BACK_TEST](vec_x, vec_y, test_file);
			else
				test_vector_func[PUSH_BACK_TEST](vec_y, vec_x, test_file);
			break;
		case POP_BACK_TEST:
			if (std::rand() % 2)
				test_vector_func[POP_BACK_TEST](vec_x, vec_y, test_file);
			else
				test_vector_func[POP_BACK_TEST](vec_y, vec_x, test_file);
			break;
		case ERASE_TEST:
			if (std::rand() % 2)
				test_vector_func[ERASE_TEST](vec_x, vec_y, test_file);
			else
				test_vector_func[ERASE_TEST](vec_y, vec_x, test_file);
			break;
		case RESIZE_TEST:
			if (std::rand() % 2)
				test_vector_func[RESIZE_TEST](vec_x, vec_y, test_file);
			else
				test_vector_func[RESIZE_TEST](vec_y, vec_x, test_file);
			break;
		case SWAP_TEST:
			if (std::rand() % 2)
				test_vector_func[SWAP_TEST](vec_x, vec_y, test_file);
			else
				test_vector_func[SWAP_TEST](vec_y, vec_x, test_file);
			break;
		case CLEAR_TEST:
			if (std::rand() % 2)
				test_vector_func[CLEAR_TEST](vec_x, vec_y, test_file);
			else
				test_vector_func[CLEAR_TEST](vec_y, vec_x, test_file);
			break;
		}
		test_print(x);
		test_print(y);
	}
	
}