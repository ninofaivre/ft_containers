#if FT
# include "vector.hpp"
#elif STD
# include <vector>
#endif

#include <iostream>

int	main(void)
{
	NAMESPACE::vector<int>::const_iterator::value_type	i = -42;
	NAMESPACE::vector<int>::const_iterator::pointer	ptr = &i;
	// reverse_iterator should inherit from iterator via iterator_traits
	NAMESPACE::vector<int>::const_reverse_iterator::iterator::value_type inherit = -42;
	inherit = 42;
	ptr = &i;
	i = 42;
	std::cout << i << std::endl;
	std::cout << *ptr << std::endl;
	std::cout << inherit << std::endl;
}
