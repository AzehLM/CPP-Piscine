#ifndef INTERN_HPP
# define INTERN_HPP

#include "AForm.hpp"

class Intern
{
	private:
		struct FormCreator {
			std::string formName;
			AForm* (*create)(const std::string& target);
		};

		static AForm* createShrubberyForm(const std::string& target);
		static AForm* createRobotomyForm(const std::string& target);
		static AForm* createPresidentialForm(const std::string& target);

		static const FormCreator formCreator[3];

	public:
		Intern(void);
		Intern(const Intern& src);

		Intern&	operator=(const Intern& src);

		~Intern();

		AForm*	makeForm(const std::string& formName, const std::string& target);
};


#endif
