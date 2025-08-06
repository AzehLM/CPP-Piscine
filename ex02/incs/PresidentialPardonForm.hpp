#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"

class PresidentialPardonForm : public AForm {

	private:
		static const unsigned int	SIGN_GRADE = 25;
		static const unsigned int	EXEC_GRADE = 5;
		std::string 				_target;
		void	executeForm(void) const;

	public:
		PresidentialPardonForm(void);
		PresidentialPardonForm(const std::string& target);
		PresidentialPardonForm(const PresidentialPardonForm& src);

		~PresidentialPardonForm(void);

		PresidentialPardonForm&	operator=(const PresidentialPardonForm& src);

		std::string	getTarget(void) const;
};

#endif
