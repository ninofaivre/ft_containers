#include "vector.hpp"

#include <vector>

int	main(void)
{
	NAMESPACE::vector<int>	intTest;
	for (int i = 0; i < 10000; i++)
		intTest.push_back(i);
	return (0);
}
