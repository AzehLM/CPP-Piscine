#include "colors.h"
#include "Form.hpp"

Form::Form(void) : _name("default form"), _isSigned(false), _signing(42), _executing(42) {
	std::cout << YELLOW "Form default constructor called" RESET << std::endl;
}

Form::Form(const std::string& name, const unsigned int signing, const unsigned int executing) : _name(name), _isSigned(false), _signing(signing), _executing(executing) {

	if (signing < Form::MAX_GRADE)
		throw Form::GradeTooHighException();
	else if (signing > Form::MIN_GRADE)
		throw Form::GradeTooLowException();
	if (executing < Form::MAX_GRADE)
		throw Form::GradeTooHighException();
	else if (executing > Form::MIN_GRADE)
		throw Form::GradeTooLowException();
	std::cout << YELLOW "Form (" << _name << ") parametric constructor called" RESET << std::endl;
}

Form::Form(const Form& src) : _name(src._name), _isSigned(src._isSigned), _signing(src._signing), _executing(src._executing) {
	std::cout << YELLOW "Form (" << _name << ") constructor by copy called" RESET << std::endl;
}

Form::~Form(void) {
	std::cout << "Form (" << _name <<  ")" << RED " destructor" RESET << " called" << std::endl;
}

Form&	Form::operator=(const Form& src) {

	if (this != &src) {
		this->_isSigned = src._isSigned;
	}

	std::cout << BLUE "Assignment operator = called on " << this->_name << RESET << std::endl;
	return (*this);
}

const std::string&	Form::getName(void) const {
	return (this->_name);
}

bool				Form::getStatus(void) const {
	return (this->_isSigned);
}

unsigned int	Form::getSigningRequirement(void) const {
	return (this->_signing);
}

unsigned int	Form::getExecutingGrade(void) const {
	return (this->_executing);
}

void	Form::beSigned(const Bureaucrat& bureaucrat) {

	if (bureaucrat.getGrade() > this->_signing) {
		throw Form::GradeTooLowException();
	} else {
		_isSigned = true;
	}
}

const char*	Form::GradeTooHighException::what(void) const throw() {
	return (RED "Grade is too high" RESET);
}

const char*	Form::GradeTooLowException::what(void) const throw() {
	return (RED "Grade is too low" RESET);
}


std::ostream&	operator<<(std::ostream& o, const Form& form) {

	o << form.getName() << " is " << (form.getStatus() ? MAGENTA "signed" : RED "not signed") << RESET << std::endl;
	o << "Signing requierement: " << form.getSigningRequirement() << " | Executing requierement: " << form.getExecutingGrade() << RESET;

	return (o);
}
