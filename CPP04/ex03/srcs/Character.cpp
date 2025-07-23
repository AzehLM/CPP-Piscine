#include <iostream>

#include "Character.hpp"
#include "colors.h"

Character::Character(void) : _name("Default") {

	for (int i = 0; i < 4; i++) {
		_inventory[i] = NULL;
	}
	for (int i = 0; i < 100; i++) {
		_storage[i] = NULL;
	}
}

Character::Character(const std::string& name) : _name(name) {

	for (int i = 0; i < 4; i++) {
		_inventory[i] = NULL;
	}
	for (int i = 0; i < 100; i++) {
		_storage[i] = NULL;
	}
}

Character::Character(const Character& src) : _name(src._name) {

	for (int i = 0; i < 4; i++) {
		_inventory[i] =  (src._inventory[i]) ? (src._inventory[i]->clone()) : NULL;
	}
	for (int i = 0; i < 100; i++) {
		_storage[i] = (src._storage[i]) ? (src._storage[i]->clone()) : NULL;;
	}
}

Character::~Character(void) {
	for (int i = 0; i < 4; i++) {
		delete _inventory[i];
	}
	for (int i = 0; i < 100; i++) {
		delete _storage[i];
	}
}

Character&	Character::operator=(const Character& src) {

	if (this != &src) {
		this->_name = src._name;
		for (int i = 0; i < 4; i++) {
			delete _inventory[i];
			_inventory[i] =  (src._inventory[i]) ? (src._inventory[i]->clone()) : NULL;
		}
		for (int i = 0; i < 100; i++) {
			delete _storage[i];
			_storage[i] = (src._storage[i]) ? (src._storage[i]->clone()) : NULL;
		}
	}

	return (*this);
}

const std::string&	Character::getName() const {
	return (_name);
}

void	Character::equip(AMateria* m) {

	if (!m)
		return ;

	for (int i = 0; i < 4; i++) {
		if (!_inventory[i]) {
			_inventory[i] =  m;
			break ;
		}
	}
}

void	Character::unequip(int idx) {

	if (idx < 0 || idx > 3) {
		std::cout << RED "Invalid index, cannot unequip" RESET << std::endl;
		return ;
	}
	else if (!_inventory[idx]) {
		std::cout << RED "Empty index, cannot unequip nothing" RESET << std::endl;
		return ;
	}

	for (int i = 0; i < 100; i++) {
		if (!_storage[i]) {
			_storage[i] = _inventory[idx];
			_inventory[idx] = NULL;
			break ;
		}
	}

}

void	Character::use(int idx, ICharacter& target) {
	if ((idx >= 0 && idx <= 3) && this->_inventory[idx] != NULL) {
		_inventory[idx]->use(target);
	}
}
