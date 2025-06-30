#include "Weapon.hpp"

Weapon::Weapon(const std::string& weapon) : _type(weapon) {}

Weapon::~Weapon(void) {}

const std::string&	Weapon::getType(void) const
{
	return (this->_type);
}

void	Weapon::setType(const std::string& type)
{
	this->_type = type;
}
