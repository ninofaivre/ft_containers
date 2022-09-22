#include "map.hpp"
#include "utility.hpp"
#include <map>
#include <iostream>
#include <utility>
#include <memory>

int	main(void)
{
	{
		NAMESPACE::map<int, int>	test;
		NAMESPACE::map<int, int>::iterator it = test.begin();
	//	test[0] = 42;
		std::cout << it->second << std::endl;
	}
	/*
	{
		NAMESPACE::map<int, int>	map_a, map_b;
		map_b[0] = 36;
		map_a[0] = 42;
		map_a[1] = 21;
		NAMESPACE::map<int, int>::iterator	it = map_a.begin();
		std::cout << it->second << std::endl;
		std::cout << "swap a, b" << std::endl;
		map_a.swap(map_b);
		std::cout << it->second << std::endl;
		it++;
		std::cout << it->second << std::endl;
	}
	*/
}
