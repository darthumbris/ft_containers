#include "test_random_value.hpp"


# define VECTOR_TESTS 13
# define MAX_TESTS	128
# define MAX_SIZE	64

static int	vector_test = 0;

#define CONSTRUCTOR_TEST 0
#define ASSIGN_OPERATOR_TEST 1
#define COMPARE_OPERATOR_INSERT_TEST 2
#define INSERT_TEST 3
#define ASSIGN_FUNCTION_TEST 4
#define PUSH_BACK_TEST 5
#define POP_BACK_TEST 6
#define ERASE_TEST 7
#define RESIZE_TEST 8
#define SWAP_TEST 9
#define CLEAR_TEST 10
#define AT_DATA_TEST 11
#define RESERVE_TEST 12

template <typename _vector>
void	test_at_and_data(_vector& x, _vector&y, std::ofstream& test_file)
{
	test_file << "Test: " << vector_test++;
	test_file << " - at and operator[] and data" << std::endl;
	if (std::rand() % 2)
	{
		if (!x.empty())
		{
			test_file << "x.at(rand()): " << std::endl;
			test_file << x.at(std::rand() % x.size());
			test_file << "x[rand()]: " << std::endl;
			test_file << x[std::rand() % x.size()] << std::endl;
			test_file << "x.data(): " << std::endl;
			test_file << *x.data() << std::endl;
		}
	}
	else
	{
		if (!y.empty())
		{
			test_file << "y.at(rand()): " << std::endl;
			test_file << y.at(std::rand() % y.size());
			test_file << "y[rand()]: " << std::endl;
			test_file << y[std::rand() % y.size()] << std::endl;
			test_file << "y.data(): " << std::endl;
			test_file << *y.data() << std::endl;
		}
	}
}

template <typename _vector>
void	test_reserve(_vector& x, _vector&y, std::ofstream& test_file)
{
	test_file << "Test: " << vector_test++;
	test_file << " - at and operator[] and data" << std::endl;
	if (std::rand() % 2)
	{
		test_file << "capacity before reserve: " << x.capacity() << std::endl;
		test_file << "x.reserve(rand()): " << std::endl;
		x.reserve(std::rand() % (MAX_SIZE * 2));
		test_file << "capacity after reserve: " << std::endl;
		test_file << x.capacity() << std::endl;
	}
	else
	{
		test_file << "capacity before reserve: " << y.capacity() << std::endl;
		test_file << "y.reserve(rand()): " << std::endl;
		y.reserve(std::rand() % (MAX_SIZE * 2));
		test_file << "capacity after reserve: " << std::endl;
		test_file << y.capacity() << std::endl;
	}
}

template <typename _vector>
void	test_clear(_vector& x, _vector&y, std::ofstream& test_file)
{
	test_file << "Test: " << vector_test++;
	test_file << " - clear" << std::endl;
	if (std::rand() % 2)
	{
		test_file << "x.size before clear: " << x.size() << std::endl;
		test_file << "x.clear():" << std::endl;
		x.clear();
	}
	else
	{
		test_file << "y.size before clear: " << y.size() << std::endl;
		test_file << "y.clear():" << std::endl;
		y.clear();
	}
	test_file << "x.size(): " << x.size() << std::endl;
	test_file << "y.size(): " << y.size() << std::endl;
}

template <typename _vector>
void	test_swap(_vector& x, _vector&y, std::ofstream& test_file)
{
	test_file << "Test: " << vector_test++;
	test_file << " - swap" << std::endl;
	if (std::rand() % 2)
	{
		test_file << "x.swap(y):" << std::endl;
		x.swap(y);
	}
	else
	{
		test_file << "y.swap(x):" << std::endl;
		y.swap(x);
	}
}

