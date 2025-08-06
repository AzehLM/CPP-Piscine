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
#include "colors.h"
#include <unistd.h>

int main(void)
{
	// initialization here to avoid calling it everytime we get into the executeForm function of the RobotomyForm.
	// This also fixes the "false" randomisation of calls, rand isn't called after srand is being reset.
	srand(time(NULL));

	{
		std::cout << CYAN "\tCanonical form tests - ShrubberyCreationForm" RESET << std::endl;

		ShrubberyCreationForm form1;
		ShrubberyCreationForm form2("Garden");
		ShrubberyCreationForm form3(form2);
		ShrubberyCreationForm form4;

		form4 = form3;

		// Test des getters
		assert(form2.getTarget() == "Garden");
		assert(form3.getTarget() == "Garden");
		assert(form4.getTarget() == "Garden");
		assert(form2.getSigningRequirement() == 145);
		assert(form2.getExecutingGrade() == 137);
		assert(form2.getStatus() == false);
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tCanonical form tests - RobotomyRequestForm" RESET << std::endl;

		RobotomyRequestForm form1;
		RobotomyRequestForm form2("Bender");
		RobotomyRequestForm form3(form2);
		RobotomyRequestForm form4;

		form4 = form3;

		// Test des getters
		assert(form2.getTarget() == "Bender");
		assert(form3.getTarget() == "Bender");
		assert(form4.getTarget() == "Bender");
		assert(form2.getSigningRequirement() == 72);
		assert(form2.getExecutingGrade() == 45);
		assert(form2.getStatus() == false);
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tCanonical form tests - PresidentialPardonForm" RESET << std::endl;

		PresidentialPardonForm form1;
		PresidentialPardonForm form2("Arthur Dent");
		PresidentialPardonForm form3(form2);
		PresidentialPardonForm form4;

		form4 = form3;

		// Test des getters
		assert(form2.getTarget() == "Arthur Dent");
		assert(form3.getTarget() == "Arthur Dent");
		assert(form4.getTarget() == "Arthur Dent");
		assert(form2.getSigningRequirement() == 25);
		assert(form2.getExecutingGrade() == 5);
		assert(form2.getStatus() == false);
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tPolymorphism test" RESET << std::endl;

		AForm* forms[3];
		forms[0] = new ShrubberyCreationForm("Park");
		forms[1] = new RobotomyRequestForm("Wall-E");
		forms[2] = new PresidentialPardonForm("Ford Prefect");

		Bureaucrat highLevel("Boss", 1);

		for (int i = 0; i < 3; i++) {
			std::cout << *forms[i] << std::endl;
			highLevel.signForm(*forms[i]);
			assert(forms[i]->getStatus() == true);
			std::cout << *forms[i] << std::endl;
		}

		for (int i = 0; i < 3; i++) {
			delete forms[i];
		}
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tSigning with insufficient grade" RESET << std::endl;

		try {
			Bureaucrat lowLevel("Intern", 150);
			ShrubberyCreationForm form("Office");

			std::cout << lowLevel << std::endl;
			std::cout << form << std::endl;
			assert(form.getStatus() == false);
			lowLevel.signForm(form);
			assert(form.getStatus() == false); // Should still be unsigned
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tExecuting unsigned form" RESET << std::endl;

		try {
			Bureaucrat boss("CEO", 1);
			RobotomyRequestForm form("Employee");

			assert(form.getStatus() == false);
			boss.executeForm(form); // Should fail - form not signed
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tExecuting with insufficient grade" RESET << std::endl;

		try {
			Bureaucrat signer("Manager", 70);
			Bureaucrat executor("Assistant", 50);
			RobotomyRequestForm form("Printer");

			signer.signForm(form);
			assert(form.getStatus() == true);

			executor.executeForm(form); // Grade 50, needs 45 - should fail
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tProper execution - ShrubberyCreationForm" RESET << std::endl;

		try {
			Bureaucrat gardener("Gardener", 130);
			ShrubberyCreationForm form("BackYard");

			gardener.signForm(form);
			assert(form.getStatus() == true);

			gardener.executeForm(form);

			// Verify file was created
			std::ifstream file("BackYard_shrubbery");
			assert(file.is_open());
			file.close();
			std::remove("BackYard_shrubbery");

			std::cout << GREEN " ✓ File was created successfully" RESET << std::endl;
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tProper execution - RobotomyRequestForm" RESET << std::endl;

		try {
			Bureaucrat technician("Technician", 40);
			RobotomyRequestForm form("Target-42");

			technician.signForm(form);
			assert(form.getStatus() == true);

			std::cout << "Executing robotomy 5 times:" << std::endl;
			for (int i = 0; i < 5; i++) {
				technician.executeForm(form);
			}
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tProper execution - PresidentialPardonForm" RESET << std::endl;

		try {
			Bureaucrat president("President", 1);
			PresidentialPardonForm form("Marvin");

			president.signForm(form);
			assert(form.getStatus() == true);

			president.executeForm(form);
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tEdge case - Exact grade requirements" RESET << std::endl;

		try {

			Bureaucrat exactSigner("Exact Signer", 145);
			ShrubberyCreationForm form1("Test1");

			exactSigner.signForm(form1);
			assert(form1.getStatus() == true);
			std::cout << GREEN " ✓ Exact signing grade works" RESET << std::endl;

			Bureaucrat exactExecutor("Exact Executor", 137);
			ShrubberyCreationForm form2("Test2");

			exactSigner.signForm(form2);
			exactExecutor.executeForm(form2);

			std::remove("Test2_shrubbery"); // Clean up

			std::cout << GREEN " ✓ Exact execution grade works" RESET << std::endl;

			Bureaucrat tooLowSigner("Too Low", 146);
			ShrubberyCreationForm form3("Test3");

			tooLowSigner.signForm(form3);
			assert(form3.getStatus() == false);
			std::cout << GREEN " ✓ One grade too low for signing fails correctly" RESET << std::endl;
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tComplete workflow test" RESET << std::endl;

		try {

			Bureaucrat ceo("CEO", 1);
			Bureaucrat manager("Manager", 26);
			Bureaucrat intern("Intern", 145);

			// Create all form types
			ShrubberyCreationForm shrub("CompanyGarden");
			RobotomyRequestForm robot("CoffeeMachine");
			PresidentialPardonForm pardon("Employee of the Month");

			std::cout << "Initial states:" << std::endl;
			std::cout << shrub << std::endl;
			std::cout << robot << std::endl;
			std::cout << pardon << std::endl;

			intern.signForm(shrub);
			intern.signForm(robot);    // Should fail
			intern.signForm(pardon);   // Should fail

			std::cout << std::endl;

			// Manager can sign all but presidential
			manager.signForm(shrub);
			manager.signForm(robot);
			manager.signForm(pardon);


			std::cout << std::endl;

			// CEO executes all
			ceo.signForm(pardon);

			ceo.executeForm(shrub);
			ceo.executeForm(robot);
			ceo.executeForm(pardon);

			std::remove("CompanyGarden_shrubbery");

			std::cout << GREEN "\n ✓ Complete workflow test passed" RESET << std::endl;
			std::cout << std::endl;
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	return 0;
}
