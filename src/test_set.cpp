#include "test_random_value.hpp"

#define SET_TESTS		9
#define SET_MAX_TESTS	128
#define SET_MAX_SIZE	64
#define SET_KEY			256

static int	set_test = 0;

#define SET_CONSTRUCTOR_TEST		0
#define SET_COMPARE_OPERATOR_TEST	1
#define SET_INSERT_TEST				2
#define SET_ERASE_TEST				3
#define SET_CLEAR_TEST				4
#define SET_BOUNDS_TEST				5
#define SET_SWAP_TEST				6
#define SET_ITERATORS_TEST			7
#define SET_COUNT_TEST				8


template <typename _set>
void test_print_set(const _set &p, std::ofstream& test_file)
{
	test_file << "empty: " << p.empty() << std::endl;
	test_file << "size: " << p.size() << std::endl;
	test_file << "max size: " << p.max_size() << std::endl;
	if (!p.empty())
	{
		test_file << "content: " << std::endl;
		for (typename _set::const_iterator it = p.begin(); it != p.end(); it++)
			test_file << "key: " << *it << std::endl;
		test_file << "reverse content: " << std::endl;
		for (typename _set::const_reverse_iterator it = p.rbegin(); it != p.rend(); it++)
			test_file << "key: " << *it << std::endl;
	}
}

template <typename _set>
void test_swap_set(_set &x, _set &y, std::ofstream& test_file)
{
	test_file << "Test: " << set_test++;
	test_file << " - swap" << std::endl;
	if (!x.empty() && !y.empty())
	{
		typename _set::const_iterator it_x = x.begin();
		typename _set::const_iterator it_y = y.begin();
		x.swap(y);
		test_file << "Check iterator validity: " << std::endl;
		test_file << "valid: " << (it_x == y.begin()) << std::endl;
		test_file << "valid: " << (it_y == x.end()) << std::endl;
	}
}

template <typename _set>
void test_count_set(_set &x, _set &y, std::ofstream& test_file)
{
	(void)x;
	test_file << "Test: " << set_test++;
	test_file << " - count" << std::endl;
	
	_set a(y);
	for (int i = 0; i < SET_KEY; i++)
	{
		test_file << i ;
		if (a.count(i) > 0)
			test_file << " is in map" << std::endl;
	}
}

template <typename _it, typename _rit>
void test_iter_increment_set(_it & _iter, _rit &_rev_iter, int rdm, std::ofstream& test_file)
{
	test_file << "test iterator increment" << std::endl;
	while (rdm--)
	{
		_iter++;
		_rev_iter++;
	}
	test_file << *_iter << std::endl;
	test_file << *_rev_iter << std::endl;
}

template <typename _it, typename _rit>
void test_iter_decrement_set(_it & _iter, _rit &_rev_iter, int rdm, std::ofstream& test_file)
{
	test_file << "test iterator decrement" << std::endl;
	while (rdm--)
	{
		_iter--;
		_rev_iter--;
	}
	test_file << *_iter << std::endl;
	test_file << *_rev_iter << std::endl;
}

template <typename _set>
void test_iterators_set(_set &x, _set &y, std::ofstream& test_file)
{
	(void)y;
	test_file << "Test: " << set_test++;
	test_file << " - iterators" << std::endl;

	typename _set::iterator it;
	it = x.begin();
	typename _set::iterator _it(it);
	typename _set::const_iterator const_it = x.end();
	typename _set::reverse_iterator rev_it = x.rbegin();
	typename _set::const_reverse_iterator const_rev_it = x.rend();

	size_t rdm;
	if (x.size())
	{
		rdm = std::rand() % x.size();
		if (rdm)
		{
			test_iter_increment_set<typename _set::iterator, typename _set::reverse_iterator>(_it, rev_it, rdm, test_file);
			test_iter_decrement_set<typename _set::const_iterator, typename _set::const_reverse_iterator>(const_it, const_rev_it, rdm, test_file);
		}
	}
}

