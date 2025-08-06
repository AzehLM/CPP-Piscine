#include <cassert>
#include <iostream>
#include <exception>
#include <fstream>
#include <cstdlib>

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"
#include "colors.h"

int main(void)
{
	srand(time(NULL));

	{
		std::cout << CYAN "\tCanonical form tests - Intern" RESET << std::endl;

		Intern intern1;
		Intern intern2(intern1);
		Intern intern3;

		intern3 = intern2;

		std::cout << GREEN " ✓ Intern canonical forms work" RESET << std::endl;
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tAll form types creation" RESET << std::endl;

		try {
			Intern intern;
			AForm* forms[3];

			forms[0] = intern.makeForm("shrubbery creation", "Garden");
			forms[1] = intern.makeForm("robotomy request", "Robot");
			forms[2] = intern.makeForm("presidential pardon", "Criminal");

			for (int i = 0; i < 3; i++) {
				assert(forms[i] != NULL);
			}

			assert(forms[0]->getName() == "ShrubberyCreationForm");
			assert(forms[1]->getName() == "RobotomyRequestForm");
			assert(forms[2]->getName() == "PresidentialPardonForm");

			assert(forms[0]->getSigningRequirement() == 145);
			assert(forms[0]->getExecutingGrade() == 137);

			assert(forms[1]->getSigningRequirement() == 72);
			assert(forms[1]->getExecutingGrade() == 45);

			assert(forms[2]->getSigningRequirement() == 25);
			assert(forms[2]->getExecutingGrade() == 5);

			for (int i = 0; i < 3; i++) {
				delete forms[i];
			}

			std::cout << GREEN " ✓ All form types created successfully" RESET << std::endl;
		}
		catch (const std::exception& e) {
			std::cout << RED "Unexpected exception: " << e.what() << RESET << std::endl;
			assert(false);
		}
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tInvalid form name test" RESET << std::endl;

		try {
			Intern intern;
			AForm* form;

			form = intern.makeForm("invalid form", "Target");
			assert(form == NULL);

			form = intern.makeForm("", "Target");
			assert(form == NULL);

			form = intern.makeForm("shrubbery", "Target");  // Missing "creation"
			assert(form == NULL);

			form = intern.makeForm("SHRUBBERY CREATION", "Target");  // Wrong case
			assert(form == NULL);

			form = intern.makeForm("robotomy", "Target");  // Missing "request"
			assert(form == NULL);

			form = intern.makeForm("presidential", "Target");  // Missing "pardon"
			assert(form == NULL);

			std::cout << GREEN " ✓ Invalid form names handled correctly" RESET << std::endl;
		}
		catch (const std::exception& e) {
			std::cout << RED "Unexpected exception: " << e.what() << RESET << std::endl;
			assert(false);
		}
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tPolymorphism with Intern-created forms" RESET << std::endl;

		try {
			Intern intern;
			Bureaucrat worker("Worker", 45);

			// Create form through base class pointer
			AForm* form = intern.makeForm("robotomy request", "Test Subject");
			assert(form != NULL);

			worker.signForm(*form);
			worker.executeForm(*form);

			// Test type through virtual behavior
			assert(form->getSigningRequirement() == 72);
			assert(form->getExecutingGrade() == 45);

			delete form;

			std::cout << GREEN " ✓ Polymorphism works correctly" RESET << std::endl;
		}
		catch (const std::exception& e) {
			std::cout << RED "Unexpected exception: " << e.what() << RESET << std::endl;
			assert(false);
		}
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tMultiple interns test" RESET << std::endl;

		try {
			Intern intern1;
			Intern intern2;
			Intern intern3;

			AForm* form1 = intern1.makeForm("shrubbery creation", "Garden1");
			AForm* form2 = intern2.makeForm("robotomy request", "Robot2");
			AForm* form3 = intern3.makeForm("presidential pardon", "Person3");

			assert(form1 != NULL);
			assert(form2 != NULL);
			assert(form3 != NULL);

			assert(form1->getName() == "ShrubberyCreationForm");
			assert(form2->getName() == "RobotomyRequestForm");
			assert(form3->getName() == "PresidentialPardonForm");

			delete form1;
			delete form2;
			delete form3;

			std::cout << GREEN " ✓ Multiple interns work independently" RESET << std::endl;
		}
		catch (const std::exception& e) {
			std::cout << RED "Unexpected exception: " << e.what() << RESET << std::endl;
			assert(false);
		}
	}

	std::cout << std::endl;

	std::cout << RED "\tREMOVE QUOTE OF LAST TESTS AND UNCOMMENT getTarget() in AForm CLASS DEFINITION" RESET << std::endl;
	std::cout << std::endl;
	// {
	// 	std::cout << CYAN "\tEdge cases" RESET << std::endl;

	// 	try {
	// 		Intern intern;
	// 		AForm* form;

	// 		form = intern.makeForm("shrubbery creation", "");
	// 		assert(form != NULL);  // Should work with empty target
	// 		delete form;

	// 		// Very long target
	// 		std::string longTarget(1000, 'A');
	// 		form = intern.makeForm("robotomy request", longTarget);
	// 		std::cout << "Target length: " << form->getTarget().length() << std::endl;
	// 		std::cout << "First 10 chars: " << form->getTarget().substr(0, 10) << std::endl;
	// 		assert(form != NULL);

	// 		delete form;

	// 		// Special characters in target
	// 		form = intern.makeForm("presidential pardon", "Test@#$%^&*()");
	// 		assert(form != NULL);
	// 		delete form;

	// 		// Whitespace handling
	// 		form = intern.makeForm("shrubbery creation ", "Target");  // Extra space
	// 		assert(form == NULL);

	// 		form = intern.makeForm(" shrubbery creation", "Target");  // Leading space
	// 		assert(form == NULL);

	// 		std::cout << GREEN " ✓ Edge cases handled correctly" RESET << std::endl;
	// 	}
	// 	catch (const std::exception& e) {
	// 		std::cout << RED "Unexpected exception: " << e.what() << RESET << std::endl;
	// 		assert(false);
	// 	}
	// }

	return (0);
}
