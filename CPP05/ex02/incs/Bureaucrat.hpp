#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include <string>
#include <exception>
#include <iostream>


class AForm;

class Bureaucrat {

	private:
		static const unsigned int MAX_GRADE = 1;
		static const unsigned int MIN_GRADE = 150;
		const std::string	_name;
		unsigned int		_grade;

	public:
		Bureaucrat(void);
		Bureaucrat(const std::string& name, const unsigned int grade);
		Bureaucrat(const Bureaucrat& src);

		~Bureaucrat(void);

		Bureaucrat& operator=(const Bureaucrat& src);

		class GradeTooHighException : public std::exception {
			public:
				const char* what (void) const throw();
		};

		class GradeTooLowException : public std::exception {
			public:
				const char* what (void) const throw();
		};

		const std::string&	getName(void) const;
		unsigned int		getGrade(void) const;

		void	incrementGrade(void);
		void	decrementGrade(void);

		void	signForm(AForm& form) const;
		void	executeForm(const AForm& form) const;
};

std::ostream& operator<<(std::ostream& o, const Bureaucrat& bureaucrat);

# endif
