#include "map.hpp"
#include <map>
#include <iostream>

int	main(void)
{
	ft::map<std::string, std::string>	test;
	test["paulo"] = "le bato";
	test["nino"] = "le tablo";
	ft::map<std::string, std::string>::iterator it = test.begin();
	it++;
	std::cout << (*it).first << std::endl;
	it++;
	it++;
	it++;
	it--;
	it--;
	it--;
	it--;
	std::cout << (*it).first << std::endl;
	it--;
	it--;
	it--;
	it--;
	it++;
	it++;
	it++;
	it++;
	it++;
	std::cout << (*it).first << std::endl;
	/*
	ft::map<int, int>	test;
	test[42] = 42;
	test[21] = 21;
	ft::map<int, int>::iterator it = test.begin();
	++it;
	std::cout << (*it).second << std::endl;
	*/
	return (0);
}
