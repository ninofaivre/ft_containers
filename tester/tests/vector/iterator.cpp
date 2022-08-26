#include "vector.hpp"

#include <vector>
#include <iostream>

int	main(void)
{
	{
		NAMESPACE::vector<int>	test;
		test.push_back(42);
		test.push_back(21);
		test.push_back(84);
		NAMESPACE::vector<int>::iterator itBegin = test.begin();
		NAMESPACE::vector<int>::iterator itEnd = test.end();
		std::cout << "*itBegin : " << *itBegin << std::endl
				  << "*(itEnd - 1) : " << *(itEnd - 1) << std::endl
				  << "*(itEnd - 2) : " << *(itEnd - 2) << std::endl
				  << "*(itBegin + 1) : " << *(itBegin + 1) << std::endl;
		itBegin++;
		itEnd--;
		std::cout << "itBegin++" << std::endl
				  << "itEnd--" << std::endl
				  << "*itBegin : " << *itBegin << std::endl
				  << "*itEnd : " << *itEnd << std::endl;
	}
	std::cout << std::string(60, '-') << std::endl;
	{
		NAMESPACE::vector<char>	test;
		test.push_back('*');
		test.push_back('z');
		test.push_back('-');
		NAMESPACE::vector<char>::iterator itBegin = test.begin();
		NAMESPACE::vector<char>::iterator itEnd = test.end();
		std::cout << "*itBegin : " << *itBegin << std::endl
				  << "*(itEnd - 1) : " << *(itEnd - 1) << std::endl
				  << "*(itEnd - 2) : " << *(itEnd - 2) << std::endl
				  << "*(itBegin + 1) : " << *(itBegin + 1) << std::endl;
		itBegin++;
		itEnd--;
		std::cout << "itBegin++" << std::endl
				  << "itEnd--" << std::endl
				  << "*itBegin : " << *itBegin << std::endl
				  << "*itEnd : " << *itEnd << std::endl;
	}
	return (0);
}
