#include "Bureaucrat.hpp"
#include "colors.h"

int	main(void)
{
	{
		std::cout << CYAN "\tCanonical form tests" RESET << std::endl;

		Bureaucrat	bureaucrat1;
		Bureaucrat	bureaucrat2("John", 42);
		Bureaucrat	bureaucrat3(bureaucrat2);

		Bureaucrat	bureaucrat4;

		bureaucrat4 = bureaucrat3;
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tInitialization tests" RESET << std::endl;

		try
		{
			Bureaucrat	jhon("John", 150);
			std::cout << jhon << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		try
		{
			Bureaucrat	bob("Bob", 151);
			std::cout << bob << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		try
		{
			Bureaucrat	matheo("Matheo", 1);
			std::cout << matheo << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		try
		{
			Bureaucrat	matheo("Matheo", 0);
			std::cout << matheo << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tIncrement/Decrement tests" RESET << std::endl;

		try
		{
			Bureaucrat	bob("Bob", 149);
			std::cout << bob << std::endl;
			bob.decrementGrade();
			std::cout << bob << std::endl;
			bob.decrementGrade();
			std::cout << bob << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		try
		{
			Bureaucrat	jhon("Jhon", 2);
			std::cout << jhon << std::endl;
			jhon.incrementGrade();
			std::cout << jhon << std::endl;
			jhon.incrementGrade();
			std::cout << jhon << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return (0);
}
