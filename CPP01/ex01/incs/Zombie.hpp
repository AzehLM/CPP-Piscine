#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <string>

class Zombie {

	private:
		std::string _name;

	public:
		Zombie(void);
		Zombie(const std::string &name);
		~Zombie(void);

		void	announce(void) const;
		void	naming(std::string &name);
};

#endif
