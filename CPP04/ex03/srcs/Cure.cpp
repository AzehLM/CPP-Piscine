#include <iostream>

#include "colors.h"
#include "Cure.hpp"

Cure::Cure(void) : AMateria("cure") {}

Cure::Cure(const Cure& src) : AMateria(src) {}

Cure::~Cure(void) {}

Cure&	Cure::operator=(const Cure& src) {

	if (this != &src) {
		AMateria::operator=(src);
	}

	return (*this);
}

void	Cure::use(ICharacter& target) {
	std::cout << GREEN "* heals " << target.getName() << "'s wounds *" RESET << std::endl;
}

AMateria*	Cure::clone() const {

	Cure* clone = new Cure(*this);

	return (clone);
}
