#include "vector.hpp"

#include <iostream>

int	main(void)
{
	ft::vector<int>	test;

	test.push_back(21);
	test.push_back(42);
	test.push_back(84);
	test.push_back(168);

	ft::vector<int>::iterator it = test.begin();
	ft::vector<int>::const_iterator cit = it;
	std::cout << *it << std::endl
			  << *cit << std::endl;
	++it;
	++cit;
	std::cout << *it << std::endl
			  << *cit << std::endl;
	*it = 9;
	std::cout << *it << std::endl
			  << *cit << std::endl;
	return (0);
}
