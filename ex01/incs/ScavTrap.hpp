#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {

	private:

	public:
		ScavTrap(void);
		ScavTrap(std::string name);
		ScavTrap(const ScavTrap& copyName);

		~ScavTrap(void);

		void	attack(const std::string& target);
		void	guardGate();
		ScavTrap&	operator=(const ScavTrap& copyName);
};


#endif
