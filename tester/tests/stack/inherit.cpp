#if FT
# include "stack.hpp"
#elif STD
# include <stack>
#endif

#include <iostream>
#include <vector>

template<class T, class Container>
struct DumbStack : public NAMESPACE::stack<T, Container>
{
	// underlying container in stack should be named c and protected so it can be inherit
	typename NAMESPACE::stack<T, Container>::container_type	DumbGetter(void)
	{ return (this->c); }
};

int main(void)
{
	DumbStack< int, std::vector<int> >	test;
	test.push(42);
	DumbStack< int, std::vector<int> >::container_type	cont = test.DumbGetter();
	std::cout << *cont.begin() << std::endl;
}
