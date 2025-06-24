#include <iostream>
#include <cmath>
#include <climits>

#include "Fixed.hpp"

const int	Fixed::_fractionalBits = 8;

std::ostream& operator<<(std::ostream& outStream, const Fixed& className)
{
	outStream << className.toFloat();

	return (outStream);
}



/* Constructors - Destructors */

Fixed::Fixed() : _fixedPointValue(0) {}

Fixed::~Fixed(void) {}

Fixed::Fixed(const Fixed& classCopyName)
{
	_fixedPointValue = classCopyName.getRawBits();
}

Fixed::Fixed(const int number)
{
	this->_fixedPointValue = number << this->_fractionalBits;
}

Fixed::Fixed(const float number)
{
	_fixedPointValue = roundf(number * (1 << this->_fractionalBits));
}



/* Getter - Setter */

int		Fixed::getRawBits(void) const
{
	return (this->_fixedPointValue);
}

void	Fixed::setRawBits(int const raw)
{
	this->_fixedPointValue = raw;
}



/* Convertors */

float	Fixed::toFloat(void) const
{
	return ((float) this->_fixedPointValue / (1 << this->_fractionalBits));
}

int	Fixed::toInt(void) const
{
	return (this->_fixedPointValue >> this->_fractionalBits);
}



/* Overload operators */

Fixed&	Fixed::operator=(const Fixed& className)
{
	this->setRawBits(className.getRawBits());

	return (*this);
}



/* Booleans */

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



/*  Arithmetic  */

Fixed Fixed::operator+(const Fixed& className) const
{
    if ((_fixedPointValue > 0 && className.getRawBits() > INT_MAX - _fixedPointValue) ||
        (_fixedPointValue < 0 && className.getRawBits() < INT_MIN - _fixedPointValue))
	{
        std::cout << "Overflow detected in addition, return: ";
        return Fixed(0);
    }

    Fixed ret;

    ret.setRawBits(_fixedPointValue + className.getRawBits());
    return (ret);
}

Fixed	Fixed::operator-(const Fixed& className) const
{
    if ((_fixedPointValue > 0 && className.getRawBits() < _fixedPointValue - INT_MAX) ||
        (_fixedPointValue < 0 && className.getRawBits() > _fixedPointValue - INT_MIN))
	{
        std::cout << "Overflow detected in subtraction, return: ";
        return Fixed(0);
    }

    Fixed ret;

    ret.setRawBits(_fixedPointValue - className.getRawBits());
    return (ret);
}

Fixed	Fixed::operator*(const Fixed& className) const
{
	long long int	resChecked;

	resChecked = (((long)this->getRawBits() * className.getRawBits()) >> _fractionalBits);

	if (resChecked > INT_MAX || resChecked < INT_MIN)
	{
		std::cout << "Overflow detected in multiplication, return: ";
		return (Fixed(0));
	}
	Fixed ret;

    ret.setRawBits((this->getRawBits() * className.getRawBits()) >> _fractionalBits);
    return (ret);
}

Fixed	Fixed::operator/(const Fixed& className) const
{

	if (className.getRawBits() == 0)
	{
		std::cout << "Division by 0 is impossible, return: ";
        return (Fixed(0));
    }

	long resChecked;

	resChecked = (((long)this->getRawBits() << _fractionalBits) / className.getRawBits());
	if (resChecked > INT_MAX || resChecked < INT_MIN)
	{
		std::cout << "Overflow detected in division, return: ";
		return (Fixed(0));
	}

    Fixed ret;

    ret.setRawBits((this->getRawBits() << _fractionalBits) / className.getRawBits());
    return (ret);
}



/* minimum/maximum */

Fixed&	Fixed::min(Fixed& className1, Fixed& className2)
{
	return (className1.getRawBits() < className2.getRawBits() ? className1 : className2);
}

Fixed&	Fixed::max(Fixed& className1, Fixed& className2)
{
	return (className1.getRawBits() > className2.getRawBits() ? className1 : className2);
}

const Fixed&	Fixed::min(const Fixed& className1, const Fixed& className2)
{
	return (className1.getRawBits() < className2.getRawBits() ? className1 : className2);
}

const Fixed&	Fixed::max(const Fixed& className1, const Fixed& className2)
{
	return (className1.getRawBits() > className2.getRawBits() ? className1 : className2);
}



/* Post/Pre-incrementation */

Fixed&	Fixed::operator++(void)
{
	_fixedPointValue++;
	return (*this);
}

Fixed&	Fixed::operator--(void)
{
	_fixedPointValue--;
	return (*this);
}

Fixed	Fixed::operator++(int)
{
	Fixed res = *this;

	_fixedPointValue++;
	return (res);
}

Fixed	Fixed::operator--(int)
{
	Fixed res = *this;

	_fixedPointValue--;
	return (res);
}
