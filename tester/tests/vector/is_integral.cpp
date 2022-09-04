#include "vector.hpp"

#include <iostream>
#include <string>
#include <vector>

template<class T>
void	oneTest(std::string name)
{
	name += " : ";
	std::cout << std::string(41, '-') << std::endl
			  << name <<  ft::is_integral<T>::value << std::endl
			  << "const " << name << ft::is_integral<const T>::value << std::endl
			  << "volatile " << name << ft::is_integral<volatile T>::value << std::endl
			  << "const volatile " << name << ft::is_integral<const volatile T>::value << std::endl;
}

int	main(void)
{
	oneTest<int *>("int *");
	oneTest<std::string>("std::string");
	oneTest<short>("short");
	oneTest<short int>("short");
	oneTest<signed short>("signed short");
	oneTest<unsigned short>("unsigned short");
	oneTest<unsigned short int>("unsigned short int");
	oneTest<int>("int");
	oneTest<signed>("signed");
	oneTest<signed int>("signed int");
	oneTest<unsigned>("unsigned");
	oneTest<unsigned int>("unsigned int");
	oneTest<long>("long");
	oneTest<long int>("long int");
	oneTest<signed long>("signed long");
	oneTest<signed long int>("signed long int");
	oneTest<unsigned long>("unsigned long");
	oneTest<unsigned long int>("unsigned long int");
	oneTest<long long>("long long");
	oneTest<long long int>("long long int");
	oneTest<signed long long>("signed long long");
	oneTest<signed long long int>("signed long long int");
	oneTest<unsigned long long>("unsigned long long int");
	oneTest<char>("char");
	oneTest<wchar_t>("wchar_t");
	oneTest<signed char>("signed char");
	oneTest<unsigned char>("unsigned char");
	oneTest<wint_t>("wint_t");
	std::cout << std::string(41, '-') << std::endl;
	return (0);
}
