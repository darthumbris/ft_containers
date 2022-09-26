#include "test_random_value.hpp"

#define MAP_TESTS		11
#define MAX_MAP_TESTS	128
#define MAX_MAP_SIZE	64
#define MAP_KEY			256

static int map_test = 0;

//TODO equal range test

enum	map_tests
{
	M_CONSTRUCTORS_TEST = 0,
	M_COMPARE_OPERATOR_TEST,
	M_INSERT_TEST,
	M_ERASE_TEST,
	M_SWAP_TEST,
	M_CLEAR_TEST,
	M_AT_DATA_TEST,
	M_BOUNDS_TEST,
	M_ITERATOR_TEST,
	M_COUNT_TEST
};

template <typename _map>
void test_print_map(const _map &p, std::ofstream& test_file)
{
	test_file << "empty : " << p.empty() << std::endl;
	test_file << "size : " << p.size() << std::endl;
	test_file << "max size : " << p.max_size() << std::endl;
	if (!p.empty())
	{
		test_file << "content : " << std::endl;
		for (typename _map::const_iterator it = p.begin(); it != p.end(); it++)
			test_file << it->first << " => " << it->second << std::endl;
		test_file << "reverse content : " << std::endl;
		for (typename _map::const_reverse_iterator it = p.rbegin(); it != p.rend(); it++)
			test_file << it->first << " => " << it->second << std::endl;
	}
}

template <typename _map>
void test_count(_map &x, _map &y, std::ofstream& test_file)
{
	(void)x;
	test_file << "Test: " << map_test++;
	test_file << " - count" << std::endl;
	
	_map a(y);

	for (int i = 0; i < MAP_KEY; i++)
	{
		test_file << i ;
		if (a.count(i) > 0)
			test_file << " is in map" << std::endl;
		else
			test_file << std::endl;
	}
}

template <typename _it, typename _rit>
void test_iter_increment(_it & _iter, _rit &_rev_iter, int rdm, std::ofstream& test_file)
{
	test_file << "test iterator increment" << std::endl;
	while (rdm--)
	{
		_iter++;
		_rev_iter++;
	}
	test_file << _iter->first << " => " << _iter->second << std::endl;
	test_file << _rev_iter->first << " => " << _rev_iter->second << std::endl;
}

template <typename _it, typename _rit>
void test_iter_decrement(_it& _iter, _rit&_rev_iter, int rdm, std::ofstream& test_file)
{
	test_file << "test iterator decrement" << std::endl;
	while (rdm--)
	{
		_iter--;
		_rev_iter--;
	}
	test_file << _iter->first << " => " << _iter->second << std::endl;
	test_file << _rev_iter->first << " => " << _rev_iter->second << std::endl;
}

template <typename _map>
void test_iterators(_map &x, _map &y, std::ofstream& test_file)
{
	(void)y;
	typedef typename _map::iterator					iter;
	typedef typename _map::const_iterator			const_iter;
	typedef typename _map::reverse_iterator			rev_iter;
	typedef typename _map::const_reverse_iterator	const_rev_iter;
	
	test_file << "Test: " << map_test++;
	test_file << " - iterators" << std::endl;

	typename _map::iterator it;
	it = x.begin();
	iter			_it(it);
	const_iter		const_it = x.end();
	rev_iter		reverse_it = x.rbegin();
	const_rev_iter	const_reverse_it = x.rend();

	size_t	rdm;
	if (x.size())
	{
		rdm = std::rand() % x.size();
		if (rdm)
		{
			test_iter_increment<iter, rev_iter>(_it, reverse_it, rdm, test_file);
			test_iter_decrement<const_iter, const_rev_iter>(const_it, const_reverse_it, rdm, test_file);
		}
	}
}

template <typename _map>
void test_bounds(_map &x, _map &y, std::ofstream& test_file)
{
	test_file << "Test: " << map_test++;
	test_file << " - bounds" << std::endl;
	
	typedef typename _map::iterator	iterator;
	iterator	it;
	iterator	itlow;
	iterator	itup;
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
					test_file << "chosen node" << std::endl;
					test_file << it->first << " => " << it->second << std::endl;
					itlow = x.lower_bound(it->first);
					itup = x.upper_bound(it->first);
					test_file << "lower" << std::endl;
					for (iterator it = itlow; it != x.end(); ++it)
						test_file << it->first << " => " << it->second << std::endl;
					test_file << "upper" << std::endl;
					for (iterator it = itup; it != x.end(); ++it)
						test_file << it->first << " => " << it->second << std::endl;
				}
			}
			break;
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
					test_file << "chosen node" << std::endl;
					test_file << it->first << " => " << it->second << std::endl;
					itlow = y.lower_bound(it->first);
					itup = y.upper_bound(it->first);
					test_file << "lower" << std::endl;
					for (iterator it = itlow; it != y.end(); ++it)
						test_file << it->first << " => " << it->second << std::endl;
					test_file << "upper" << std::endl;
					for (iterator it = itup; it != y.end(); ++it)
						test_file << it->first << " => " << it->second << std::endl;
				}
			}
			break;
	}
}

