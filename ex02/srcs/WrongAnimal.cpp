#include <iostream>

#include "WrongAnimal.hpp"
#include "colors.h"

WrongAnimal::WrongAnimal(void) : _type("WrongAnimal") {
	std::cout << YELLOW << this->_type << " default constructor called" RESET << std::endl;
}

WrongAnimal::WrongAnimal(const std::string& type) : _type(type) {
	std::cout << YELLOW << this->_type << " (WrongAnimal class) parametric constructor called" << RESET << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& copyType) : _type(copyType._type) {
	std::cout << YELLOW << this->_type << " constructor by copy called" RESET << std::endl;
}

WrongAnimal::~WrongAnimal(void) {
	std::cout << "WrongAnimal destructor called" << std::endl;
}

WrongAnimal&	WrongAnimal::operator=(const WrongAnimal& copyType) {

	std::cout << BLUE "(WrongAnimal) Copy assignment operator called" RESET << std::endl;

	if (this != &copyType) {
		this->_type = copyType._type;
	}

	return (*this);
}

const std::string&	WrongAnimal::getType() const {
	return (this->_type);
}

void	WrongAnimal::makeSound() const {
	std::cout << MAGENTA "Sounds wrong right ?" RESET << std::endl;
}
