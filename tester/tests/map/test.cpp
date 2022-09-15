#include "map.hpp"
#include <iostream>

int	main(void)
{
	ft::map<std::string, std::string>	test;
	std::cout << test["paulo"] << std::endl;
	std::cout << test["paulo"] << std::endl;
	std::cout << test["nino"] << std::endl;
	std::cout << test["paulo"] << std::endl;
	std::cout << test["paulo"] << std::endl;
	return (0);
}
