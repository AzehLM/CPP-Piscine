#include "MateriaSource.hpp"

MateriaSource::MateriaSource(void) {
	for (int i = 0; i < 4; i++) {
		_interface[i] = NULL;
	}
}

MateriaSource::MateriaSource(const MateriaSource& src) {

	for (int i = 0; i < 4; i++) {
		_interface[i] = (src._interface[i]) ? (src._interface[i]->clone()) : NULL;
	}
}

MateriaSource&	MateriaSource::operator=(const MateriaSource& src) {

	if (this != &src) {
		for (int i = 0; i < 4; i++) {
			delete _interface[i];
			_interface[i] = (src._interface[i]) ? (src._interface[i]->clone()) : NULL;
		}
	}
	return (*this);
}

MateriaSource::~MateriaSource(void) {
	for (int i = 0; i < 4; i++) {
		delete _interface[i];
	}
}

void	MateriaSource::learnMateria(AMateria* materia) {

	if (!materia)
		return;

	for (int i = 0; i < 4; i++) {
		if (_interface[i] == NULL) {
			_interface[i] = materia;
			break;
		}
	}
}

AMateria*	MateriaSource::createMateria(const std::string& type) {

	for (int i = 0; i < 4; i++) {
		if (_interface[i] && _interface[i]->getType() == type) {
			return (_interface[i]->clone());
		}
	}
	return (NULL);
}
