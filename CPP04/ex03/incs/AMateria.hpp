#ifndef AMATERIA_HPP
# define AMATERIA_HPP

#include <string>

#include "ICharacter.hpp"

class AMateria {

	protected:
		std::string	_type;

	public:
		AMateria(void);
		AMateria(const std::string& type);
		AMateria(const AMateria& copy);

		virtual ~AMateria(void);

		AMateria&	operator=(const AMateria& copy);

		const std::string&	getType() const;

		virtual	AMateria*	clone() const = 0;
		virtual void		use(ICharacter& target);
};

#endif
