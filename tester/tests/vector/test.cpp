#include "vector.hpp"
#include <vector>
#include <iostream>

int	main(void)
{
	NAMESPACE::vector<int>	test;
	std::cout << test.begin() - test.end() << std::endl;
	return (0);
}
