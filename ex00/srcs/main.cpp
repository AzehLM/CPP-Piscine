#include <ClapTrap.hpp>

int	main(void)
{
		ClapTrap	Alpha("Alpha");
		ClapTrap	Beta("Beta");

		std::cout << std::endl << "---------- ATTACK AND TAKE DAMAGES ----------" << std::endl << std::endl;
		Alpha.attack("Beta");
		Beta.attack("Alpha");
		Beta.takeDamage(10);
		Beta.clapTrapState();
		Alpha.takeDamage(5);
		Alpha.clapTrapState();

		std::cout << std::endl << "---------- BE REPAIRED ----------" << std::endl << std::endl;
		Alpha.beRepaired(5);
		Alpha.clapTrapState();
		Beta.beRepaired(90);
		Beta.clapTrapState();

		std::cout << std::endl << "---------- ATTACK UNTIL NOR MORE ENERGY ----------" << std::endl << std::endl;
		for (int i = 0; i < 10; i++)
			Alpha.attack("Beta");
		Alpha.beRepaired(5);
		Alpha.clapTrapState();
		std::cout << std::endl << "---------- IS DEAD ----------" << std::endl << std::endl;
		Beta.attack("Alpha");
		Beta.clapTrapState();
		Beta.takeDamage(10);
		std::cout << std::endl;
		std::cout << std::endl;
		ClapTrap	Delta("Delta");
		ClapTrap	DeltaCopy(Delta);

		std::cout << std::endl << "---------- Delta MAX REPAIR ----------" << std::endl << std::endl;
		DeltaCopy.beRepaired(4294967295);
		DeltaCopy.clapTrapState();
		DeltaCopy.beRepaired(4294967285);
		DeltaCopy.clapTrapState();
		std::cout << std::endl;
	return 0;
}
