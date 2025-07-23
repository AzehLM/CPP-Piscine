#ifndef CAT_HPP
# define CAT_HPP

# include "Animal.hpp"
# include "Brain.hpp"

class Cat : public Animal {

	private:
		Brain* _brainIdeas;

	public:
		Cat(void);
		Cat(const Cat& copyName);

		~Cat(void);

		Cat&	operator=(const Cat& copyName);

		void		makeSound() const;
		std::string	getIdea(int index) const;
		void		setIdea(int index, std::string idea);
};

#endif
