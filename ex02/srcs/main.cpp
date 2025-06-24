#include <iostream>
#include <climits>

#include "Fixed.hpp"

std::ostream& operator<<(std::ostream& outStream, const Fixed& className);

int main(void)
{
	Fixed a;

	Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );

	std::cout << "1: " << a << std::endl;
	std::cout << "2: " << ++a << std::endl;
	std::cout << "3: " << a << std::endl;
	std::cout << "4: " << a++ << std::endl;
	std::cout << "5: " << a << std::endl;
	std::cout << b << std::endl;

	std::cout << Fixed::max( a, b ) << std::endl;

	return (0);
}
