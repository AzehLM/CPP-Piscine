/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:24:42 by gueberso          #+#    #+#             */
/*   Updated: 2025/06/30 18:01:21 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iomanip>
#include <iostream>
#include <sstream>

#include "PhoneBook.hpp"

PhoneBook::PhoneBook() : _index(0) {}

PhoneBook::~PhoneBook() {}

static std::string	truncateString(const std::string& str)
{
	if (str.length() > 10) {
		return str.substr(0, 9) + ".";
	}
	return (str);
}

void	PhoneBook::displayContactList(void) const
{
	std::cout << "|" << std::right << std::setw(10) << "Index" << "|";
	std::cout << std::right << std::setw(10) << "First Name" << "|";
	std::cout << std::right << std::setw(10) << "Last Name" << "|";
	std::cout << std::right << std::setw(10) << "Nickname" << "|" << std::endl;

	std::cout << "|" << std::setfill('-') << std::setw(10) << "" << "|";
	std::cout << std::setw(10) << "" << "|";
	std::cout << std::setw(10) << "" << "|";
	std::cout << std::setw(10) << "" << "|" << std::endl;
	std::cout << std::setfill(' ');

	for (int i = 0; i < 8; i++) {
		if (!_contacts[i].checkEmptyContact()) {
			std::cout << "|" << std::right << std::setw(10) << i << "|";
			std::cout << std::right << std::setw(10) << truncateString(_contacts[i].getFirstName()) << "|";
			std::cout << std::right << std::setw(10) << truncateString(_contacts[i].getLastName()) << "|";
			std::cout << std::right << std::setw(10) << truncateString(_contacts[i].getNickName()) << "|" << std::endl;
		}
	}
}

static std::string	getInput(const char *section)
{
	std::string	info;

	do
	{
		std::cout << section;
		if (!std::getline(std::cin, info)) {
			return (info);
		}
		else if (info.empty())
			std::cout << "Contact sections cannot be empty." << std::endl;
	} while (info.empty());
	return (info);
}

typedef void (Contact::*contact_setter)(const std::string &);

static bool promptValueForContact(Contact& contact, const char *question, contact_setter setter)
{
	std::string input;

	input = getInput(question);
	if (input.empty())
		return (false);
	(contact.*setter)(input);
	return (true);
}

bool	PhoneBook::addContact(void)
{
	Contact		contact;

	if (!promptValueForContact(contact, "First Name: ", &Contact::setFirstName)) {return (false);}
	if (!promptValueForContact(contact, "Last Name: ", &Contact::setLastName)) {return (false);}
	if (!promptValueForContact(contact, "Nickname: ", &Contact::setNickName)) {return (false);}
	if (!promptValueForContact(contact, "Phone number: ", &Contact::setPhoneNumber)) {return (false);}
	if (!promptValueForContact(contact, "Darkest secret: ", &Contact::setDarkestSecret)) {return (false);}

	if (_index < 8) {
		_contacts[_index] = contact;
		_index++;
	} else {
		_index = 0;
		_contacts[_index] = contact;
		_index++;
	}
	std::cout << "Contact added successfully!" << std::endl;
	return (true);
}

bool	PhoneBook::searchContact(void) const
{
	int					index;
	std::string			str;

	if (this->_index == 0) {
		std::cout << "Phonebook is empty." << std::endl;
		return (true);
	}

	displayContactList();

	std::cout << std::endl << "Enter the number of the index you want to see: ";
	if (!std::getline(std::cin, str))
		return (false);
	if (str.empty())
		return (true);

	for (size_t i = 0; i < str.length(); i++) {
		if (!isdigit(str[i])) {
			std::cout << "Invalid input: not a number." << std::endl;
			return (true);
		}
	}

	std::stringstream	converter(str);
	converter >> index;

	if (index < 0 || index >= 8 || _contacts[index].checkEmptyContact()) {
		if (_contacts[index].checkEmptyContact())
			std::cout << "This index is yet empty." << std::endl;
		else
			std::cout << "Index out of PhoneBook scope." << std::endl;
		return (true);
	}
	_contacts[index].displayInfos();
	return (true);
}
