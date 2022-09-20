#include "map.hpp"
#include "utility.hpp"
#include <map>
#include <iostream>
#include <utility>

int	main(void)
{
	/*
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
	}
	{
		ft::map<int, int>	test;
		test[42] = 42;
		test[21] = 21;
		ft::map<int, int>::iterator it = test.begin();
		++it;
		std::cout << (*it).second << std::endl;
	}
	*/
	{
		ft::map<int, int>	test;
		test.insert(ft::make_pair(42, 42));
		test[42] = 42; 
		test[21] = 21; 
		std::cout << test[42] << " " << test[21] << std::endl;
		ft::map<int, int>::iterator it = test.begin();
		ft::map<int, int>::const_iterator cit = test.begin();
		it++;
		cit++;
		it->second = 84;
		std::cout << "pair(" << cit->first << ", " << cit->second << ")" << std::endl;
		cit = it;
		std::cout << test.size() << std::endl;
		test.erase(test.begin(), test.end());
		std::cout << test.size() << std::endl;
	}
	return (0);
}
