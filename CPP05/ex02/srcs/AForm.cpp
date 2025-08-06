#include "colors.h"
#include "AForm.hpp"

AForm::AForm(void) : _name("defaut AForm"), _isSigned(false), _signing(42), _executing(42) {
	std::cout << YELLOW "AForm default constructor called" RESET << std::endl;
}

AForm::AForm(const std::string& name, const unsigned int signing, const unsigned int executing) : _name(name), _isSigned(false), _signing(signing), _executing(executing) {

	if (signing < AForm::MAX_GRADE) {
		throw AForm::GradeTooHighException();
	} else if (signing > AForm::MIN_GRADE) {
		throw AForm::GradeTooLowException();
	}

	if (executing < AForm::MAX_GRADE) {
		throw AForm::GradeTooHighException();
	} else if (executing > AForm::MIN_GRADE) {
		throw AForm::GradeTooLowException();
	}

	std::cout << YELLOW "AForm (" << _name << ") parametric constructor called" RESET << std::endl;
}

AForm::AForm(const AForm& src) : _name(src._name), _isSigned(src._isSigned), _signing(src._signing), _executing(src._executing) {
	std::cout << YELLOW "AForm (" << _name << ") constructor by copy called" RESET << std::endl;
}

AForm::~AForm(void) {
	std::cout << "AForm (" << _name <<  ")" << RED " destructor" RESET << " called" << std::endl;
}

AForm&	AForm::operator=(const AForm& src) {

	if (this != &src) {
		this->_isSigned = src._isSigned;
	}

	std::cout << BLUE "Assignment operator = called on " << this->_name << RESET << std::endl;
	return (*this);
}

const std::string&	AForm::getName(void) const {
	return (this->_name);
}

bool				AForm::getStatus(void) const {
	return (this->_isSigned);
}

unsigned int		AForm::getSigningRequirement(void) const {
	return (this->_signing);
}

unsigned int		AForm::getExecutingGrade(void) const {
	return (this->_executing);
}

void				AForm::execute(const Bureaucrat& executor) const {

	if (!_isSigned) {
		throw AForm::FormNotSignedException();
	}
	if (executor.getGrade() > this->getExecutingGrade()) {
		throw AForm::GradeTooLowException();
	}
	this->executeForm(); // not sure of the parameter
}

void	AForm::beSigned(const Bureaucrat& bureaucrat) {

	if (bureaucrat.getGrade() > this->_signing) {
		throw AForm::GradeTooLowException();
	} else {
		_isSigned = true;
	}
}

const char*	AForm::GradeTooHighException::what(void) const throw() {
	return (RED "Grade is too high" RESET);
}

const char*	AForm::GradeTooLowException::what(void) const throw() {
	return (RED "Grade is too low" RESET);
}

const char* AForm::FormNotSignedException::what(void) const throw() {
	return (RED "Form not signed" RESET);
}

std::ostream&	operator<<(std::ostream& o, const AForm& form) {

	o << form.getName() << " is " << (form.getStatus() ? MAGENTA "signed" : RED "not signed") << RESET << std::endl;
	o << "Signing requierement: " << form.getSigningRequirement() << " | Executing requierement: " << form.getExecutingGrade() << RESET;

	return (o);
}
