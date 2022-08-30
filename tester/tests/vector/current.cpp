#include "vector.hpp"

#include <iostream>
#include <string>
#include <vector>

int	main(void)
{
	NAMESPACE::vector<std::string>	vct(10);
	for (unsigned long int i = 0; i < vct.size(); i++)
		vct[i] = std::string(vct.size() - i, i + 65);
	NAMESPACE::vector<std::string>::const_iterator const it;
	it = vct.erase(vct.begin());
	std::cout << it - vct.begin() << std::endl;
	return (0);
}
