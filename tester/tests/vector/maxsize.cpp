#if FT
# include "vector.hpp"
#elif STD
# include <vector>
#endif

#include <iostream>
#include <utility>

struct	testClass
{
	int	Qua;
	int Rante;
	std::pair<int, int> Deux;
};

template<class T>
void	printMaxSize(const NAMESPACE::vector<T> &vec, const std::string &type)
{ std::cout << "vector max_size() for " << type << " : " << vec.max_size() << std::endl; }

int	main(void)
{
	printMaxSize(NAMESPACE::vector<int> (), "int");
	printMaxSize(NAMESPACE::vector<char> (), "char");
	printMaxSize(NAMESPACE::vector<std::string> (), "std::string");
	printMaxSize(NAMESPACE::vector<testClass> (), "testClass");
	printMaxSize(NAMESPACE::vector<long long int> (), "long long int");
	return (0);
}
