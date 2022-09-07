#if STD
# include <vector>
#elif FT
# include "vector.hpp"
#endif

#include <iostream>

int	main(void)
{
	NAMESPACE::vector<int>	test;
	std::cout << test.begin() - test.end() << std::endl;
	/*
	#if STD // STD Timed Out test
		while (true);
	#endif
	*/
	/*
	#if FT // FT Timed Out test
		while (true);
	#endif
	*/
	/*
	#if STD // STD CC fail test
		CC fail();
	#endif
	*/
	/*
	#if FT // FT CC fail test
		CC fail();
	#endif
	*/
	return (0);
}
