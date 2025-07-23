#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"

# define RESET		"\033[0m"

# include <string>

class WrongAnimal {

	protected:
		std::string	_type;

	public:
		WrongAnimal(void);
		WrongAnimal(const std::string& type);
		WrongAnimal(const WrongAnimal& copyType);

		~WrongAnimal(void);

		WrongAnimal&	operator=(const WrongAnimal& copyType);

		const std::string&	getType() const;
		void				makeSound() const;
};

#endif
