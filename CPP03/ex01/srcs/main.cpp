#include "ScavTrap.hpp"


int	main(void)
{

	std::cout << CYAN "Basic constructor/destructor showcase" << std::endl << std::endl;

	ScavTrap	*first = new (ScavTrap);

	delete (first);

	std::cout << std::endl << CYAN "By name constructor showcase" << std::endl << std::endl;

	ScavTrap	second("Second");

	second.clapTrapState();
	second.attack("bad guy 1");
	second.clapTrapState();

	std::cout << std::endl << CYAN "By copy constructor showcase" << std::endl << std::endl;

	ScavTrap	third(second);

	third.clapTrapState();
	third.guardGate();
	for (int i = 0; i < 60; i++) {
		third.attack("bad guys");
	}
	third.clapTrapState();
	third.guardGate();

	std::cout << std::endl << CYAN "Assignment operator showcase" << std::endl << std::endl;

	ScavTrap	fourth;

	fourth = third;

	fourth.clapTrapState();


	std::cout << std::endl << RED "Testing virtual member functions" RESET << std::endl << std::endl;

	ClapTrap	*ptr = new ScavTrap("Virtuose");

	ptr->attack("musician");
	delete (ptr);

	return (0);
}
