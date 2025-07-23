#ifndef DOG_HPP
# define DOG_HPP

# include "Animal.hpp"

class Dog : public Animal {

	public:
		Dog(void);
		Dog(const Dog& copyName);

		~Dog(void);

		Dog&	operator=(const Dog& copyName);

		void	makeSound() const;
};

#endif
