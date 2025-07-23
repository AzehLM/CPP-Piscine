#include <iostream>

#include "AMateria.hpp"
#include "colors.h"

AMateria::AMateria(void) : _type("undefined") {}

AMateria::AMateria(const std::string& type) : _type(type) {}

AMateria::AMateria(const AMateria& copy) : _type(copy._type) {}

AMateria::~AMateria(void) {}

AMateria&	AMateria::operator=(const AMateria& copy) {

	if (this != &copy) {
		this->_type = copy._type;
	}

	return (*this);
}

const std::string&	AMateria::getType() const {
	return (this->_type);
}

void	AMateria::use(ICharacter& target) {
	std::cout << RED "AMateria " << target.getName() << " tried to use via AMateria." << std::endl;
}
	