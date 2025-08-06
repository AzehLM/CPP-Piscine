#ifndef AFORM_HPP
# define AFORM_HPP

#include "Bureaucrat.hpp"

class AForm {

	private:
		static const unsigned int	MAX_GRADE = 1;
		static const unsigned int	MIN_GRADE = 150;
		const std::string			_name;
		bool						_isSigned;	// false at construction
		const unsigned int			_signing;
		const unsigned int			_executing;

	protected:
		virtual void		executeForm() const = 0;

	public:
		AForm(void);
		AForm(const std::string& name, const unsigned int signing, const unsigned int executing);
		AForm(const AForm& src);

		virtual ~AForm(void);

		AForm&	operator=(const AForm& src);

		class GradeTooHighException : public std::exception {
			public:
				const char* what (void) const throw();
		};

		class GradeTooLowException : public std::exception {
			public:
				const char* what (void) const throw();
		};

		class FormNotSignedException : public std::exception {
			public:
				const char* what (void) const throw();
		};

		const std::string&	getName(void) const;
		bool				getStatus(void) const;
		unsigned int		getSigningRequirement(void) const;
		unsigned int		getExecutingGrade(void) const;

		void	beSigned(const Bureaucrat& bureaucrat);
		void	execute(const Bureaucrat& executor) const;

		// virtual std::string	getTarget() const = 0;
};

std::ostream&	operator<<(std::ostream& o, const AForm& form);

#endif
