#include "map.hpp"
#include <map>
#include <iostream>

int	main(void)
{
	ft::map<int, int>	test;
	test[42] = 42;
	std::cout << test[42] << std::endl;
	std::cout << test.size() << std::endl;
	return (0);
}
