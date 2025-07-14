#include "limits.h"

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(void) : ClapTrap() {

	this->_hitPoints = 100;
	this->_energyPoints = 50;
	this->_attackDamage = 20;

	std::cout << YELLOW "ScavTrap default constructor called" RESET << std::endl;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {

	this->_hitPoints = 100;
	this->_energyPoints = 50;
	this->_attackDamage = 20;

	std::cout << YELLOW "ScavTrap " << this->_name <<" constructor by name called" RESET << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& copyName) : ClapTrap(copyName) {

	*this = copyName;

	std::cout << GREEN << this->_name << " copy constructor called" RESET << std::endl;
}

ScavTrap::~ScavTrap(void) {
	std::cout << this->_name << " destructor called" << std::endl;

}

void	ScavTrap::guardGate(void) {

	if (_energyPoints == 0 || _hitPoints == 0) {
		std::cout << RED "ScavTrap " << _name << " cannot change to Gate keeper mode." RESET << std::endl;
		return ;
	}

	_energyPoints--;
	std::cout << MAGENTA << this->_name << " is now in Gate keeper mode." RESET << std::endl;
}

void	ScavTrap::attack(const std::string& target) {

	if (_energyPoints == 0 || _hitPoints == 0) {
		std::cout << RED "ScavTrap " << _name << " cannot attack " << target << "." RESET << std::endl;
		return ;
	}

	_energyPoints--;
	std::cout << MAGENTA "ScavTrap " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage!" RESET << std::endl;
}


ScavTrap&	ScavTrap::operator=(const ScavTrap& copyName) {

	std::cout << BLUE "Copy assignment operator called" RESET << std::endl;

	if (this != &copyName) {
		this->_name = copyName._name;
		this->_hitPoints = copyName._hitPoints;
		this->_energyPoints = copyName._energyPoints;
		this->_attackDamage = copyName._attackDamage;
	}

	return (*this);
}
