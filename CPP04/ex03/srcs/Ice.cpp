#include <iostream>

#include "colors.h"
#include "Ice.hpp"

Ice::Ice(void) : AMateria("ice") {}

Ice::Ice(const Ice& src) : AMateria(src) {}

Ice::~Ice(void) {}

Ice&	Ice::operator=(const Ice& src) {

	if (this != &src) {
		AMateria::operator=(src);
	}

	return (*this);
}

void	Ice::use(ICharacter& target) {
	std::cout << BLUE "* shoots an ice bolt at " << target.getName() << " *" RESET << std::endl;
}

AMateria*	Ice::clone() const {

	Ice* clone = new Ice(*this);

	return (clone);
}