template <typename _vector>
void	test_resize(_vector& x, _vector&y, std::ofstream& test_file)
{
	size_t resize;
	test_file << "Test: " << vector_test++;
	test_file << " - resize" << std::endl;
	if (!x.empty())
	{
		test_file << "capacity before resize: " << x.capacity() << std::endl;
		test_file << "size before resize: " << x.size() << std::endl;
		resize = std::rand() % (x.size() * 2);
		test_file << "resize : x.resize(rand() % size * 2, rand()):" << std::endl;
		test_file << "resizing to: " << resize << std::endl;
		x.resize(resize, rdm_val<typename _vector::value_type>());
	}
	else
	{
		test_file << "capacity before resize: " << x.capacity() << std::endl;
		test_file << "size before resize: " << x.size() << std::endl;
		resize = std::rand() % MAX_SIZE;
		test_file << "resize : x.resize(rand() % max_size, rand()):" << std::endl;
		test_file << "resizing to: " << resize << std::endl;
		x.resize(resize, rdm_val<typename _vector::value_type>());
	}
	if (!y.empty())
	{
		test_file << "capacity before resize: " << y.capacity() << std::endl;
		test_file << "size before resize: " << y.size() << std::endl;
		resize = std::rand() % (y.size() * 2);
		test_file << "resize : y.resize(rand() % size * 2, rand()):" << std::endl;
		test_file << "resizing to: " << resize << std::endl;
		y.resize(resize, rdm_val<typename _vector::value_type>());
	}
	else
	{
		test_file << "capacity before resize: " << y.capacity() << std::endl;
		test_file << "size before resize: " << y.size() << std::endl;
		resize = std::rand() % MAX_SIZE;
		test_file << "resize : y.resize(rand() % max_size, rand()):" << std::endl;
		test_file << "resizing to: " << resize << std::endl;
		y.resize(resize, rdm_val<typename _vector::value_type>());
	}
}

template <typename _vector>
void	test_erase(_vector& x, _vector&y, std::ofstream& test_file)
{
	test_file << "Test: " << vector_test++;
	test_file << " - erase" << std::endl;
	typename _vector::iterator pos;
	(void)y;
	switch (std::rand() % 4)
	{
		case (0) :
			test_file << "erase case 0 erase(iterator pos) x.erase(x.begin()):" << std::endl;
			if (!x.empty())
				x.erase(x.begin());
		case (1) :
			test_file << "erase case 1 erase(iterator pos) x.erase(x.end() -1 ):" << std::endl;
			if (!x.empty())
				x.erase(x.end() - 1);
		case (2) :
			test_file << "erase case 2 erase(iterator first, iterator last) x.erase(x.begin(), rand() pos):" << std::endl;
			if (!x.empty() && x.size() > 1)
			{   
				pos = x.begin() + (std::rand() % x.size());
				x.erase(x.begin(), pos);
			}
		case (3) :
			test_file << "erase case 3 erase(iteror first, iterator last) y.erase(y.begin(), rand() pos):" << std::endl;
			if (!y.empty() && y.size() > 1)
			{
				pos = y.begin() + (std::rand() % y.size());
				y.erase(y.begin(), pos);
			}
			break ;
	}
}

template <typename _vector>
void	test_pop_back(_vector& x, _vector&y, std::ofstream& test_file)
{
	test_file << "Test: " << vector_test++;
	test_file << " - pop_back" << std::endl;
	switch (std::rand() % 2)
	{
		case (0) :
			test_file << "pop_back case 0: popping all of x" << std::endl;
			if (!x.empty())
				for (size_t i = 0; i < x.size(); i++)
					x.pop_back();
		case (1) :
			test_file << "pop_back case 1: popping all of y" << std::endl;
			if (!y.empty())
				for (size_t i = 0; i < y.size(); i++)
					y.pop_back();
	}
}

template <typename _vector>
void	test_push_back(_vector& x, _vector&y, std::ofstream& test_file)
{
	test_file << "Test: " << vector_test++;
	test_file << " - push_back" << std::endl;
	switch (std::rand() % 3)
	{
		case (0) :
			test_file << "push_back case 0: x.push_back(rand()) (for loop)" << std::endl;
			for (size_t i = 0; i < std::rand() % MAX_SIZE; i++)
				x.push_back(rdm_val<typename _vector::value_type>());
		case (1) :
			test_file << "push_back case 1: y.push_back(rand()) (for loop)" << std::endl;
			for (size_t i = 0; i < std::rand() % MAX_SIZE; i++)
				y.push_back(rdm_val<typename _vector::value_type>());
		case (2) :
			test_file << "push_back case 2: a.push_back(rand()) (one push_back)" << std::endl;
			_vector a;
			a.push_back(rdm_val<typename _vector::value_type>());
			test_print(a, test_file);
	}
}

