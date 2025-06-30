#include "Zombie.hpp"

Zombie* newZombie(std::string name);
void	randomChump(std::string name);

int	main(void)
{
	Zombie	*firstZombie;

	firstZombie = newZombie("Matt");
	firstZombie->announce();

	delete (firstZombie);

	randomChump("Daemon");

	return (0);
}
