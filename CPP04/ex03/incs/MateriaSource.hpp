#ifndef MATERIASOURCE_HPP
# define MATERIASOURCE_HPP

# include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource {

	private:
		AMateria*	_interface[4];

	public:
		MateriaSource(void);
		MateriaSource(const MateriaSource& src);

		~MateriaSource(void);

		MateriaSource&	operator=(const MateriaSource& src);

		void		learnMateria(AMateria* materia);
		AMateria*	createMateria(const std::string& type);
};

#endif
