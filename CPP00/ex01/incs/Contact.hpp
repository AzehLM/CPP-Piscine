/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:24:15 by gueberso          #+#    #+#             */
/*   Updated: 2025/05/04 12:26:23 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <string>

class Contact {

	private:
		std::string	_firstName;
		std::string	_lastName;
		std::string	_nickName;
		std::string	_phoneNumber;
		std::string	_darkestSecret;

	public:
		Contact();
		~Contact();

		void	setFirstName(const std::string &firstname);
		void	setLastName(const std::string &lastName);
		void	setNickName(const std::string &nickName);
		void	setPhoneNumber(const std::string &phoneNumber);
		void	setDarkestSecret(const std::string &darkestSecret);

		std::string	getFirstName(void) const;
		std::string	getLastName(void) const;
		std::string	getNickName(void) const;
		std::string	getPhoneNumber(void) const;
		std::string	getDarkestSecret(void) const;

		void	displayInfos(void) const;
		bool	checkEmptyContact(void) const;
};

#endif