template <typename _set>
void test_bounds_set(_set &x, _set &y, std::ofstream& test_file)
{
	test_file << "Test: " << set_test++;
	test_file << " - bounds" << std::endl;
	
	typedef typename _set::iterator iterator;
	iterator it;
	iterator it_low;
	iterator it_up;
	switch (std::rand() % 2)
	{
		case 0:
			test_file << "bounds test 0 x lower and upper bound: " << std::endl;
			if (!x.empty())
			{
				it = x.begin();
				size_t rdn = std::rand() % x.size();
				while (rdn--)
					it++;
				if (it != x.end())
				{
					test_file << "chosen node: " << std::endl;
					test_file << *it << std::endl;
					it_low = x.lower_bound(*it);
					it_up = x.upper_bound(*it);
					test_file << "lower_bound: " << std::endl;
					for (iterator it = it_low; it != x.end(); ++it)
						test_file << *it << std::endl;
					test_file << "upper_bound: " << std::endl;
					for (iterator it = it_up; it != x.end(); ++it)
						test_file << *it << std::endl;
				}
			}
		case 1:
			test_file << "bounds test 0 y lower and upper bound: " << std::endl;
			if (!y.empty())
			{
				it = y.begin();
				size_t rdn = std::rand() % y.size();
				while (rdn--)
					it++;
				if (it != y.end())
				{
					test_file << "chosen node: " << std::endl;
					test_file << *it << std::endl;
					it_low = y.lower_bound(*it);
					it_up = y.upper_bound(*it);
					test_file << "lower_bound: " << std::endl;
					for (iterator it = it_low; it != y.end(); ++it)
						test_file << *it << std::endl;
					test_file << "upper_bound: " << std::endl;
					for (iterator it = it_up; it != y.end(); ++it)
						test_file << *it << std::endl;
				}
			}
	}
}

template <typename _set>
void	test_clear_set(_set &x, _set &y, std::ofstream& test_file)
{
	test_file << "Test: " << set_test++;
	test_file << " - clear" << std::endl;
	if (std::rand() % 2)
		x.clear();
	else
		y.clear();
}

template <typename _set>
void test_erase_set(_set &x, _set &y, std::ofstream& test_file)
{
	test_file << "Test: " << set_test++;
	test_file << " - erase" << std::endl;
	typename _set::iterator it;
	switch (std::rand() % 4)
	{
		case 0:
			test_file << "erase test 0 erase(iterator pos) x.erase(x.begin()): " << std::endl;
			if (!x.empty())
				x.erase(x.begin());
			break ;
		case 1:
			test_file << "erase test 1 erase(const key) x.erase(rand()): " << std::endl;
			test_file << "Elements erased: " << x.erase(rdm_val<typename _set::key_type>()) << std::endl;
			break ;
		case 2:
			test_file << "erase test 2 erase(iterator first, iterator last) erasing x: " << std::endl;
			test_file << "x size: " << x.size() << std::endl;
			if (x.size() > SET_MAX_SIZE)
			{
				it = x.begin();
				int i;
				for (i = 0; i < std::rand() % SET_MAX_SIZE; i++)
					it++;
				test_file << "going to erase from pos: " << i << std::endl;
				test_file << "with key: " << *it << std::endl;
				x.erase(it, x.end());
			}
			break ;
		case 3:
			test_file << "erase test 3 erase(iterator pos) erasing y: " << std::endl;
			test_file << "y size: " << y.size() << std::endl;
			it = y.begin();
			if (!y.empty() && y.size() > 5)
			{
				for (int i = 0; i < std::rand() % 5; i++)
					it++;
				test_file << "going to erase set with value: " << *it << std::endl;
				y.erase(it);
			}
			break;
	}
}


template <typename _set>
void test_insert_set(_set &x, _set &y, std::ofstream& test_file)
{
	test_file << "Test: " << set_test++;
	test_file << " - insert" << std::endl;
	typename _set::iterator it;
	typedef typename ft::pair<typename _set::iterator, bool>   pair_return;
	pair_return     ret; 
	try
	{
		switch (std::rand() % 4)
		{
			case 0:
				test_file << "insert test 0 insert(value) (random value): " << std::endl;
				for (int i = 0; i < std::rand() % SET_MAX_SIZE; i++)
				{
					ret = x.insert(rdm_val<typename _set::value_type>());
					test_file << "key:" << *ret.first << std::endl;
					test_file << "already in:" << ret.second << std::endl;
				}
				break;
			case 1:
				test_file << "insert test 1 insert(value) (value already exists): " << std::endl;
				if (!x.empty())
				{
					test_file << "inserting in x the value of x.begin(): " << std::endl;
					ret = x.insert(*(x.begin()));
					test_file << "key:" << *ret.first << std::endl;
					test_file << "already in:" << ret.second << std::endl;

				}
				if (!y.empty())
				{
					test_file << "inserting in y the value of --(y.end()): " << std::endl;
					ret = y.insert(*(--(y.end())));
					test_file << "key:" << *ret.first << std::endl;
					test_file << "already in:" << ret.second << std::endl;
				}
				break;
			case 2:
				test_file << "insert test 2 insert(input it first, input it last): " << std::endl;
				if (!y.empty())
					x.insert(y.begin(), --(y.end()));
				if (!x.empty())
					y.insert(x.begin(), x.end());
				break;
			case 3:
				test_file << "insert test 3 insert(iterator hint, value): " << std::endl;
				if (!y.empty())
				{
					typename _set::key_type test = rdm_val<typename _set::key_type>();
					it = y.begin();
					for (int k = 0; k < std::rand() % SET_MAX_SIZE; k++)
					{
						it = y.insert(it, test);
						test++;
					}
				}
		}
		test_print_set(x, test_file);
		test_print_set(y, test_file);
	}
	catch (std::exception &error)
	{
		test_file << error.what() << std::endl;
	}
}

