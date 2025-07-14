#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"

# define RESET		"\033[0m"

# include <iostream>

class ClapTrap {

	private:
		std::string		_name;
		unsigned int	_hitPoints;		// HP en vrai -> start at 10
		unsigned int	_energyPoints;	// starts at 10
		unsigned int	_attackDamage;	// starts at 0

	public:
		ClapTrap(void);
		ClapTrap(std::string name);
		ClapTrap(const ClapTrap& copyName);

		~ClapTrap(void);

		void		attack(const std::string& target);
		void		takeDamage(unsigned int amount);
		void		beRepaired(unsigned int amount);

		void		clapTrapState( void ) const;

		ClapTrap&	operator=(const ClapTrap& copyName);
};

#endif
