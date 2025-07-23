#ifndef WRONGANIMAL_CPP
# define WRONGANIMAL_CPP

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
