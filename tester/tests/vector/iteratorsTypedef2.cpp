#if FT
# include "vector.hpp"
#elif STD
# include <vector>
#endif

#include <iostream>

//Failure test none of this should compile

int	main(void)
{
	NAMESPACE::vector<int>::const_iterator::value_type	i = -42; //value_type should be not const
	NAMESPACE::vector<int>::const_iterator::pointer		ptr = &i; // ptr should be const
	NAMESPACE::vector<int>::const_iterator::reference	ref = i; // ref should be const
	// vector iterator should not inherit from iterator (even if you do it via iterator_traits)
	NAMESPACE::vector<int>::iterator::value_type 		inherit = 42;
	ref = i; // ref should be const
	ptr = &i; // should work
	*ptr = 42; // ptr should be const
	i = 42; //value_type should be not const
	std::cout << i << std::endl;
	std::cout << *ptr << std::endl;
	std::cout << inherit << std::endl;
	return (0);
}