template <typename _vector>
void	test_assign(_vector& x, _vector&y, std::ofstream& test_file)
{
	_vector a;
	test_file << "Test: " << vector_test++;
	test_file << " - Assign" << std::endl;
	switch (std::rand() % 4)
	{
	case (0):
		test_file << "Assign case 0 assign(size_type count, const T& value) a.assign(0, rand()):" << std::endl;
		a.assign(0, rdm_val<typename _vector::value_type>());
	case (1):
		test_file << "Assign case 1 assign(size_type count, const T& value) a.assign(rand(), rand()):" << std::endl;
		a.assign(std::rand() % MAX_SIZE, rdm_val<typename _vector::value_type>());
	case (2):
		test_file << "Assign case 2 assign(InputIt first, InputIt last): a.assign(y.begin(), y.end())" << std::endl;
		a.assign(y.begin(), y.end());
	case (3):
		test_file << "Assign case 3 assign(InputIt first, InputIt last): a.assign(y.begin + rand(), y.end())" << std::endl;
		if (!y.empty())
			a.assign(y.begin() + (std::rand() % y.size()), y.end());
	case (4):
		test_file << "Assign case 4 assign(InputIt first, InputIt last): a.assign(y.begin(), y.end() - rand())" << std::endl;
		if (!y.empty())
			a.assign(y.begin(), y.end() - (std::rand() % y.size()));
	case (5):
		test_file << "Assign case 5 assign(InputIt first, InputIt last): x.assign(a.begin(), a.end() - rand())" << std::endl;
		if (!a.empty())
			x.assign(a.begin(), a.end() - (std::rand() % a.size()));
	}
	test_print(a, test_file);
}

