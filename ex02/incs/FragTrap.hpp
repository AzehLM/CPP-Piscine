#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap : public ClapTrap {

	public:
		FragTrap(void);
		FragTrap(std::string name);
		FragTrap(const FragTrap& copyName);

		~FragTrap(void);

		void	attack(const std::string& target);
		void	highFivesGuys(void);

		FragTrap&	operator=(const FragTrap& copyName);
};


#endif
