#ifndef DOG_HPP
# define DOG_HPP

# include "Animal.hpp"
# include "Brain.hpp"

class Dog : public Animal {

	private:
		Brain* _brainIdeas;

	public:
		Dog(void);
		Dog(const Dog& copyName);

		~Dog(void);

		Dog&	operator=(const Dog& copyName);

		void		makeSound() const;
		std::string	getIdea(int index) const;
		void		setIdea(int index, std::string idea);
};

#endif
