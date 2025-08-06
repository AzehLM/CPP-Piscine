/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:08:42 by mhotting          #+#    #+#             */
/*   Updated: 2025/07/29 18:51:18 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <exception>

#include "Bureaucrat.hpp"
#include "colors.h"
#include "Form.hpp"

int main(void)
{
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << CYAN "\tBasic tests" RESET << std::endl;
		try
		{
			Form first("1st Form", 10, 10);
			std::cout << first << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
		try
		{
			Form second("2nd form", 151, 2);
			std::cout << second << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
		try
		{
			Form third("3rd form", 2, 151);
			std::cout << third << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
		try
		{
			Form fourth("4th form", 0, 42);
			std::cout << fourth << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
		try
		{
			Form fifth("5th form", 42, 0);
			std::cout << fifth << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
	}
	std::cout << std::endl;
	{
		std::cout << CYAN "\tSigning Form properly" << std::endl;
		try
		{
			Bureaucrat	b1("Bureaucrat", 42);
			Form		form("Correct form", 40, 50);
			b1.signForm(form);
			std::cout << form << std::endl;
			std::cout << b1 << std::endl;
			b1.incrementGrade();
			b1.incrementGrade();
			std::cout << b1 << " (after two incrementation)" << std::endl;
			b1.signForm(form);
			std::cout << form << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		
	}
	std::cout << std::endl;
	{
		std::cout << CYAN "\tSigning Form with insufficient grade" RESET << std::endl;
		try
		{
			Bureaucrat	b1("Low Grade Bureaucrat", 100);
			Form		form("High Level Form", 50, 30);
			std::cout << b1 << std::endl;
			std::cout << form << std::endl;
			b1.signForm(form);
			std::cout << form << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
	}
	std::cout << std::endl;
	{
		std::cout << CYAN "\tSigning already signed Form" RESET << std::endl;
		try
		{
			Bureaucrat	b1("First Bureaucrat", 10);
			Bureaucrat	b2("Second Bureaucrat", 5);
			Form		form("Important Form", 20, 15);
			
			std::cout << "Before first signature:" << std::endl;
			std::cout << form << std::endl;
			
			b1.signForm(form);
			std::cout << "After first signature:" << std::endl;
			std::cout << form << std::endl;
			
			b2.signForm(form);
			std::cout << "After second signature attempt:" << std::endl;
			std::cout << form << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
	}
	std::cout << std::endl;
	{
		std::cout << CYAN "\tTesting Bureaucrat grade limits" RESET << std::endl;
		try
		{
			Bureaucrat	b1("Test Bureaucrat", 2);
			std::cout << b1 << std::endl;
			
			b1.incrementGrade();
			std::cout << b1 << " (after increment)" << std::endl;
			
			b1.incrementGrade(); // Should throw exception
			std::cout << b1 << " (after second increment)" << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
		
		try
		{
			Bureaucrat	b2("Another Test Bureaucrat", 149);
			std::cout << b2 << std::endl;
			
			b2.decrementGrade();
			std::cout << b2 << " (after decrement)" << std::endl;
			
			b2.decrementGrade(); // Should throw exception
			std::cout << b2 << " (after second decrement)" << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
	}
	std::cout << std::endl;
	{
		std::cout << CYAN "\tTesting copy constructor and assignment operator" RESET << std::endl;
		try
		{
			Form		original("Original Form", 30, 25);
			Bureaucrat	b1("Signer", 20);
			
			b1.signForm(original);
			std::cout << "Original form: " << original << std::endl;
			
			Form copy(original);
			std::cout << "Copied form: " << copy << std::endl;
			
			Form assigned("Temp", 100, 100);
			assigned = original;
			std::cout << "Assigned form: " << assigned << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
	}
    return (0);
}
