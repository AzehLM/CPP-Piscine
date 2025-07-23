#include <iostream>

#include "Cat.hpp"
#include "colors.h"


Cat::Cat(void) : Animal("Cat"), _brainIdeas(new Brain()) {
	std::cout << YELLOW << this->_type << " default constructor called" RESET << std::endl;
}

Cat::Cat(const Cat& copyName) : Animal(copyName), _brainIdeas(new Brain(*copyName._brainIdeas)) {
	std::cout << YELLOW << this->_type << " copy constructor called" RESET << std::endl;
}

Cat::~Cat(void) {

	delete this->_brainIdeas;

	std::cout << this->_type << " destructor called" << std::endl;
}

Cat&	Cat::operator=(const Cat& copyType) {

	std::cout << BLUE << this->_type << " copy assignment operator called" RESET << std::endl;

	if (this != &copyType) {
		Animal::operator=(copyType);
		delete this->_brainIdeas;
		this->_brainIdeas = new Brain(*copyType._brainIdeas
		);
	}

	return (*this);
}

void	Cat::makeSound() const {
	std::cout << MAGENTA "Meow" RESET << std::endl;
}

std::string	Cat::getIdea(int index) const {
	return (this->_brainIdeas->getIdea(index));
}

void	Cat::setIdea(int index, std::string idea) {
	this->_brainIdeas->setIdea(index, idea);
}
