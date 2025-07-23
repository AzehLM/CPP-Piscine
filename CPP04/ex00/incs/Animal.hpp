#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"

# define RESET		"\033[0m"

# include <string>

class Animal {

	protected:
		std::string _type;

	public:
		Animal(void);
		Animal(const std::string& type);
		Animal(const Animal& copyType);

		virtual	~Animal(void);

		Animal&	operator=(const Animal& copyType);

		const std::string&	getType() const;
		virtual void		makeSound() const;
};

#endif
