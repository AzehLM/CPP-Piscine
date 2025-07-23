#ifndef CURE_HPP
# define CURE_HPP

#include "AMateria.hpp"

class Cure : public AMateria {

	private:

	public:
		Cure(void);
		Cure(const Cure& src);
		~Cure(void);

		Cure&		operator=(const Cure& src);

		AMateria*	clone() const;
		void		use(ICharacter& target);
};

#endif
