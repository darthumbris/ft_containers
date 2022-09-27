#include "test_random_value.hpp"

#define STACK_TESTS		4
#define STACK_MAX_TESTS	128
#define STACK_MAX_SIZE	64

static int	stack_test = 0;

#define S_CONSTRUCTOR_TEST		0
#define S_COMPARE_OPERATOR_TEST	1
#define S_PUSH_BACK_TEST		2
#define S_POP_BACK_TEST			3


template <typename _stack>
void test_print_stack(_stack &p, std::ofstream& test_file)
{
	test_file << "empty : " << p.empty() << std::endl;
	test_file << "size : " << p.size() << std::endl;
	if (!p.empty())
	{
		test_file << "top : " << p.top() << std::endl;
		test_file << "content : " << std::endl;
		while (!p.empty())
		{
			test_file << p.top() << std::endl;
			p.pop();
		}
	}
}

template <typename _stack>
void test_pop_back_stack(_stack &x, _stack &y, std::ofstream& test_file)
{
	test_file << "Test: " << stack_test++;
	test_file << " - pop" << std::endl;
	size_t rdm = std::rand();
	switch (std::rand() % 2)
	{
		case 0:
			test_file << "pop test 0 x.pop(rand()) in loop: " << std::endl;
			if (!x.empty())
				for (size_t i = 0; i < rdm % x.size(); i++)
					x.pop();
		case 1:
			test_file << "pop test 1 y.pop(rand()) in loop: " << std::endl;
			if (!y.empty())
				for (size_t i = 0; i < rdm % y.size(); i++)
					y.pop();
	}
}

template <typename _stack>
void test_push_back_stack(_stack &x, _stack &y, std::ofstream& test_file)
{
	test_file << "Test: " << stack_test++;
	test_file << " - push" << std::endl;
	switch (std::rand() % 3)
	{
		case 0:
			test_file << "push test 0 x.push(rand()) in loop: " << std::endl;
			for (int i = 0; i < std::rand() % STACK_MAX_TESTS; i++)
				x.push(rdm_val<int>());
		case 1:
			test_file << "push test 1 y.push(rand()) in loop: " << std::endl;
			for (int i = 0; i < std::rand() % STACK_MAX_TESTS; i++)
				y.push(rdm_val<int>());
		case 2:
			test_file << "push test 2 z.push(rand()) one value: " << std::endl;
			_stack a; //default constructor
			a.push(rdm_val<int>());
			test_print_stack(a, test_file);
	}
}

template <typename _stack>
void test_compare_op_stack(_stack &x, _stack &y, std::ofstream& test_file)
{
	test_file << "Test: " << stack_test++;
	test_file << " - compare operators" << std::endl;
	if (x == y)
		test_file << "x == y" << std::endl;
	if (x != y)
		test_file << "x != y" << std::endl;
	if (x > y)
		test_file << "x > y" << std::endl;
	if (x >= y)
		test_file << "x >= y" << std::endl;
	if (x < y)
		test_file << "x < y" << std::endl;
	if (x <= y)
		test_file << "x <= y" << std::endl;
}

template <typename _stack>
void test_constructors_stack(_stack &x, _stack &y, std::ofstream& test_file)
{
	test_file << "Test: " << stack_test++;
	test_file << " - constructors" << std::endl;
	ft::vector<int> myvector(std::rand() % STACK_MAX_SIZE, rdm_val<int>());
	ft::stack<int, ft::vector<int> > a(myvector); //default constructor
	ft::stack<int, ft::vector<int> > b(a); //copy constructor

	ft::stack<int, std::deque<int> > test_deque; //test with other container than vector
	for(int i = 0; i < 30; i++)
		test_deque.push(i);

	ft::stack<int>						c;
	ft::stack<int>						d;
	ft::stack<int, std::deque<int> >	e;
	c = x; // assignment operator
	d = y; // assignment operator
	e = test_deque; //assignment operator also working with deque
	test_print_stack(a, test_file);
	test_print_stack(b, test_file);
	test_print_stack(c, test_file);
	test_print_stack(d, test_file);
	test_print_stack(e, test_file);
	test_print_stack(test_deque, test_file);
}

template <class _stack>
void test_stack(int rdm_seed, std::ofstream& test_file)
{
	std::srand(rdm_seed);
	void (*_test_main[])(_stack &, _stack &, std::ofstream&) =
		{
			&test_constructors_stack,
			&test_compare_op_stack,
			&test_push_back_stack,
			&test_pop_back_stack,
		};

	_stack x;
	_stack y;

	int test_counter = 0;
	for (int i = 0; i < STACK_MAX_TESTS; i++, test_counter++)
	{
		test_file << "MAIN TEST : " << test_counter << std::endl;
		switch (std::rand() % STACK_TESTS)
		{
		case (S_CONSTRUCTOR_TEST):
			if (std::rand() % 2)
				_test_main[S_CONSTRUCTOR_TEST](x, y, test_file);
			else
				_test_main[S_CONSTRUCTOR_TEST](y, x, test_file);
			break;
		case (S_COMPARE_OPERATOR_TEST) :
			if (std::rand() % 2)
				_test_main[S_COMPARE_OPERATOR_TEST](x, y, test_file);
			else
				_test_main[S_COMPARE_OPERATOR_TEST](y, x, test_file);
		case (S_PUSH_BACK_TEST):
			if (std::rand() % 2)
				_test_main[S_PUSH_BACK_TEST](x, y, test_file);
			else
				_test_main[S_PUSH_BACK_TEST](y, x, test_file);
			break;
		case (S_POP_BACK_TEST):
			if (std::rand() % 2)
				_test_main[S_POP_BACK_TEST](x, y, test_file);
			else
				_test_main[S_POP_BACK_TEST](y, x, test_file);
			break;
		}
		test_print_stack(x, test_file);
		test_print_stack(y, test_file);
	}
}
