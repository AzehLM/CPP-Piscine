#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <string>

class Animal {

	protected:
		std::string _type;

	public:
		Animal(void);
		Animal(const std::string& type);
		Animal(const Animal& copyType);

		virtual ~Animal(void);

		Animal&	operator=(const Animal& copyType);

		const std::string&		getType() const;
		virtual void			makeSound() const;
};

#endif
