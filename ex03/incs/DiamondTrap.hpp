#ifndef DIAMONDTRAP_HPP
# define DIAMONDTRAP_HPP

#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

class DiamondTrap : public ScavTrap, public FragTrap {

	private:
		std::string	_name;

	public:
		DiamondTrap(void);
		DiamondTrap(std::string name);
		DiamondTrap(const DiamondTrap& copyName);

		~DiamondTrap(void);

		DiamondTrap&	operator=(const DiamondTrap& copyName);

		void	attack(const std::string& target);
		void	whoAmI();
};

#endif
