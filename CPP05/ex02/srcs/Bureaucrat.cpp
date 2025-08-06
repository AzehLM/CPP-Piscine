#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "colors.h"

Bureaucrat::Bureaucrat(void) : _name("Someone"), _grade(150) {
	std::cout << YELLOW "Bureaucrat default constructor called" RESET << std::endl;
}

Bureaucrat::Bureaucrat(const std::string& name, const unsigned int grade) : _name(name) {

	if (grade < Bureaucrat::MAX_GRADE) {
		throw Bureaucrat::GradeTooHighException();
	} else if (grade > Bureaucrat::MIN_GRADE) {
		throw Bureaucrat::GradeTooLowException();
	}
	_grade = grade;
	std::cout << YELLOW "Bureaucrat (" << _name << ") parametric constructor called" RESET << std::endl;
}

Bureaucrat::Bureaucrat(const Bureaucrat& src) : _name(src._name), _grade(src._grade) {
	std::cout << YELLOW "Bureaucrat (" << _name << ") constructor by copy called" RESET << std::endl;
}

Bureaucrat::~Bureaucrat(void) {
	std::cout << "Bureaucrat (" << _name << ") " <<  RED "destructor" RESET << " called" << std::endl;
}

Bureaucrat&	Bureaucrat::operator=(const Bureaucrat& src) {

	if (this != &src) {
		this->_grade = src._grade;
	}

	std::cout << BLUE "Assigment operator = called on " << this->_name << RESET << std::endl;
	return (*this);
}

const std::string&	Bureaucrat::getName(void) const {
	return (this->_name);
}

unsigned int		Bureaucrat::getGrade(void) const {
	return (this->_grade);
}

void	Bureaucrat::incrementGrade(void) {

	if (this->_grade == Bureaucrat::MAX_GRADE) {
		throw Bureaucrat::GradeTooHighException();
	}

	this->_grade--;
}

void	Bureaucrat::decrementGrade(void) {

	if (this->_grade == Bureaucrat::MIN_GRADE) {
		throw Bureaucrat::GradeTooLowException();
	}

	this->_grade++;
}

const char* Bureaucrat::GradeTooHighException::what(void) const throw() {
	return (RED "Grade is too high" RESET);
}

const char* Bureaucrat::GradeTooLowException::what(void) const throw() {
	return (RED "Grade is too low" RESET);
}

std::ostream& operator<<(std::ostream& o, const Bureaucrat& bureaucrat) {

	o << GREEN << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << "." RESET;

	return (o);
}


void	Bureaucrat::signForm(AForm& form) const {

	if (form.getStatus()) {
		std::cout << RED << this->_name << " couldn't sign " << form.getName() << " because it is already signed" RESET << std::endl;
		return ;
	}

	try
	{
		form.beSigned(*this);
		std::cout << GREEN << this->_name << " signed " << form.getName() << RESET << std::endl;

	}
	catch(const std::exception& e)
	{
		std::cout << RED << this->_name << " couldn't sign " << form.getName() << " because " << e.what() << "." RESET << std::endl;
	}
}

void	Bureaucrat::executeForm(const AForm& form) const {

	try
	{
		form.execute(*this);
		std::cout << this->_name << GREEN " executed " RESET << form.getName() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << RED << this->_name << " couldn't execute " << form.getName() << " because " << e.what() << RESET << std::endl;
	}
}
