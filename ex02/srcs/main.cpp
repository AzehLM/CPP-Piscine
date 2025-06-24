#include <iostream>

#include "Fixed.hpp"

std::ostream& operator<<(std::ostream& o, const Fixed& f);

int main(void)
{
	Fixed a(1.0f);
	Fixed b(1.01f);
	Fixed c(a);
	Fixed d(2.5f);

	std::cout << "--------------------" << std::endl;
	std::cout << "INIT VALUES:" << std::endl;
	std::cout << "\t" << BLUE"a = " << a << RESET << std::endl;
	std::cout << "\t" << BLUE"b = " << b << RESET << std::endl;
	std::cout << std::endl;

	std::cout << "--------------------" << std::endl;
	std::cout << "POST INCREMENT/DECREMENT:" << std::endl;
	std::cout << "\t" << BLUE "a++ = " << a++ << RESET <<  std::endl;
	std::cout << "\t" << GREEN "a = " << a << RESET << std::endl;
	std::cout << "\t" << BLUE "a-- = " << a-- << RESET << std::endl;
	std::cout << "\t" << GREEN "a = " << a << RESET << std::endl;
	std::cout << std::endl;

	std::cout << "--------------------" << std::endl;
	std::cout << "PRE INCREMENT/DECREMENT:" << std::endl;
	std::cout << "\t" << GREEN"++a = " << ++a << RESET << std::endl;
	std::cout << "\t" << BLUE"a = " << a << RESET << std::endl;
	std::cout << "\t" << GREEN"--a = " << --a << RESET << std::endl;
	std::cout << "\t" << BLUE"a = " << a << RESET << std::endl;
	std::cout << std::endl;

	std::cout << "--------------------" << std::endl;
	std::cout << "COMPARISONS:" << std::endl;
	std::cout << "\t" << BLUE "a = " << a << RESET << std::endl;
	std::cout << "\t" << BLUE "b = " << b << RESET << std::endl;
	std::cout << "\t" << BLUE "c = " << c << RESET << std::endl;
	std::cout << std::endl;
	std::cout << "\t" << GREEN "a < b: " << (a < b) << RESET << std::endl;
	std::cout << "\t" << GREEN "b < a: " << (b < a) << RESET << std::endl;
	std::cout << "\t" << GREEN "a <= b: " << (a <= b) << RESET << std::endl;
	std::cout << "\t" << GREEN "b <= a: " << (b <= a) << RESET << std::endl;
	std::cout << "\t" << GREEN "a <= c: " << (a <= c) << RESET << std::endl;
	std::cout << std::endl;
	std::cout << "\t" << GREEN "a > b: " << (a > b) << RESET << std::endl;
	std::cout << "\t" << GREEN "b > a: " << (b > a) << RESET << std::endl;
	std::cout << "\t" << GREEN "a >= b: " << (a >= b) << RESET << std::endl;
	std::cout << "\t" << GREEN "b >= a: " << (b >= a) << RESET << std::endl;
	std::cout << "\t" << GREEN "a >= c: " << (a >= c) << RESET << std::endl;
	std::cout << std::endl;
	std::cout << "\t" << GREEN "a == b: " << (a == b) << RESET << std::endl;
	std::cout << "\t" << GREEN "a == c: " << (a == c) << RESET << std::endl;
	std::cout << "\t" << GREEN "a != b: " << (a != b) << RESET << std::endl;
	std::cout << "\t" << GREEN "a != c: " << (a != c) << RESET << std::endl;
	std::cout << std::endl;

	std::cout << "--------------------" << std::endl;
	std::cout << "OPERATIONS:" << std::endl;
	std::cout << "\t" << BLUE "a = " << a << RESET << std::endl;
	std::cout << "\t" << BLUE "b = " << b << RESET << std::endl;
	std::cout << "\t" << BLUE "d = " << d << RESET << std::endl;
	std::cout << "\t" << GREEN "a + b = " << a + b << RESET << std::endl;
	std::cout << "\t" << GREEN "a - b = " << a - b << RESET << std::endl;
	std::cout << "\t" << GREEN "d - a = " << d - a << RESET << std::endl;
	std::cout << "\t" << GREEN "a * d = " << a * d << RESET << std::endl;
	std::cout << "\t" << GREEN "d * a = " << d * a << RESET << std::endl;
	std::cout << "\t" << RED "d * (d - a) = " << d * (d - a) << RESET << std::endl;
	std::cout << "\t" << RED "a / Fixed(2.0f) = " << a / Fixed(2.0f) << RESET << std::endl;
	std::cout << "\t" << RED "a / Fixed(2.0f) * Fixed(2.0f) = " << a / Fixed(2.0f) * Fixed(2.0f) << RESET << std::endl;
	std::cout << std::endl;

	std::cout << "--------------------" << std::endl;
	std::cout << "MIN/MAX:" << std::endl;
	std::cout << "\t" << BLUE "a = " << a << RESET << std::endl;
	std::cout << "\t" << BLUE "b = " << b << RESET << std::endl;
	std::cout << "\t" << GREEN "min(a, b) = " << Fixed::min(a, b) << RESET << std::endl;
	std::cout << "\t" << GREEN "max(a, b) = " << Fixed::max(a, b) << RESET << std::endl;
	std::cout << std::endl;


	// Fixed a;

	// Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );

	// std::cout << "1: " << a << std::endl;
	// std::cout << "2: " << ++a << std::endl;
	// std::cout << "3: " << a << std::endl;
	// std::cout << "4: " << a++ << std::endl;
	// std::cout << "5: " << a << std::endl;
	// std::cout << b << std::endl;

	// std::cout << Fixed::max( a, b ) << std::endl;

	return (0);
}
