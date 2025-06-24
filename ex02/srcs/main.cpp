

#include <iostream>
#include <climits>

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
	std::cout << "\t" << GREEN "d * (d - a) = " << d * (d - a) << RESET << std::endl;
	std::cout << "\t" << GREEN "a / Fixed(2.0f) = " << a / Fixed(2.0f) << RESET << std::endl;
	std::cout << "\t" << GREEN "a / Fixed(2.0f) * Fixed(2.0f) = " << a / Fixed(2.0f) * Fixed(2.0f) << RESET << std::endl;
	std::cout << std::endl;

	std::cout << "--------------------" << std::endl;
	std::cout << "MIN/MAX:" << std::endl;
	std::cout << "\t" << BLUE "a = " << a << RESET << std::endl;
	std::cout << "\t" << BLUE "b = " << b << RESET << std::endl;
	std::cout << "\t" << GREEN "min(a, b) = " << Fixed::min(a, b) << RESET << std::endl;
	std::cout << "\t" << GREEN "max(a, b) = " << Fixed::max(a, b) << RESET << std::endl;
	std::cout << std::endl;


	std::cout << "--------------------" << std::endl;
	std::cout <<  "TEST DIVISION PAR ZÉRO:" RESET << std::endl;
	Fixed zero(0);
	std::cout << "\t" << BLUE "a = " << a << RESET << std::endl;
	std::cout << "\t" << BLUE "zero = " << zero << RESET << std::endl;
	std::cout << "\t" << RED "a / zero = " << (a / zero) << RESET << std::endl;

	std::cout << "--------------------" << std::endl;
	std::cout <<  "TEST OVERFLOW ADDITION:" RESET << std::endl;

	Fixed maxVal;
	maxVal.setRawBits(INT_MAX - 100);
	Fixed largeVal;
	largeVal.setRawBits(200);
	std::cout << "\t" << BLUE "maxVal (raw: " << maxVal.getRawBits() << ") = " << maxVal << RESET << std::endl;
	std::cout << "\t" << BLUE "largeVal (raw: " << largeVal.getRawBits() << ") = " << largeVal << RESET << std::endl;
	std::cout << "\t" << RED "maxVal + largeVal = " << (maxVal + largeVal) << RESET << std::endl;
	std::cout << std::endl;

	std::cout << "--------------------" << std::endl;
	std::cout <<  "TEST OVERFLOW SOUSTRACTION:" RESET << std::endl;

	Fixed minVal;
	minVal.setRawBits(INT_MIN + 100);
	Fixed negLargeVal;
	negLargeVal.setRawBits(-200);

	std::cout << "\t" << BLUE "minVal (raw: " << minVal.getRawBits() << ") = " << minVal << RESET << std::endl;
	std::cout << "\t" << BLUE "negLargeVal (raw: " << negLargeVal.getRawBits() << ") = " << negLargeVal << RESET << std::endl;
	std::cout << "\t" << RED "minVal - largeVal = " << (minVal - largeVal) << RESET << std::endl;
	std::cout << std::endl;

	std::cout << "--------------------" << std::endl;
	std::cout <<  "TEST OVERFLOW MULTIPLICATION:" RESET << std::endl;

	Fixed bigVal1;
	bigVal1.setRawBits(46340 << 8);
	Fixed bigVal2;
	bigVal2.setRawBits(46341 << 8);

	std::cout << "\t" << BLUE "bigVal1 = " << bigVal1 << RESET << std::endl;
	std::cout << "\t" << BLUE "bigVal2 = " << bigVal2 << RESET << std::endl;
	std::cout << "\t" << RED "bigVal1 * bigVal2 = " << (bigVal1 * bigVal2) << RESET << std::endl;
	std::cout << std::endl;

	std::cout << "--------------------" << std::endl;
	std::cout <<  "TEST OVERFLOW DIVISION:" RESET << std::endl;

	Fixed veryLargeVal;
	veryLargeVal.setRawBits(INT_MAX);
	Fixed verySmallVal;
	verySmallVal.setRawBits(1);

	std::cout << "\t" << BLUE "veryLargeVal (raw: " << veryLargeVal.getRawBits() << ") = " << veryLargeVal << RESET << std::endl;
	std::cout << "\t" << BLUE "verySmallVal (raw: " << verySmallVal.getRawBits() << ") = " << verySmallVal << RESET << std::endl;
	std::cout << "\t" << RED "veryLargeVal / verySmallVal = " << (veryLargeVal / verySmallVal) << RESET << std::endl;
	std::cout << std::endl;

	std::cout << "--------------------" << std::endl;
	std::cout <<  "TESTS AVEC VALEURS LIMITES:" RESET << std::endl;

	Fixed maxFixed;
	maxFixed.setRawBits(INT_MAX);
	Fixed minFixed;
	minFixed.setRawBits(INT_MIN);
	Fixed one(1);

	std::cout << "\t" << BLUE "maxFixed = " << maxFixed << RESET << std::endl;
	std::cout << "\t" << BLUE "minFixed = " << minFixed << RESET << std::endl;
	std::cout << "\t" << BLUE "one = " << one << RESET << std::endl;
	std::cout << std::endl;

	std::cout << "\t" << RED "maxFixed + one = " << (maxFixed + one) << RESET << std::endl;
	std::cout << "\t" << RED "minFixed - one = " << (minFixed - one) << RESET << std::endl;
	std::cout << "\t" << RED "maxFixed * Fixed(2) = " << (maxFixed * Fixed(2)) << RESET << std::endl;
	std::cout << "\t" << RED "minFixed / Fixed(0.5f) = " << (minFixed / Fixed(0.5f)) << RESET << std::endl;
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
