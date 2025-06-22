#include <iostream>
#include <cmath>

#include "Fixed.hpp"

const int	Fixed::_fractionalBits = 8;

Fixed::Fixed() : _fixedPointValue(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::~Fixed(void)
{
	std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(const Fixed& classCopyName)
{
	std::cout << "Copy constructor called" << std::endl;

	_fixedPointValue = classCopyName.getRawBits();
}



Fixed::Fixed(const int number)
{
	std::cout << "Int constructor called" << std::endl;

	this->_fixedPointValue = number << this->_fractionalBits;
}

Fixed::Fixed(const float number)
{
	std::cout << "Float constructor called" << std::endl;

	_fixedPointValue = roundf(number * (1 << this->_fractionalBits));
}






int		Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member function called" << std::endl;

	return (this->_fixedPointValue);
}

void	Fixed::setRawBits(int const raw)
{
	this->_fixedPointValue = raw;
}

float	Fixed::toFloat(void) const
{
	return ((float) this->_fixedPointValue / (1 << this->_fractionalBits));
}

int	Fixed::toInt(void) const
{
	return (this->_fixedPointValue >> this->_fractionalBits);
}

std::ostream& operator<<(std::ostream& outStream, const Fixed& className)
{
	outStream << className.toFloat();

	return (outStream);
}

Fixed&	Fixed::operator=(const Fixed& className)
{
	std::cout << "Copy assignment operator called" << std::endl;

	this->setRawBits(className.getRawBits());

	return (*this);
}

/*  booleans */

bool	Fixed::operator>(const Fixed& className) const
{
	return (this->getRawBits() > className.getRawBits());
}

bool	Fixed::operator<(const Fixed& className) const
{
	return (this->getRawBits() < className.getRawBits());
}

bool	Fixed::operator>=(const Fixed& className) const
{
	return (this->getRawBits() >= className.getRawBits());
}

bool	Fixed::operator<=(const Fixed& className) const
{
	return (this->getRawBits() <= className.getRawBits());
}

bool	Fixed::operator==(const Fixed& className) const
{
	return (this->getRawBits() == className.getRawBits());
}

bool	Fixed::operator!=(const Fixed& className) const
{
	return (this->getRawBits() != className.getRawBits());
}
