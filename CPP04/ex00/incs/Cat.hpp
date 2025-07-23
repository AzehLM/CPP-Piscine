#ifndef CAT_HPP
# define CAT_HPP

# include "Animal.hpp"

class Cat : public Animal {

	public:
		Cat(void);
		Cat(const Cat& copyName);

		~Cat(void);

		Cat&	operator=(const Cat& copyName);

		void	makeSound() const;
};

#endif