template <typename _map>
void test_compare_op(_map &x, _map &y, std::ofstream& test_file)
{
	test_file << "Test: " << map_test++;
	test_file << " - compare operators" << std::endl;

	_map a(x);

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

template <typename _map>
void	test_clear_map(_map &x, _map &y, std::ofstream& test_file)
{
	test_file << "Test: " << map_test++;
	test_file << " - clear" << std::endl;
	if (std::rand() % 2)
		x.clear();
	else
		y.clear();
}

template <typename _map>
void test_swap_map(_map &x, _map &y, std::ofstream& test_file)
{
	test_file << "Test: " << map_test++;
	test_file << " - swap" << std::endl;
	if (!x.empty() && !y.empty())
	{
		typename _map::const_iterator it_x = x.begin();
		typename _map::const_iterator it_y = y.begin();
		x.swap(y);
		test_file << "Check iterator validity" << std::endl;
		test_file << "valid : " << (it_x == y.begin()) << std::endl;
		test_file << "valid : " << (it_y == x.end()) << std::endl;
		it_x = x.begin();
		it_y = y.begin();
		std::swap(x, y);
		test_file << "Check iterator validity" << std::endl;
		test_file << "valid : " << (it_x == y.begin()) << std::endl;
		test_file << "valid : " << (it_y == x.end()) << std::endl;
	}
}

template <typename _map>
void test_erase_map(_map &x, _map &y, std::ofstream& test_file)
{
	test_file << "Test: " << map_test++;
	test_file << " - erase" << std::endl;
	typename _map::iterator	it;
	switch (std::rand() % 4)
	{
		case 0 :
			test_file << "erase test 0 x.erase(iterator pos) : " << std::endl;
			if (!x.empty())
				x.erase(x.begin());
			break ;
		case 1 :
			test_file << "erase test 1 x.erase(const key& key) : " << std::endl;
			test_file << "Element erased: " << x.erase(rdm_val<typename _map::key_type>()) << std::endl;
			break ;
		case 2 :
			test_file << "erase test 2 x.erase(iterator first, iterator last) : " << std::endl;
			test_file << "size: " << x.size() << std::endl;
			if (!x.empty() && x.size() > 15)
			{
				it = x.begin();
				for (int i = 0; i < std::rand() % 15; i++)
					it++;
				test_file << "erasing somethingadas" << std::endl;
				test_file << "erasing key: " << it->first << std::endl;
				x.erase(it, x.end());
			}
			break ;
		case 3 :
			test_file << "erase test 3 y.erase(iterator pos) : " << std::endl;
			it = y.begin();
			if (!y.empty() && y.size() > 5)
			{
				int i;
				for (i = 0; i < std::rand() % 5; i++)
					it++;
				test_file << "erasing at i: " << i << std::endl;
				test_file << "going to erase map entry with key: " << it->first << std::endl;
				y.erase(it);
			}
			break;
	}
	test_print_map(x, test_file);
    test_print_map(y, test_file);
}

template <typename _map>
void test_insert_map(_map &x, _map &y, std::ofstream& test_file)
{
    test_file << "Test: " << map_test++;
    test_file << " - insert" << std::endl;
    typename _map::iterator it;
    typedef typename ft::pair<typename _map::key_type, typename _map::mapped_type>	pair_type;
    typedef typename ft::pair< typename _map::iterator, bool>						pair_return;
    
    pair_return	ret; 
    pair_type	value;
    try
    {
        switch (std::rand() % 4)
        {
            case 0:
                test_file << "insert test 0 insert(value) (random value):" << std::endl;
                for (int i = 0; i < std::rand() % MAX_MAP_TESTS; i++)
                {
                    ret = x.insert(rdm_val<typename _map::value_type>());
                    test_file << "key :" << ret.first->first << std::endl;
                    test_file << " value : " << ret.first->second << std::endl;
                    test_file << "already in :" << ret.second << std::endl;
                }
                break;
            case 1:
                test_file << "insert test 1 insert() (value already exists): " << std::endl;
                if (!x.empty())
                {
                    ret = x.insert(*(x.begin()));
                    test_file << "key :" << ret.first->first << std::endl;
                    test_file << " value : " << ret.first->second << std::endl;
                    test_file << "already in :" << ret.second << std::endl;
                }
                if (!y.empty())
                {
                    ret = y.insert(*(--(y.end())));
                    test_file << "key :" << ret.first->first << std::endl;
                    test_file << " value : " << ret.first->second << std::endl;
                    test_file << "already in :" << ret.second << std::endl;
                }
                break;
            case 2:
                test_file << "insert test 2 insert(inputit first, inputit last): " << std::endl;
                if (!y.empty())
                    x.insert(y.begin(), --(y.end()));
                if (!x.empty())
                    y.insert(x.begin(), x.end());
                break;
            case 3:
                test_file << "insert test 3 insert(iterator hint, value): " << std::endl;
                if (!y.empty())
                {
                    typename _map::key_type	test;
                    it = y.begin();
                    test = it->first;
                    for (int k = 0; k < std::rand() % MAX_MAP_TESTS; k++)
                    {
                        value = ft::make_pair(test, rdm_val<typename _map::mapped_type>());
                        it = y.insert(it, value);
                        test++;
                    }
                }
				break;
        }
        test_print_map(x, test_file);
        test_print_map(y, test_file);
    }
    catch (std::exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

template <typename _map>
void test_at_find_operator(_map &x, _map &y, std::ofstream& test_file)
{
	(void)x;
	(void)y;
	typename _map::key_type		rdm_key;
	typename _map::mapped_type	rdm_value;

	test_file << "Test: " << map_test++;
	test_file << " - at find and operator[ ]" << std::endl;
	_map a;

	for (int i = 0; i < MAX_MAP_TESTS; i++)
	{
		rdm_key = rdm_val<typename _map::key_type>();
		rdm_value = rdm_val<typename _map::mapped_type>();
		test_file << "operator[random key] = random value: " << std::endl;
		test_file << "key: " << rdm_key << " and value: " << rdm_value << std::endl;
		a[rdm_key] = rdm_value;
		test_file << "at(key): " << std::endl;
		test_file << "a at key: " << rdm_key << " gives value: " << a.at(rdm_key) << std::endl;
		test_file << "find(key): " << std::endl;
		test_file << a.find(rdm_key)->first << std::endl;
	}
	test_print_map(a, test_file);
}

template <typename _map>
void test_constructors_map(_map &x, _map &y, std::ofstream& test_file)
{
	test_file << "Test: " << map_test++;
	test_file << " - Constructors" << std::endl;
	_map a; //Default/empty constructor
	for (int i = 0 ; i < MAX_MAP_TESTS; i++)
		a.insert(rdm_val<typename _map::value_type>()); //Insert
	test_print_map(a, test_file);
	_map b(a.begin(), a.end()); //range constructor
	test_print_map(b, test_file);
	_map c(a); // Copy constructor
	test_print_map(c, test_file);
	x = c; // Assignment operator
	y = b; // Assignment operator
}


template <class _map>
void test_map(int rdm_seed, std::ofstream& test_file)
{
	std::srand(rdm_seed);

	void (*test_map_func[MAP_TESTS])(_map &, _map &, std::ofstream&) =
		{
			&test_constructors_map,
			&test_at_find_operator,
			&test_compare_op,
			&test_insert_map,
			&test_erase_map,
			&test_swap_map,
			&test_clear_map,
			&test_bounds,
			&test_iterators,
			&test_count,
		};

	_map map_x;
	_map map_y;

	int test_counter = 0;

	for (int i = 0; i < MAX_MAP_TESTS; i++, test_counter++)
	{
		test_file << "Map test: " << test_counter << std::endl;
		switch (std::rand() % MAP_TESTS)
		{
		case (M_CONSTRUCTORS_TEST):
			if (std::rand() % 2)
				test_map_func[M_CONSTRUCTORS_TEST](map_x, map_y, test_file);
			else
				test_map_func[M_CONSTRUCTORS_TEST](map_y, map_x, test_file);
			break;
		case (M_INSERT_TEST):
			if (std::rand() % 2)
				test_map_func[M_INSERT_TEST](map_x, map_y, test_file);
			else
				test_map_func[M_INSERT_TEST](map_y, map_x, test_file);
			break;
		case (M_ERASE_TEST):
			if (std::rand() % 2)
				test_map_func[M_ERASE_TEST](map_x, map_y, test_file);
			else
				test_map_func[M_ERASE_TEST](map_y, map_x, test_file);
			break;
		case (M_CLEAR_TEST):
			test_map_func[M_CLEAR_TEST](map_x, map_y, test_file);
			break;
		case (M_BOUNDS_TEST):
			if (std::rand() % 2)
				test_map_func[M_BOUNDS_TEST](map_x, map_y, test_file);
			else
				test_map_func[M_BOUNDS_TEST](map_y, map_x, test_file);
			break;
		case (M_COMPARE_OPERATOR_TEST):
			if (std::rand() % 2)
				test_map_func[M_COMPARE_OPERATOR_TEST](map_x, map_y, test_file);
			else
				test_map_func[M_COMPARE_OPERATOR_TEST](map_y, map_x, test_file);
			break;
		case (M_ITERATOR_TEST):
			if (std::rand() % 2)
				test_map_func[M_ITERATOR_TEST](map_x, map_y, test_file);
			else
				test_map_func[M_ITERATOR_TEST](map_y, map_x, test_file);
			break;
		case (M_SWAP_TEST) :
			if (std::rand() % 2)
				test_map_func[M_SWAP_TEST](map_x, map_y, test_file);
			else
				test_map_func[M_SWAP_TEST](map_y, map_x, test_file);
			break;
		case (M_COUNT_TEST) :
			if (std::rand() % 2)
				test_map_func[M_COUNT_TEST](map_x, map_y, test_file);
			else
				test_map_func[M_COUNT_TEST](map_y, map_x, test_file);
			break;
		}
		test_print_map(map_x, test_file);
		test_print_map(map_y, test_file);
	}
}
