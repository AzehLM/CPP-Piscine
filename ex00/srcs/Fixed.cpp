#include <iostream>

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

Fixed::Fixed(Fixed& classCopyName)
{
	std::cout << "Copy constructor called" << std::endl;

	*this = classCopyName;
}

Fixed&	Fixed::operator=(Fixed& classCopyName)
{
	std::cout << "Copy assignment operator called" << std::endl;
	this->setRawBits(classCopyName.getRawBits());
	return (*this);
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
