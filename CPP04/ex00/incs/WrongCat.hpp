#ifndef WRONGCAT_HPP
# define WRONGCAT_HPP

#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal {

	public:
		WrongCat(void);
		WrongCat(const WrongCat& copyName);

		~WrongCat(void);

		WrongCat&	operator=(const WrongCat& copyName);

		void		makeSound() const;
};

#endif
