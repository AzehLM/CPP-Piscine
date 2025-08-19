#include <cerrno>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter(void) {}

ScalarConverter::ScalarConverter(const ScalarConverter&) {}

ScalarConverter&	ScalarConverter::operator=(const ScalarConverter&) { return (*this); }

ScalarConverter::~ScalarConverter(void) {}

void ScalarConverter::convert(const std::string& convert) {

	bool	validNumber = true;
	char	*endPtr = NULL;
	double	nb = 0;

	if (convert.length() == 1 && !std::isdigit(convert[0])) {
		nb = static_cast<double>(convert[0]);
		validNumber = false;  // Single char is valid for conversion but I decided to set it to false since one digit char are non-printable characters
	} else {
		errno = 0;
		nb = strtod(convert.c_str(), &endPtr);
		// Here we check errno value because the only error strtod can send is an out of range value.
		// We also check if endptr points to the beginning of the string
		if (errno == ERANGE || endPtr == convert.c_str()) {
			validNumber = false;
			errno = 0;
		} else if (*endPtr != '\0') {
			if (*endPtr != 'f' || *(endPtr + 1) != '\0') {
				validNumber = false;
			}
		}
	}

	ScalarConverter::printChar(nb, validNumber);
	ScalarConverter::printInt(nb, validNumber);
	ScalarConverter::printFloat(nb, validNumber);
	ScalarConverter::printDouble(nb, validNumber);
}

void ScalarConverter::printChar(const double nb, const bool valid) {

	std::cout << "char: ";

	if (!valid || std::isnan(nb) || std::isinf(nb) || nb < std::numeric_limits<char>::min() || nb > std::numeric_limits<char>::max()) {
		std::cout << "impossible" << std::endl;
		return ;
	}

	char c = static_cast<char>(nb);

	if (!std::isprint(c)) {
		std::cout << "Non displayable" << std::endl;
		return;
	}

	std::cout << "'" << c << "'" << std::endl;
}

void	ScalarConverter::printInt(const double nb, const bool valid) {

	std::cout << "int: ";

	if (!valid || nb >  std::numeric_limits<int>::max() || nb < std::numeric_limits<int>::min() || std::isnan(nb)) {
		std::cout << "impossible" << std::endl;
		return ;
	}

	int	i = static_cast<int>(nb);
	std::cout << i << std::endl;
}

void	ScalarConverter::printFloat(const double nb, const bool valid) {

	std::cout << "float: ";

	if (!valid || (!std::isinf(nb) && (nb > std::numeric_limits<float>::max() || nb < -std::numeric_limits<float>::max()))) {
		std::cout << "impossible" << std::endl;
		return ;
	}

	float f = static_cast<float>(nb);
	std::cout << std::fixed << std::setprecision(1) << f << 'f' << std::endl;
}

void	ScalarConverter::printDouble(const double nb, const bool valid) {

	std::cout << "double: ";

	if (!valid || (!std::isinf(nb) && (nb > std::numeric_limits<double>::max() || nb < -std::numeric_limits<double>::max())) ) {
		std::cout << "impossible" << std::endl;
		return ;
	}

	double d = static_cast<double>(nb);

	std::cout << d << std::endl;
}