template <typename _set>
void test_compare_op_set(_set &x, _set &y, std::ofstream& test_file)
{
	test_file << "Test: " << set_test++;
	test_file << " - compare operators" << std::endl;

	_set a(x);
	if (x < y)
		test_file << "x < y" << std::endl;
	if (x > y)
		test_file << "x > y" << std::endl;
	if (y < x)
		test_file << "y < x" << std::endl;
	if (y > x)
		test_file << "y > x" << std::endl;
	if (x <= a)
		test_file << "x <= a" << std::endl;
	if (x >= a)
		test_file << "x >= a" << std::endl;
	if (y <= a)
		test_file << "y <= a" << std::endl;
	if (y >= a)
		test_file << "y >= a" << std::endl;
	if (x == a)
		test_file << "x == a" << std::endl;
	if (x != y)
		test_file << "x != y" << std::endl;
}


template <typename _set>
void test_constructors_set(_set &x, _set &y, std::ofstream& test_file)
{
	test_file << "Test: " << set_test++;
	test_file << " - constructors" << std::endl;
	_set a; //default constructor
	for (int i = 0 ; i < SET_MAX_SIZE; i++)
		a.insert(rdm_val<typename _set::value_type>());
	test_print_set(a, test_file);
	_set b(a.begin(), a.end()); //range constructor
	test_print_set(b, test_file);
	_set c(a); //copy constructor
	test_print_set(c, test_file);
	x = c; //assignment operator
	y = b; //assignment operator
}

template <class _set>
void test_set(int rdm_seed, std::ofstream& test_file)
{
	std::srand(rdm_seed);

	void (*_test_main[])(_set &, _set &, std::ofstream&) =
		{
			&test_constructors_set,
			&test_compare_op_set,
			&test_insert_set,
			&test_erase_set,
			&test_clear_set,
			&test_bounds_set,
			&test_iterators_set,
			&test_swap_set,
			&test_count_set
		};

	_set x;
	_set y;

	int	test_counter = 0;

	for (int i = 0; i < SET_MAX_TESTS; i++, test_counter++)
	{
		test_file << "Set test: " << test_counter << std::endl;
		switch (std::rand() % SET_TESTS)
		{
		case (SET_CONSTRUCTOR_TEST):
			if (std::rand() % 2)
				_test_main[SET_CONSTRUCTOR_TEST](x, y, test_file);
			else
				_test_main[SET_CONSTRUCTOR_TEST](y, x, test_file);
			break;
		case (SET_COMPARE_OPERATOR_TEST):
			if (std::rand() % 2)
				_test_main[SET_COMPARE_OPERATOR_TEST](x, y, test_file);
			else
				_test_main[SET_COMPARE_OPERATOR_TEST](y, x, test_file);
			break;
		case (SET_INSERT_TEST):
			if (std::rand() % 2)
				_test_main[SET_INSERT_TEST](x, y, test_file);
			else
				_test_main[SET_INSERT_TEST](y, x, test_file);
			break;
		case (SET_ERASE_TEST):
			_test_main[SET_ERASE_TEST](x, y, test_file);
			break;
		case (SET_CLEAR_TEST):
			if (std::rand() % 2)
				_test_main[SET_CLEAR_TEST](x, y, test_file);
			else
				_test_main[SET_CLEAR_TEST](y, x, test_file);
			break;
		case (SET_BOUNDS_TEST):
			if (std::rand() % 2)
				_test_main[SET_BOUNDS_TEST](x, y, test_file);
			else
				_test_main[SET_BOUNDS_TEST](y, x, test_file);
			break;
		case (SET_SWAP_TEST):
			if (std::rand() % 2)
				_test_main[SET_SWAP_TEST](x, y, test_file);
			else
				_test_main[SET_SWAP_TEST](y, x, test_file);
			break;
		case (SET_ITERATORS_TEST) :
			if (std::rand() % 2)
				_test_main[SET_ITERATORS_TEST](x, y, test_file);
			else
				_test_main[SET_ITERATORS_TEST](y, x, test_file);
			break;
		case (SET_COUNT_TEST) :
			if (std::rand() % 2)
				_test_main[SET_COUNT_TEST](x, y, test_file);
			else
				_test_main[SET_COUNT_TEST](y, x, test_file);
			break;
		}
		test_print_set(x, test_file);
		test_print_set(y, test_file);
	}
}