#include <iostream>

#include "Dog.hpp"


Dog::Dog(void) : Animal("Dog") {
	std::cout << YELLOW << this->_type << " default constructor called" RESET << std::endl;
}

Dog::Dog(const Dog& copyName) : Animal(copyName) {
	std::cout << YELLOW << this->_type << " copy constructor called" RESET << std::endl;
}

Dog::~Dog(void) {
	std::cout << this->_type << " destructor called" << std::endl;
}

Dog&	Dog::operator=(const Dog& copyType) {

	if (this != &copyType) {
		this->_type = copyType._type;
	}

	std::cout << BLUE << this->_type << " copy assignment operator called" RESET << std::endl;

	return (*this);
}

void	Dog::makeSound() const {
	std::cout << MAGENTA "Bark" RESET << std::endl;
}