template <typename _vector>
void	test_insert(_vector& x, _vector&y, std::ofstream& test_file)
{
	test_file << "Test: " << vector_test++;
	test_file << " - insert" << std::endl;
	typename _vector::iterator it;
	if (!x.empty())
		it = x.begin() + std::rand() % x.size();
	else
	{
		it = x.end();
		try
		{
			switch (std::rand() % 3)
			{
				case 0:
					test_file << "Insert test 0 insert(iterator pos, const T& value):" << std::endl;
					test_file << *x.insert(it, rdm_val<typename _vector::value_type>()) << std::endl;
					if (!y.empty())
						test_file << *y.insert(y.begin(), rdm_val<typename _vector::value_type>()) << std::endl;
					break;
				case 1:
					test_file << "Insert test 1 insert(iterator pos, inputIt first, inputIt last):" << std::endl;
					if (!x.empty() && !y.empty())
						y.insert(y.begin() + (std::rand() % y.size()), it, it + (std::rand() % (x.size() - (it - x.begin()))));
					else if (!y.empty())
						y.insert(y.begin() + (std::rand() % y.size()), it, x.end());
					else
						y.insert(y.begin(), it, x.end());
					break;
				case 2:
					test_file << "capacity before: " << y.capacity() << std::endl;
					test_file << "size before: " << y.size() << std::endl;
					test_file << "Insert test 2 insert(iterator pos, size_type count, const T& value):" << std::endl;
					if (!y.empty())
						y.insert(y.begin(), (std::rand() % y.size()), rdm_val<typename _vector::value_type>());
					else
						y.insert(y.begin(), std::rand() % 5, rdm_val<typename _vector::value_type>());
					break;
			}
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}

template <typename _vector>
void	test_compare_op_and_insert(_vector& x, _vector&y, std::ofstream& test_file)
{
	test_file << "Test: " << vector_test++;
	test_file << " - compare operator and insert" << std::endl;
	_vector a;
	_vector b;
	a.insert(a.begin(), MAX_SIZE, rdm_val<typename _vector::value_type>());
	b.insert(b.begin(), a.begin(), a.end());
	if (a == b)
		test_file << "a == b" << std::endl;
	b.pop_back();
	if (a != b)
		test_file << "a != b" << std::endl;
	if (a > b)
		test_file << "a > b" << std::endl;
	if (a >= b)
		test_file << "a >= b" << std::endl;
	if (x < y)
		test_file << "x < y" << std::endl;
	if (x <= y)
		test_file << "x <= y" << std::endl;
	test_print(a, test_file);
	test_print(b, test_file);
}

template <typename _vector>
void	test_assign_operator(_vector& x, _vector&y, std::ofstream& test_file)
{
	test_file << "Test: " << vector_test++;
	test_file << " - Assignment operator" << std::endl;
	_vector	z = x;
	y = z;
	test_print(z, test_file);
	x = _vector(z);
	y = z;
	y = _vector(z);
}

template <typename _vector>
void	test_constructors(_vector& x, _vector&y, std::ofstream& test_file)
{
	test_file << "Test: " << vector_test++;
	test_file << " (Constructor)" << std::endl;
	x = _vector(std::rand() % MAX_SIZE, rdm_val<typename _vector::value_type>()); //fill constructor
	y = _vector(x.begin(), x.end()); // range constructor
	_vector	z(std::rand() % MAX_SIZE, rdm_val<typename _vector::value_type>()); //fill constructor
	test_print(x, test_file);
	test_print(y, test_file);
	test_print(z, test_file);
	test_file << "Copy Constructor" << std::endl;
	_vector	u(x); //copy constructor
	_vector	w(y); // copy constructor
	test_print(u, test_file);
	test_print(w, test_file);
	test_print(z, test_file);
}

template <class _vector>
void	test_vector(int seed, std::ofstream& test_file)
{
	std::srand(seed);
	void (*test_vector_func[VECTOR_TESTS])(_vector &, _vector &, std::ofstream&) =
	{
		&test_constructors,
		&test_assign_operator,
		&test_compare_op_and_insert,
		&test_insert,
		&test_assign,
		&test_push_back,
		&test_pop_back,
		&test_erase,
		&test_resize,
		&test_swap,
		&test_clear,
		&test_at_and_data,
		&test_reserve,
	};

	_vector	vec_x; //default constructor
	_vector	vec_y; //defualt constructor

	int	test_counter = 0;

	for (int i = 0; i < MAX_TESTS; i++, test_counter++)
	{
		test_file << "Vector test: " << test_counter << std::endl;
		switch (std::rand() % VECTOR_TESTS)
		{
		case CONSTRUCTOR_TEST:
			if (std::rand() % 2)
				test_vector_func[CONSTRUCTOR_TEST](vec_x, vec_y, test_file);
			else
				test_vector_func[CONSTRUCTOR_TEST](vec_y, vec_x, test_file);
			break;
		case ASSIGN_OPERATOR_TEST:
			if (std::rand() % 2)
				test_vector_func[ASSIGN_OPERATOR_TEST](vec_x, vec_y, test_file);
			else
				test_vector_func[ASSIGN_OPERATOR_TEST](vec_y, vec_x, test_file);
			break;		
		case COMPARE_OPERATOR_INSERT_TEST:
			if (std::rand() % 2)
				test_vector_func[COMPARE_OPERATOR_INSERT_TEST](vec_x, vec_y, test_file);
			else
				test_vector_func[COMPARE_OPERATOR_INSERT_TEST](vec_y, vec_x, test_file);
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
		case AT_DATA_TEST:
			if (std::rand() % 2)
				test_vector_func[AT_DATA_TEST](vec_x, vec_y, test_file);
			else
				test_vector_func[AT_DATA_TEST](vec_y, vec_x, test_file);
			break;
		case RESERVE_TEST:
			if (std::rand() % 2)
				test_vector_func[RESERVE_TEST](vec_x, vec_y, test_file);
			else
				test_vector_func[RESERVE_TEST](vec_y, vec_x, test_file);
			break;
		}
		test_print(vec_x, test_file);
		test_print(vec_y, test_file);
	}	
}
