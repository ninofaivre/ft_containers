#include "vector.hpp"
#include <vector>
#include <iostream>

int	main(void)
{
	NAMESPACE::vector<int>::const_iterator::value_type	test;
	test = 42;
	std::cout << test << std::endl;
	test = 21;
	std::cout << test << std::endl;
	return (0);
}
