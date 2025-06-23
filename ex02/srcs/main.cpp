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
    std::cout << "\t" << "a = " << a << std::endl;
    std::cout << "\t" << "b = " << b << std::endl;
    std::cout << std::endl;

    std::cout << "--------------------" << std::endl;
    std::cout << "POST INCREMENT/DECREMENT:" << std::endl;
    std::cout << "\t" << "a++ = " << a++ << std::endl;
    std::cout << "\t" << "a = " << a << std::endl;
    std::cout << "\t" << "a-- = " << a-- << std::endl;
    std::cout << "\t" << "a = " << a << std::endl;
    std::cout << std::endl;

    std::cout << "--------------------" << std::endl;
    std::cout << "PRE INCREMENT/DECREMENT:" << std::endl;
    std::cout << "\t" << "++a = " << ++a << std::endl;
    std::cout << "\t" << "a = " << a << std::endl;
    std::cout << "\t" << "--a = " << --a << std::endl;
    std::cout << "\t" << "a = " << a << std::endl;
    std::cout << std::endl;

    std::cout << "--------------------" << std::endl;
    std::cout << "COMPARISONS:" << std::endl;
    std::cout << "\t" << "a = " << a << std::endl;
    std::cout << "\t" << "b = " << b << std::endl;
    std::cout << "\t" << "c = " << c << std::endl;
    std::cout << std::endl;
    std::cout << "\t" << "a < b: " << (a < b) << std::endl;
    std::cout << "\t" << "b < a: " << (b < a) << std::endl;
    std::cout << "\t" << "a <= b: " << (a <= b) << std::endl;
    std::cout << "\t" << "b <= a: " << (b <= a) << std::endl;
    std::cout << "\t" << "a <= c: " << (a <= c) << std::endl;
    std::cout << std::endl;
    std::cout << "\t" << "a > b: " << (a > b) << std::endl;
    std::cout << "\t" << "b > a: " << (b > a) << std::endl;
    std::cout << "\t" << "a >= b: " << (a >= b) << std::endl;
    std::cout << "\t" << "b >= a: " << (b >= a) << std::endl;
    std::cout << "\t" << "a >= c: " << (a >= c) << std::endl;
    std::cout << std::endl;
    std::cout << "\t" << "a == b: " << (a == b) << std::endl;
    std::cout << "\t" << "a == c: " << (a == c) << std::endl;
    std::cout << "\t" << "a != b: " << (a != b) << std::endl;
    std::cout << "\t" << "a != c: " << (a != c) << std::endl;
    std::cout << std::endl;

    std::cout << "--------------------" << std::endl;
    std::cout << "OPERATIONS:" << std::endl;
    std::cout << "\t" << "a = " << a << std::endl;
    std::cout << "\t" << "b = " << b << std::endl;
    std::cout << "\t" << "d = " << d << std::endl;
    std::cout << "\t" << "a + b = " << a + b << std::endl;
    std::cout << "\t" << "a - b = " << a - b << std::endl;
    std::cout << "\t" << "d - a = " << d - a << std::endl;
    std::cout << "\t" << "a * d = " << a * d << std::endl;
    std::cout << "\t" << "d * a = " << d * a << std::endl;
    std::cout << "\t" << "d * (d - a) = " << d * (d - a) << std::endl;
    std::cout << "\t" << "a / Fixed(2.0f) = " << a / Fixed(2.0f) << std::endl;
    std::cout << "\t" << "a / Fixed(2.0f) * Fixed(2.0f) = " << a / Fixed(2.0f) * Fixed(2.0f) << std::endl;
    std::cout << std::endl;

    std::cout << "--------------------" << std::endl;
    std::cout << "MIN/MAX:" << std::endl;
    std::cout << "\t" << "a = " << a << std::endl;
    std::cout << "\t" << "b = " << b << std::endl;
    std::cout << "\t" << "min(a, b) = " << Fixed::min(a, b) << std::endl;
    std::cout << "\t" << "max(a, b) = " << Fixed::max(a, b) << std::endl;
    std::cout << std::endl;


    // Fixed a;

    // Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );

    // std::cout << a << std::endl;
    // std::cout << ++a << std::endl;
    // std::cout << a << std::endl;
    // std::cout << a++ << std::endl;
    // std::cout << a << std::endl;
    // std::cout << b << std::endl;

    // std::cout << Fixed::max( a, b ) << std::endl;

    return (0);
}
