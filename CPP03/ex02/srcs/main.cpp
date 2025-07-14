#include "FragTrap.hpp"
#include "ScavTrap.hpp"

int	main(void)
{
	std::cout << CYAN "Basic constructor/destructor showcase" RESET << std::endl << std::endl;

	FragTrap	*first = new FragTrap();

	delete (first);

	std::cout << std::endl << CYAN "By name constructor showcase" RESET << std::endl << std::endl;

	FragTrap	second("FragBot");

	second.clapTrapState();
	second.attack("enemy robot");
	second.clapTrapState();
	second.highFivesGuys();

	std::cout << std::endl << CYAN "By copy constructor showcase" RESET << std::endl << std::endl;

	FragTrap	third(second);

	third.clapTrapState();
	third.highFivesGuys();
	third.takeDamage(50);
	third.clapTrapState();
	third.beRepaired(30);
	third.clapTrapState();

	std::cout << std::endl << CYAN "Assignment operator showcase" RESET << std::endl << std::endl;

	FragTrap	fourth;

	fourth = third;

	fourth.clapTrapState();
	fourth.highFivesGuys();

	std::cout << std::endl << RED "Testing virtual destructor with FragTrap" RESET << std::endl << std::endl;

	ClapTrap	*ptr = new FragTrap("Polymorphic");

	ptr->attack("target");
	delete (ptr);

	std::cout << std::endl << MAGENTA "Testing both ScavTrap and FragTrap together" RESET << std::endl << std::endl;

	ScavTrap	scav("Guardian");
	FragTrap	frag("Bomber");

	scav.clapTrapState();
	frag.clapTrapState();

	scav.guardGate();
	frag.highFivesGuys();

	scav.attack("FragTrap");
	frag.takeDamage(20);
	frag.clapTrapState();

	std::cout << std::endl << YELLOW "Testing polymorphism with array of ClapTrap pointers" RESET << std::endl << std::endl;

	ClapTrap	*robots[3];

	robots[0] = new ClapTrap("Basic");
	robots[1] = new ScavTrap("Scavenger");
	robots[2] = new FragTrap("Fragmentation");

	for (int i = 0; i < 3; i++) {
		robots[i]->attack("common enemy");
	}

	std::cout << std::endl << RED "Deleting all robots..." RESET << std::endl;

	for (int i = 0; i < 3; i++) {
		delete robots[i];
	}

	return (0);
}
