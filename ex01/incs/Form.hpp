#ifndef FORM_HPP
# define FORM_HPP

#include "Bureaucrat.hpp"

class Form {

	private:
		static const unsigned int MAX_GRADE = 1;
		static const unsigned int MIN_GRADE = 150;
		const std::string	_name;
		bool				_isSigned;	// false at construction
		const unsigned int	_signing;
		const unsigned int	_executing;

	public:
		Form(void);
		Form(const std::string& name, const unsigned int signing, const unsigned int executing);
		Form(const Form& src);

		~Form(void);

		Form&	operator=(const Form& src);

		class GradeTooHighException : public std::exception {
			public:
				const char* what (void) const throw();
		};

		class GradeTooLowException : public std::exception {
			public:
				const char* what (void) const throw();
		};

		const std::string&	getName(void) const;
		bool				getStatus(void) const;

		unsigned int		getSigningRequirement(void) const;
		unsigned int		getExecutingGrade(void) const;

		void	beSigned(const Bureaucrat& bureaucrat);

};

std::ostream&	operator<<(std::ostream& o, const Form& form);

#endif
