#include <iostream>

#include "colors.h"
#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"

AForm*	Intern::createShrubberyForm(const std::string& target) {
	return new ShrubberyCreationForm(target);
}

AForm*	Intern::createRobotomyForm(const std::string& target) {
	return new RobotomyRequestForm(target);
}

AForm*	Intern::createPresidentialForm(const std::string& target) {
	return new PresidentialPardonForm(target);
}

Intern::Intern(void) {
	std::cout << YELLOW "Intern default constructor called" RESET << std::endl;
}

Intern::Intern(const Intern& src) {
	(void) src;
	std::cout << YELLOW "Intern constructor by copy called" RESET << std::endl;
}

Intern::~Intern(void) {
	std::cout << "Intern " RED "destructor" RESET " called" << std::endl;
}

Intern&	Intern::operator=(const Intern& src) {
	(void) src;
	std::cout << BLUE "Assigment operator = called on Intern" RESET << std::endl;

	return (*this);
}

const Intern::FormCreator	Intern::formCreator[3] = {
	{"shrubbery creation", &createShrubberyForm},
	{"robotomy request", &createRobotomyForm},
	{"presidential pardon", &createPresidentialForm}
};

AForm*	Intern::makeForm(const std::string& formName, const std::string& target) {

	for (int i = 0; i < 3; i++) {
		if (formCreator[i].formName == formName) {
			std::cout << "Intern creates " << BLUE << formName << RESET << std::endl;
			return (formCreator[i].create(target));
		}
	}

	std::cout << RED "Form name '" << formName << "' doesn't exist" RESET << std::endl;

	return (NULL);
}
