#include <iostream>

#include "WrongCat.hpp"
#include "colors.h"

WrongCat::WrongCat() : WrongAnimal("Cat") {
	std::cout << YELLOW << this->_type << " default constructor called" RESET << std::endl;
}

WrongCat::WrongCat(const WrongCat& copyName) : WrongAnimal(copyName) {
	std::cout << YELLOW << this->_type << " copy constructor called" RESET << std::endl;
}

WrongCat::~WrongCat() {
	std::cout << this->_type << " destructor called" << std::endl;
}

WrongCat&	WrongCat::operator=(const WrongCat& copyName) {

	std::cout << BLUE << this->_type << " copy assigment operator called" RESET << std::endl;

	if (this != &copyName) {
		this->_type = copyName._type;
	}

	return (*this);
}

void	WrongCat::makeSound() const {
	std::cout << MAGENTA "Meow but sounds kinda wrong" RESET << std::endl;
}
