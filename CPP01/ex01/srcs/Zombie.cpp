#include <iostream>

#include "Zombie.hpp"

Zombie::Zombie(void) : _name("") {}

Zombie::Zombie(const std::string &name) : _name(name) {}

Zombie::~Zombie(void) {}

void	Zombie::announce(void) const
{
	std::cout << this->_name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void	Zombie::naming(std::string &name)
{
	this->_name = name;
}
