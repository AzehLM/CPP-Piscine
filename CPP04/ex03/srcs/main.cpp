#include "Character.hpp"
#include "Cure.hpp"
#include "Ice.hpp"
#include "MateriaSource.hpp"
#include "colors.h"
#include <iostream>

int main()
{
	std::cout << YELLOW "=== BASIC SUBJECT TEST ===" RESET << std::endl;
	{
		IMateriaSource* src = new MateriaSource();
		src->learnMateria(new Ice());
		src->learnMateria(new Cure());

		ICharacter* me = new Character("me");
		AMateria* tmp;

		tmp = src->createMateria("ice");
		me->equip(tmp);
		tmp = src->createMateria("cure");
		me->equip(tmp);

		ICharacter* bob = new Character("bob");
		me->use(0, *bob);
		me->use(1, *bob);

		delete bob;
		delete me;
		delete src;
	}
	std::cout << std::endl;

	std::cout << CYAN "=== INVENTORY MANAGEMENT TESTS ===" RESET << std::endl;
	{
		std::cout << BLUE "--- Test: Full inventory (4 slots) ---" RESET << std::endl;
		ICharacter* character = new Character("FullTester");
		IMateriaSource* source = new MateriaSource();

		source->learnMateria(new Ice());
		source->learnMateria(new Cure());

		std::cout << GREEN "Equipping 4 materias:" RESET << std::endl;
		for (int i = 0; i < 4; i++) {
			AMateria* materia = source->createMateria(i % 2 == 0 ? "ice" : "cure");
			character->equip(materia);
			std::cout << "  Equipped " << materia->getType() << " in slot " << i << std::endl;
		}

		std::cout << YELLOW "Trying to equip when inventory is full:" RESET << std::endl;
		AMateria* extra = source->createMateria("ice");
		character->equip(extra);
		std::cout << "  Extra materia should not be equipped" << std::endl;
		delete extra;

		ICharacter* target = new Character("Target1");
		std::cout << MAGENTA "Using all equipped materias:" RESET << std::endl;
		for (int i = 0; i < 4; i++) {
			std::cout << "  Slot " << i << ": ";
			character->use(i, *target);
		}

		delete target;
		delete character;
		delete source;
	}
	std::cout << std::endl;

	std::cout << CYAN "=== UNEQUIP AND STORAGE TESTS ===" RESET << std::endl;
	{
		std::cout << BLUE "--- Test: Unequip functionality ---" RESET << std::endl;
		ICharacter* character = new Character("UnequipTester");
		IMateriaSource* source = new MateriaSource();

		source->learnMateria(new Ice());
		source->learnMateria(new Cure());

		AMateria* ice1 = source->createMateria("ice");
		AMateria* cure1 = source->createMateria("cure");
		AMateria* ice2 = source->createMateria("ice");

		character->equip(ice1);
		character->equip(cure1);
		character->equip(ice2);

		ICharacter* dummy = new Character("Dummy");

		std::cout << GREEN "Before unequipping:" RESET << std::endl;
		character->use(0, *dummy);
		character->use(1, *dummy);
		character->use(2, *dummy);

		std::cout << YELLOW "Unequipping slot 1 (cure):" RESET << std::endl;
		character->unequip(1);

		std::cout << GREEN "After unequipping slot 1:" RESET << std::endl;
		character->use(0, *dummy); // Should still work
		character->use(1, *dummy); // Should do nothing
		character->use(2, *dummy); // Should still work

		// Unequip first item
		std::cout << YELLOW "Unequipping slot 0 (ice):" RESET << std::endl;
		character->unequip(0);

		std::cout << GREEN "After unequipping slot 0:" RESET << std::endl;
		character->use(0, *dummy); // Should do nothing
		character->use(2, *dummy); // Should still work

		delete dummy;
		delete character;
		delete source;
	}
	std::cout << std::endl;

	std::cout << CYAN "=== COPY CONSTRUCTOR TESTS ===" RESET << std::endl;
	{
		std::cout << BLUE "--- Test: Character copy constructor ---" RESET << std::endl;
		Character original("Original");
		IMateriaSource* source = new MateriaSource();

		source->learnMateria(new Ice());
		source->learnMateria(new Cure());

		original.equip(source->createMateria("ice"));
		original.equip(source->createMateria("cure"));

		Character copy(original);

		ICharacter* target = new Character("Target2");

		std::cout << GREEN "Original character (" << original.getName() << ") actions:" RESET << std::endl;
		original.use(0, *target);
		original.use(1, *target);

		std::cout << GREEN "Copied character (" << copy.getName() << ") actions:" RESET << std::endl;
		copy.use(0, *target);
		copy.use(1, *target);

		std::cout << YELLOW "Both should have independent inventories" RESET << std::endl;

		copy.unequip(0);

		copy.use(0, *target);
		copy.use(1, *target);

		original.use(0, *target);
		original.use(1, *target);

		original.unequip(0);
		original.use(0, *target);

		delete target;
		delete source;
	}
	std::cout << std::endl;

	std::cout << CYAN "=== ASSIGNMENT OPERATOR TESTS ===" RESET << std::endl;
	{
		std::cout << BLUE "--- Test: Character assignment operator ---" RESET << std::endl;
		Character char1("Character1");
		Character char2("Character2");
		IMateriaSource* source = new MateriaSource();

		source->learnMateria(new Ice());
		source->learnMateria(new Cure());

		char1.equip(source->createMateria("ice"));
		char1.equip(source->createMateria("cure"));

		char2.equip(source->createMateria("cure"));

		ICharacter* target = new Character("Target3");

		std::cout << GREEN "Before assignment:" RESET << std::endl;
		std::cout << "Character1: ";
		char1.use(0, *target);
		char1.use(1, *target);
		std::cout << "Character2: ";
		char2.use(0, *target);
		char2.use(1, *target);

		char2 = char1;

		std::cout << GREEN "After assignment (char2 = char1):" RESET << std::endl;
		std::cout << "Character1: ";
		char1.use(0, *target);
		char1.use(1, *target);
		std::cout << "Character2 (should be same as char1): ";
		char2.use(0, *target);
		char2.use(1, *target);

		delete target;
		delete source;
	}
	std::cout << std::endl;

	std::cout << CYAN "=== MATERIASOURCE TESTS ===" RESET << std::endl;
	{
		std::cout << BLUE "--- Test: MateriaSource capacity and unknown types ---" RESET << std::endl;
		IMateriaSource* source = new MateriaSource();

		std::cout << GREEN "Learning 4 materias (2 ice, 2 cure):" RESET << std::endl;
		source->learnMateria(new Ice());
		source->learnMateria(new Cure());
		source->learnMateria(new Ice());
		source->learnMateria(new Cure());

		std::cout << YELLOW "Trying to learn 5th materia (should be ignored):" RESET << std::endl;
		AMateria* extra = new Ice();
		source->learnMateria(extra);
		delete extra;

		std::cout << GREEN "Creating known materias:" RESET << std::endl;
		AMateria* ice = source->createMateria("ice");
		AMateria* cure = source->createMateria("cure");

		if (ice && cure) {
			std::cout << "  Successfully created: " << ice->getType() << " and " << cure->getType() << std::endl;
			delete ice;
			delete cure;
		}

		std::cout << YELLOW "Creating unknown materia type:" RESET << std::endl;
		AMateria* unknown = source->createMateria("fire");
		if (unknown == NULL) {
			std::cout << "  Correctly returned NULL for unknown materia type 'fire'" << std::endl;
		} else {
			std::cout << "  ERROR: Should have returned NULL!" << std::endl;
			delete unknown;
		}

		delete source;
	}
	std::cout << std::endl;

	std::cout << CYAN "=== EDGE CASES TESTS ===" RESET << std::endl;
	{
		std::cout << BLUE "--- Test: Null pointers and invalid indices ---" RESET << std::endl;
		ICharacter* character = new Character("EdgeTester");
		IMateriaSource* source = new MateriaSource();

		std::cout << YELLOW "Testing null materia equip:" RESET << std::endl;
		character->equip(NULL);
		std::cout << "  Null materia equip handled safely" << std::endl;

		std::cout << YELLOW "Testing null materia learn:" RESET << std::endl;
		source->learnMateria(NULL);
		std::cout << "  Null materia learn handled safely" << std::endl;

		std::cout << YELLOW "Testing invalid use indices:" RESET << std::endl;
		ICharacter* dummy = new Character("Dummy2");
		character->use(-1, *dummy);  // Invalid negative
		character->use(4, *dummy);   // Invalid too high
		character->use(999, *dummy); // Invalid way too high
		std::cout << "  Invalid indices handled safely" << std::endl;

		std::cout << YELLOW "Testing invalid unequip indices:" RESET << std::endl;
		character->unequip(-1);
		character->unequip(4);
		character->unequip(999);
		std::cout << "  Invalid unequip indices handled safely" << std::endl;

		delete dummy;
		delete character;
		delete source;
	}
	std::cout << std::endl;

	std::cout << CYAN "=== MULTIPLE CHARACTERS INTERACTION ===" RESET << std::endl;
	{
		std::cout << BLUE "--- Test: Multiple independent characters ---" RESET << std::endl;
		IMateriaSource* source = new MateriaSource();
		source->learnMateria(new Ice());
		source->learnMateria(new Cure());

		ICharacter* alice = new Character("Alice");
		ICharacter* bob = new Character("Bob");
		ICharacter* charlie = new Character("Charlie");

		alice->equip(source->createMateria("ice"));
		alice->equip(source->createMateria("cure"));

		bob->equip(source->createMateria("cure"));
		bob->equip(source->createMateria("ice"));

		charlie->equip(source->createMateria("ice"));

		std::cout << GREEN "All characters using their materias:" RESET << std::endl;
		std::cout << "Alice: ";
		alice->use(0, *bob);
		alice->use(1, *charlie);


		std::cout << "Bob: ";
		bob->use(0, *alice);
		bob->use(1, *charlie);

		std::cout << "Charlie: ";
		charlie->use(0, *alice);
		charlie->use(1, *bob); // Should do nothing (no materia in slot 1)

		delete alice;
		delete bob;
		delete charlie;
		delete source;
	}
	std::cout << std::endl;

	std::cout << GREEN "=== ALL TESTS COMPLETED SUCCESSFULLY ===" RESET << std::endl;

	return 0;
}
