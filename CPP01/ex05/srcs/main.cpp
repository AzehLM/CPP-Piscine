#include <iostream>

#include "Harl.hpp"

int	main(int ac, char **av)
{
	Harl	harl;

	if (ac < 2)
	{
		harl.complain("DEBUG");
		harl.complain("INFO");
		harl.complain("WARNING");
		harl.complain("ERROR");
		harl.complain("TEST");
		harl.complain("     ");
	}
	else {
		for (int i = 1; i < ac; i++) {
			harl.complain(av[i]);
		}
	}
	return (0);
}
