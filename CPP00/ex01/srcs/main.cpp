/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:24:14 by gueberso          #+#    #+#             */
/*   Updated: 2025/05/04 20:50:01 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "PhoneBook.hpp"

int	main(void)
{
	PhoneBook	PhoneBook;
	std::string	input;

	while (true) {

		std::cout << "Please, enter your command (ADD, SEARCH, EXIT): ";
		if (!std::getline(std::cin, input))
			return (1);
		else if (input == "ADD") {
			if (!PhoneBook.addContact())
				break ;
		}
		else if (input == "SEARCH") {
			if (!PhoneBook.searchContact())
				break ;
		}
		else if (input == "EXIT") {
			std::cout << "Bye, the contacts are lost forever!" << std::endl;
			break ;
		}
		else
			std::cout << "Invalid input" << std::endl;
	}
	return (0);
}
