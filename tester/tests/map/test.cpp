#include "map.hpp"
#include "utility.hpp"
#include <map>
#include <iostream>
#include <utility>
#include <memory>

template <class T_MAP, class T_IT>
void	isEnd(const T_MAP &map, const T_IT &it)
{ std::cout << (it == map.end() ? "it == end" : "cit != end") << std::endl; }

int	main(void)
{
	{
		NAMESPACE::map<int, int>	a;
		NAMESPACE::map<int, int>::const_iterator	cit = a.end();
		a[0] = 42;
		isEnd(a, cit);
		cit--;
		isEnd(a, cit);
		std::cout << cit->second << std::endl;
	}
	{
		NAMESPACE::map<int, int>	a;
		NAMESPACE::map<int, int>::const_iterator	cit = a.end();
		isEnd(a, cit);
		a[0] = 42;
	}
	{
		NAMESPACE::map<int, int>	a;
		NAMESPACE::map<int, int>	b;
		a[0] = 42;
		b[0] = 42;
		std::cout << (a == b ? "A identique à B" : "A différent de B") << std::endl;
	}
	return (0);
}
