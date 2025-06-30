/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:24:51 by gueberso          #+#    #+#             */
/*   Updated: 2025/05/04 15:03:59 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "Contact.hpp"

Contact::Contact()
{
	_firstName = "";
	_lastName = "";
	_nickName = "";
	_phoneNumber = "";
	_darkestSecret = "";
}

Contact::~Contact() {}

void	Contact::setFirstName(const std::string &firstName)
{
	_firstName = firstName;
}

void	Contact::setLastName(const std::string &lastName)
{
	_lastName = lastName;
}

void	Contact::setNickName(const std::string &nickName)
{
	_nickName = nickName;
}

void	Contact::setPhoneNumber(const std::string &phoneNumber)
{
	_phoneNumber = phoneNumber;
}

void	Contact::setDarkestSecret(const std::string &darkestSecret)
{
	_darkestSecret = darkestSecret;
}

std::string Contact::getFirstName(void) const
{
	return (_firstName);
}

std::string Contact::getLastName(void) const
{
	return (_lastName);
}

std::string Contact::getNickName(void) const
{
	return (_nickName);
}

std::string Contact::getPhoneNumber(void) const
{
	return (_phoneNumber);
}

std::string	Contact::getDarkestSecret(void) const
{
	return (_darkestSecret);
}

void	Contact::displayInfos(void) const
{
	std::cout << "FirstName: " << _firstName <<std::endl;
	std::cout << "LastName: " << _lastName <<std::endl;
	std::cout << "NickName: " << _nickName <<std::endl;
	std::cout << "PhoneNumber: " << _phoneNumber <<std::endl;
	std::cout << "DarkestSecret: " << _darkestSecret <<std::endl;
}

bool	Contact::checkEmptyContact(void) const
{
	return (_firstName.empty());
}
