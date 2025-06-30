#ifndef HARL_HPP
# define HARL_HPP

# include <string>

class Harl {

	private:

		void	(Harl::*_memberFunctions[5])(void);

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
