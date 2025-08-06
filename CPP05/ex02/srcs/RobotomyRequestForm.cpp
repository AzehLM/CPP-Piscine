#include <cstdlib>

#include "colors.h"
#include "RobotomyRequestForm.hpp"


RobotomyRequestForm::RobotomyRequestForm(void) : AForm("Default RobotomyForm", RobotomyRequestForm::SIGN_GRADE, RobotomyRequestForm::EXEC_GRADE), _target("Default Target") {
	std::cout << YELLOW "RobotomyRequestForm (" << this->getName() << ") default constructor called" RESET << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const std::string& target) :  AForm("RobotomyRequestForm", RobotomyRequestForm::SIGN_GRADE, RobotomyRequestForm::EXEC_GRADE), _target(target) {
	std::cout << YELLOW "RobotomyRequestForm (" << this->getName() << ") parametric constructor called" RESET << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& src) : AForm(src), _target(src._target) {
	std::cout << YELLOW "RobotomyRequestForm (" << this->getName() << ") constructor by copy called" RESET << std::endl;
}

RobotomyRequestForm::~RobotomyRequestForm(void) {
	std::cout << "RobotomyRequestForm (" << this->getName() <<  ")" << RED " destructor" RESET << " called" << std::endl;
}

RobotomyRequestForm&	RobotomyRequestForm::operator=(const RobotomyRequestForm& src) {

	if (this != &src) {
		AForm::operator=(src);
		_target = src._target;
	}

	std::cout << BLUE "Assignment operator = called on " << this->getName() << RESET << std::endl;
	return (*this);
}

void	RobotomyRequestForm::executeForm(void) const {

	std::cout << MAGENTA "Brrrrzzzzzzz: ";
	if (rand() % 2 == 0) {
		std::cout << this->getTarget() << " has been robotomized successfully." RESET << std::endl;
	} else {
		std::cout << "Robotomization has failed..." RESET << std::endl;
	}
}

std::string	RobotomyRequestForm::getTarget(void) const {
	return (this->_target);
}
