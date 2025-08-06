#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"

class RobotomyRequestForm : public AForm {

	private:
		static const unsigned int	SIGN_GRADE = 72;
		static const unsigned int	EXEC_GRADE = 45;
		std::string					_target;
		void	executeForm(void) const;

	public:
		RobotomyRequestForm(void);
		RobotomyRequestForm(const std::string& target);
		RobotomyRequestForm(const RobotomyRequestForm& src);

		~RobotomyRequestForm(void);

		RobotomyRequestForm&	operator=(const RobotomyRequestForm& src);

		std::string	getTarget(void) const;
};

#endif
