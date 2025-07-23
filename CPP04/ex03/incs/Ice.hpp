#ifndef ICE_HPP
# define ICE_HPP

#include "AMateria.hpp"

class Ice : public AMateria {

	private:

	public:
		Ice(void);
		Ice(const Ice& src);
		~Ice(void);

		Ice&	operator=(const Ice& src);

		AMateria*	clone() const;
		void		use(ICharacter& target);
};

#endif
