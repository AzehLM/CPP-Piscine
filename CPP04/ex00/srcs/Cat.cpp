#include <iostream>

#include "Cat.hpp"


Cat::Cat(void) : Animal("Cat") {
	std::cout << YELLOW << this->_type << " default constructor called" RESET << std::endl;
}

Cat::Cat(const Cat& copyName) : Animal(copyName) {
	std::cout << YELLOW << this->_type << " copy constructor called" RESET << std::endl;
}

Cat::~Cat(void) {
	std::cout << this->_type << " destructor called" << std::endl;
}

Cat&	Cat::operator=(const Cat& copyType) {

	if (this != &copyType) {
		this->_type = copyType._type;
	}

	std::cout << BLUE << this->_type << " copy assignment operator called" RESET << std::endl;

	return (*this);
}

void	Cat::makeSound() const {
	std::cout << MAGENTA "Meow" RESET << std::endl;
}
