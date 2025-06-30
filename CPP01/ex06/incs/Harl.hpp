#ifndef HARL_HPP
# define HARL_HPP

# include <string>

typedef enum levelEnum
{
	DEBUG,
	ERROR,
	INFO,
	WARNING,
	OTHER
}	e_levelEnum;

class Harl {

	private:
		void	debug(void);
		void	info(void);
		void	warning(void);
		void	error(void);
		void	other(void);
	public:
		Harl(void);
		~Harl(void);

		void	complain(std::string level);
};


#endif
