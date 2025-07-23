#include <iostream>

#include "Dog.hpp"
#include "colors.h"


Dog::Dog(void) : Animal("Dog"), _brainIdeas(new Brain()) {
	std::cout << YELLOW << this->_type << " default constructor called" RESET << std::endl;
}

Dog::Dog(const Dog& copyName) : Animal(copyName), _brainIdeas(new Brain(*copyName._brainIdeas)) {
	std::cout << YELLOW << this->_type << " copy constructor called" RESET << std::endl;
}

Dog::~Dog(void) {

	delete this->_brainIdeas;

	std::cout << this->_type << " destructor called" << std::endl;
}

Dog&	Dog::operator=(const Dog& copyType) {

	std::cout << BLUE << this->_type << " copy assignment operator called" RESET << std::endl;

	if (this != &copyType) {
		Animal::operator=(copyType);
		delete this->_brainIdeas;
		this->_brainIdeas = new Brain(*copyType._brainIdeas);
	}

	return (*this);
}

void	Dog::makeSound() const {
	std::cout << MAGENTA "Bark" RESET << std::endl;
}

std::string	Dog::getIdea(int index) const {
	return (this->_brainIdeas->getIdea(index));
}

void	Dog::setIdea(int index, std::string idea) {
	this->_brainIdeas->setIdea(index, idea);
}
