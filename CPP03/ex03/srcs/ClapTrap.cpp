#include <limits.h>

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void) : _name("Dumb"), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
	std::cout << YELLOW "Default constructor called" RESET << std::endl;
}

ClapTrap::ClapTrap(std::string name) : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
	std::cout << YELLOW "Constructor by name called" RESET << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& copyName) {
	*this = copyName;
	std::cout << GREEN "Copy constructor called" RESET << std::endl;
}

ClapTrap::~ClapTrap(void) {
	std::cout << "Destructor called" << std::endl;
}

ClapTrap&	ClapTrap::operator=(const ClapTrap& copyName) {

	std::cout << BLUE "Copy assignment operator called" RESET << std::endl;

	if (this != &copyName) {
		this->_name = copyName._name;
		this->_hitPoints = copyName._hitPoints;
		this->_energyPoints = copyName._energyPoints;
		this->_attackDamage = copyName._attackDamage;
	}

	return (*this);
}


void	ClapTrap::attack(const std::string& target) {
	if (_energyPoints == 0 || _hitPoints == 0) {
		std::cout << RED "ClapTrap " << _name << " cannot attack " << target << "." RESET << std::endl;
		return ;
	}
	_energyPoints--;
	std::cout << MAGENTA "ClapTrap " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage!" RESET << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount) {
	if (amount >= _hitPoints) {
		_hitPoints = 0;
		std::cout << MAGENTA "ClapTrap " << _name << " took " << amount << " of damage, causing them to die!" RESET << std::endl;
		return ;
	}
	_hitPoints -= amount;
	std::cout << MAGENTA "ClapTrap" << _name << " took " << amount << " of damage!" RESET << std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount) {
	if (_energyPoints == 0 || _hitPoints == 0) {
		std::cout << RED "ClapTrap " << _name << " cannot repair." RESET << std::endl;
		return ;
	}
	if ((UINT_MAX - amount) < _hitPoints) {
		std::cout << RED "ClapTrap " << _name << " cannot have more than " << UINT_MAX << " hit points!" RESET << std::endl;
		return ;
	}
	_energyPoints--;
	_hitPoints += amount;
	std::cout << MAGENTA "ClapTrap " << _name << " repaired for " << amount << " of hit points!" RESET << std::endl;

}


void	ClapTrap::clapTrapState( void ) const {
	std::cout << "\n" BLUE << _name << " has:" << "\n" << _hitPoints << " hit points" << "\n" << _energyPoints << " energy points and " << "\n" << _attackDamage << " attack damage!" << RESET << std::endl;
}
