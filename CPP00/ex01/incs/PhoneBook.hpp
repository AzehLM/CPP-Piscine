/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:23:32 by gueberso          #+#    #+#             */
/*   Updated: 2025/05/04 20:36:59 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"

class PhoneBook {

	private:
		Contact		_contacts[8];
		int			_index;

	public:
		PhoneBook();
		~PhoneBook();

		bool		addContact(void);
		bool		searchContact(void) const;
		void		displayContactList(void) const;
};

#endif
