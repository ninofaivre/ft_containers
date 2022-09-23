#if STD
# include <vector>
#elif FT
# include "vector.hpp"
#endif

#include <memory>
#include <iostream>

struct WRONG 
{
};

template <class T>
struct customAllocator : public std::allocator<T> //fail if get reference and creference by allocator
{
	typedef	WRONG		reference;
	typedef const WRONG	const_reference;
};

int	main(void)
{
	{
		typedef typename NAMESPACE::vector< int, customAllocator<int> >	tested_type;

		tested_type::value_type			test_value_type = 42;
		std::cout << test_value_type << std::endl;
		tested_type::allocator_type		test_allocator_type = customAllocator<int> ();
		std::cout << test_allocator_type.max_size() << std::endl;
		tested_type::size_type			test_size_type = 42;
		std::cout << test_size_type << std::endl;
		tested_type::difference_type	test_difference_type = 42;
		(void)test_difference_type;
		tested_type::reference			test_reference_type = test_value_type;
		std::cout << test_reference_type << std::endl;
		tested_type::const_reference	test_const_reference_type = test_value_type;
		std::cout << test_const_reference_type << std::endl;
		tested_type::pointer			test_pointer_type = &test_value_type;
		std::cout << *test_pointer_type << std::endl;
		tested_type::const_pointer		test_const_pointer_type = &test_value_type;
		std::cout << *test_const_pointer_type << std::endl;
	}
}
