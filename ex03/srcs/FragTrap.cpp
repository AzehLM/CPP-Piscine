#include "FragTrap.hpp"

FragTrap::FragTrap(void) : ClapTrap() {

	this->_hitPoints = 100;
	this->_energyPoints = 100;
	this->_attackDamage = 30;

	std::cout << YELLOW "Default FragTrap constructor called" RESET << std::endl;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name) {

	this->_hitPoints = 100;
	this->_energyPoints = 100;
	this->_attackDamage = 30;

	std::cout << YELLOW "FragTrap " << this->_name << " name constructor called" RESET << std::endl;
}

FragTrap::FragTrap(const FragTrap& copyName) : ClapTrap(copyName) {

	*this = copyName;

	std::cout << GREEN << this->_name << " copy construtor called" RESET << std::endl;
}

FragTrap::~FragTrap(void) {
	std::cout << "FragTrap " << this->_name << " destructor called" << std::endl;
}

FragTrap&	FragTrap::operator=(const FragTrap& copyName) {

	std::cout << BLUE "Copy assignment operator called" RESET << std::endl;

	if (this != &copyName) {
		this->_name = copyName._name;
		this->_hitPoints = copyName._hitPoints;
		this->_energyPoints = copyName._energyPoints;
		this->_attackDamage = copyName._attackDamage;
	}

	return (*this);
}


void	FragTrap::attack(const std::string& target) {

	if (_energyPoints == 0 || _hitPoints == 0) {
		std::cout << RED "FragTrap " << _name << " cannot attack " << target << "." RESET << std::endl;
		return ;
	}

	_energyPoints--;
	std::cout << MAGENTA "FragTrap " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage!" RESET << std::endl;
}

void	FragTrap::highFivesGuys(void) {
	if (_energyPoints == 0 || _hitPoints == 0) {
		std::cout << RED "FragTrap " << _name << " cannot high five." RESET << std::endl;
		return ;
	}

	_energyPoints--;
	std::cout << MAGENTA << _name << " is highfiving the other guys." RESET << std::endl;
}
