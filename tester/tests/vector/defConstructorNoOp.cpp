#if STD
# include <vector>
#elif FT
# include "vector.hpp"
#endif

#include <iostream>
#include <utility>

int	main(void)
{
	{
		NAMESPACE::vector<int>	test;
	}
	{
		NAMESPACE::vector<char>	test;
	}
	{
		NAMESPACE::vector< std::pair<int, int> >	test;
	}
	return (0);
}
