#ifndef CHARACTER_HPP
# define CHARACTER_HPP

#include "AMateria.hpp"

class Character : public ICharacter {

	private:
		std::string	_name;
		AMateria*	_inventory[4];
		AMateria*	_storage[100];

	public:
		Character(void);
		Character(const std::string& name);
		Character(const Character& src);

		~Character(void);

		Character&	operator=(const Character& src);

		const std::string& getName() const;

		void	equip(AMateria* m);
		void	unequip(int idx);
		void	use(int idx, ICharacter& target);
};

#endif
