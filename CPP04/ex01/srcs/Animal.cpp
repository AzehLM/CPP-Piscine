#include <iostream>

#include "Animal.hpp"
#include "colors.h"

Animal::Animal(void) : _type("Animal") {
	std::cout << YELLOW << this->_type << " default constructor called" RESET << std::endl;
}

Animal::Animal(const std::string& type) : _type(type) {
	std::cout << YELLOW << this->_type << " (Animal class) parametric constructor called" RESET << std::endl;
}

Animal::Animal(const Animal& copyType) : _type(copyType._type) {
	std::cout << YELLOW << this->_type << " constructor by copy called" RESET << std::endl;
}

Animal::~Animal(void) {
	std::cout << "Animal destructor called" << std::endl;
}

Animal&	Animal::operator=(const Animal& copyType) {

	std::cout << BLUE "(Animal) Copy assignment operator called" RESET << std::endl;

	if (this != &copyType) {
		this->_type = copyType._type;
	}

	return (*this);
}

const std::string&	Animal::getType() const {
	return (this->_type);
}

void	Animal::makeSound() const {
	std::cout << MAGENTA << this->_type <<" does a *Whistling sound*" RESET << std::endl;
}
