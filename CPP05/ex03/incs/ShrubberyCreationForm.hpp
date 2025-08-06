#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"

class ShrubberyCreationForm : public AForm {

	private:
		static const unsigned int	SIGN_GRADE = 145;
		static const unsigned int	EXEC_GRADE = 137;
		std::string 				_target;
		void	executeForm(void) const;

	public:
		ShrubberyCreationForm(void);
		ShrubberyCreationForm(const std::string& target);
		ShrubberyCreationForm(const ShrubberyCreationForm& src);

		~ShrubberyCreationForm(void);

		ShrubberyCreationForm&	operator=(const ShrubberyCreationForm& src);

		class OpeningOutStreamFailException : public std::exception {
			public:
				const char* what(void) const throw();
		};

		std::string	getTarget(void) const;
};

#endif
