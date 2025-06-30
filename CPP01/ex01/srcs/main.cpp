#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name);

int	main(void)
{
	std::string	name = "zombie_name";
	Zombie		*horde;
	int			N = -5;


	if (!(horde = zombieHorde(N, name)))
		return (1);

	for (int i = 0; i < N; i++) {
		horde[i].announce();
	}

	delete [] horde;

	return (0);
}
