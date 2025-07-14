#include "DiamondTrap.hpp"

int	main(void)
{
	std::cout << "=== TESTS CONSTRUCTEURS ===" << std::endl;
	std::cout << "\n--- Constructeur par défaut ---" << std::endl;
	DiamondTrap	diamond1;
	diamond1.whoAmI();

	std::cout << "\n--- Constructeur avec paramètre ---" << std::endl;
	DiamondTrap	diamond2("Alice");
	diamond2.whoAmI();

	std::cout << "\n--- Constructeur de copie ---" << std::endl;
	DiamondTrap	diamond3(diamond2);
	diamond3.whoAmI();

	std::cout << "\n=== TESTS OPÉRATEUR D'ASSIGNATION ===" << std::endl;
	DiamondTrap	diamond4("Bob");
	diamond4.whoAmI();
	std::cout << "Assignation de diamond2 vers diamond4:" << std::endl;
	diamond4 = diamond2;
	diamond4.whoAmI();

	std::cout << "\n=== TESTS MÉTHODES HÉRITÉES ===" << std::endl;
	DiamondTrap	hero("Hero");

	std::cout << "\n--- Test attack (héritée de ScavTrap) ---" << std::endl;
	hero.attack("Goblin");
	hero.attack("Orc");
	hero.attack("Dragon");

	std::cout << "\n--- Test takeDamage ---" << std::endl;
	hero.takeDamage(30);
	hero.takeDamage(50);
	hero.takeDamage(200); // Plus que les HP restants

	std::cout << "\n--- Test beRepaired ---" << std::endl;
	hero.beRepaired(25);
	hero.beRepaired(10);

	std::cout << "\n=== TESTS MÉTHODES SPÉCIALES ===" << std::endl;
	DiamondTrap	warrior("Warrior");

	std::cout << "\n--- Test guardGate (de ScavTrap) ---" << std::endl;
	warrior.guardGate();
	warrior.guardGate();

	std::cout << "\n--- Test highFivesGuys (de FragTrap) ---" << std::endl;
	warrior.highFivesGuys();
	warrior.highFivesGuys();

	std::cout << "\n--- Test whoAmI (propre à DiamondTrap) ---" << std::endl;
	warrior.whoAmI();

	std::cout << "\n=== TESTS LIMITES ÉNERGIE ===" << std::endl;
	DiamondTrap	tired("Tired");
	tired.clapTrapState();

	for (int i = 0; i < 55; i++) // énergie initiale (50)
	{
		std::cout << "Action " << i + 1 << ": ";
		if (i % 2 == 0)
			tired.attack("enemy");
		else
			tired.beRepaired(1);
		tired.clapTrapState();
	}

	std::cout << "\n=== TESTS AVEC POINTEURS ===" << std::endl;
	std::cout << "\n--- Test polymorphisme ---" << std::endl;
	ClapTrap*	poly1 = new DiamondTrap("Poly1");
	ScavTrap*	poly2 = new DiamondTrap("Poly2");
	FragTrap*	poly3 = new DiamondTrap("Poly3");

	poly1->attack("target1");
	poly2->attack("target2");
	poly3->attack("target3");

	std::cout << "\n=== TESTS SCENARIOS COMPLEXES (not at all) ===" << std::endl;
	DiamondTrap	fighter("Fighter");
	DiamondTrap	opponent("Opponent");

	std::cout << "\n--- Combat simulé ---" << std::endl;
	fighter.whoAmI();
	opponent.whoAmI();

	std::cout << "\n-- Round 1 --" << std::endl;
	fighter.attack("Opponent");
	opponent.takeDamage(30);
	opponent.attack("Fighter");
	fighter.takeDamage(30);

	std::cout << "\n-- Round 2 --" << std::endl;
	fighter.guardGate();
	opponent.highFivesGuys();

	std::cout << "\n-- Réparations --" << std::endl;
	fighter.beRepaired(20);
	opponent.beRepaired(15);

	std::cout << "\n-- Round final --" << std::endl;
	fighter.attack("Opponent");
	opponent.takeDamage(30);

	std::cout << "\n=== FIN DES TESTS ===" << std::endl;
	std::cout << "Destruction automatique des objets..." << std::endl;

	return (0);
}
