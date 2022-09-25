#if STD
# include <vector>
#elif FT
# include "vector.hpp"
#endif

#include <iostream>
#include <memory>
#include <list>

template <class T>
class customAllocator : public std::allocator<T>
{};

template <class Vector>
void	printVec(const Vector &vec, size_t size, const std::string &name)
{
	for (size_t i = size; i < 100; i++)
		std::cout << name << '[' << i << "] : " << vec[i] << std::endl;
}

int	main(void)
{
	{
		NAMESPACE::vector< int, customAllocator<int> >	test;
	}
	{
		customAllocator<int>	_alloc;
		NAMESPACE::vector<int>	test (_alloc);
	}
	{
		std::list<int>	listTest;
		for (size_t i = 0; i < 100; i++)
			listTest.push_back(i * (i / 3) + i);
		NAMESPACE::vector<int>	vecTest (listTest.begin(), listTest.end());
		printVec(vecTest, 100, "vecTest");
	}
	{
		// check if iterator constructor protected against value_type same as size_type
		NAMESPACE::vector<int> test(100, 5);
		printVec(test, 100, "test");
	}
	return (0);
}
