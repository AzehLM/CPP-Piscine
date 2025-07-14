#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap(void) : ClapTrap("unknown_clap_name"), ScavTrap(), FragTrap(), _name("Diamond") {

	_hitPoints = 100;
	_energyPoints = 50;
	_attackDamage = 30;

	std::cout << YELLOW "Default DiamondTrap constructor called" RESET << std::endl;
}

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name), _name(name) {

	_hitPoints = 100;
	_energyPoints = 50;
	_attackDamage = 30;

	std::cout << YELLOW "DiamondTrap " << this->_name << " name constructor called" RESET << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap& copyName) {

	*this = copyName;

	std::cout << GREEN << "DiamondTrap " << this->_name << " copy construtor called" RESET << std::endl;
}

DiamondTrap::~DiamondTrap() {
	std::cout << "DiamondTrap " << this->_name << " destructor called" << std::endl;
}

DiamondTrap&	DiamondTrap::operator=(const DiamondTrap& copyName) {

	std::cout << BLUE "Copy assignment operator called" RESET << std::endl;

	if (this != &copyName) {
		ClapTrap::operator=(copyName); // pour actualiser le nom de la base class egalement
		this->_name = copyName._name;
	}

	return (*this);
}

void	DiamondTrap::attack(const std::string& target) {
	ScavTrap::attack(target);
}

void	DiamondTrap::whoAmI() {

	std::cout << GREEN << "DiamondTrap _name: " << this->_name << std::endl
			<< "ClapTrap _name: " << ClapTrap::_name << RESET << std::endl;
}
