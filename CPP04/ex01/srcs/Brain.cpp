#include <iostream>
#include <sstream>

#include "Brain.hpp"
#include "colors.h"

Brain::Brain(void) {

	for (int i = 0; i < 100; i++) {
		std::stringstream	id;
		id << i;
		this->_ideas[i] = "idea_number_";
		this->_ideas[i].append(id.str());
	}

	std::cout << YELLOW "Brain default constructor called" RESET << std::endl;
}

Brain::Brain(const Brain& copy) {

	*this = copy;

	std::cout << YELLOW "Brain copy constructor called" RESET << std::endl;
}

Brain::~Brain(void) {
	std::cout << "Brain destructor called" << std::endl;
}

Brain&	Brain::operator=(const Brain& src) {

	std::cout << BLUE "(Brain) copy assignment operator called" RESET << std::endl;

	if (this != &src) {
		for (int i = 0; i < 100; i++) {
			this->_ideas[i] = src._ideas[i];
		}
	}

	return (*this);
}

std::string	Brain::getIdea(int index) const {

	if (index < 0 || index >= 100)
		return ("Out of range");
	return (this->_ideas[index]);
}

void	Brain::setIdea(int index, std::string idea) {

	if (index < 0 || index >= 100)
		return ;
	_ideas[index] = idea;
}
