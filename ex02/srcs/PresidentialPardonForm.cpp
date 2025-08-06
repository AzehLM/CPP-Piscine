#include "colors.h"
#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(void) : AForm("Default PresidentialForm", PresidentialPardonForm::SIGN_GRADE, PresidentialPardonForm::EXEC_GRADE), _target("Default Target") {
	std::cout << YELLOW "PresidentialPardonForm (" << this->getName() << ") default constructor called" RESET << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const std::string& target) : AForm("PresidentialPardonForm", PresidentialPardonForm::SIGN_GRADE, PresidentialPardonForm::EXEC_GRADE), _target(target) {
	std::cout << YELLOW "PresidentialPardonForm (" << this->getName() << ") parametric constructor called" RESET << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& src) : AForm(src), _target(src._target) {
	std::cout << YELLOW "PresidentialPardonForm (" << this->getName() << ") constructor by copy called" RESET << std::endl;
}

PresidentialPardonForm::~PresidentialPardonForm(void) {
	std::cout << "PresidentialPardonForm (" << this->getName() <<  ")" << RED " destructor" RESET << " called" << std::endl;
}

PresidentialPardonForm&	PresidentialPardonForm::operator=(const PresidentialPardonForm& src) {

	if (this != &src) {
		AForm::operator=(src);
		_target = src._target;
	}

	std::cout << BLUE "Assignment operator = called on " << this->getName() << RESET << std::endl;
	return (*this);
}

void	PresidentialPardonForm::executeForm(void) const {
	std::cout << MAGENTA << this->getTarget() << " has been pardoned by Zaphod Beeblebrox." RESET << std::endl;
}

std::string	PresidentialPardonForm::getTarget(void) const {
	return (this->_target);
}
