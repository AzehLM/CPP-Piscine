#include <iostream>

#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongCat.hpp"

int main()
{

	{
		const Animal* meta = new Animal();
		const Animal* j = new Dog();
		const Animal* i = new Cat();
		std::cout << j->getType() << " " << std::endl;
		std::cout << i->getType() << " " << std::endl;
		i->makeSound(); //will output the cat sound!
		j->makeSound();
		meta->makeSound();

		delete meta;
		delete j;
		delete i;
	}
	{
		const Animal* schnuffi = new Dog();
		const Animal* mitzi = new Cat();
		const Animal *animalCollection[4];

		animalCollection[0] = new Cat;
		animalCollection[1] = new Dog();
		animalCollection[2] = new Animal(*mitzi);
		animalCollection[3] = new Animal(*schnuffi);
		for (size_t i = 0; i < 4; i++)
			animalCollection[i]->makeSound();

		delete schnuffi;
		delete mitzi;
		for (size_t i = 0; i < 4; i++)
			delete animalCollection[i];
	}
		std::cout << std::endl << CYAN "\t\tOWN TEST" << RESET << std::endl << std::endl;

	{
		std::cout << CYAN "\t\tTest with simple declaration" << RESET << std::endl;

		Animal	animal;
		Cat		cat;
		Dog		dog;

		std::cout << CYAN "\t\tTypes showcase" << RESET << std::endl;

		std::cout << RED << animal.getType() << RESET<< std::endl;
		std::cout << RED << cat.getType() << RESET<< std::endl;
		std::cout << RED << dog.getType() << RESET<< std::endl;

		std::cout << CYAN "\t\tSounds showcase" << RESET << std::endl;

		animal.makeSound();
		cat.makeSound();
		dog.makeSound();

		std::cout << CYAN "\t\tDestructors" << RESET << std::endl;
	}
	{
		std::cout << CYAN "\t\tTest contructor by copy + copy" << RESET << std::endl;

		Animal*	animal = new Animal();
		Cat*	cat = new Cat();
		Dog*	dog = new Dog();

		std::cout << CYAN "\t\tCopy" << RESET << std::endl;

		Animal animalCopy = *animal;
		Cat catCopy = *cat;
		Dog dogCopy = *dog;

		std::cout << CYAN "\t\tTypes showcase" << RESET << std::endl;

		std::cout << RED << animal->getType() << RESET << std::endl;
		std::cout << RED << cat->getType() << RESET << std::endl;
		std::cout << RED << dog->getType() << RESET << std::endl;

		std::cout << RED << animalCopy.getType() << RESET<< std::endl;
		std::cout << RED << catCopy.getType() << RESET<< std::endl;
		std::cout << RED << dogCopy.getType() << RESET<< std::endl;

		std::cout << CYAN "\t\tSounds showcase" << RESET << std::endl;

		animal->makeSound();
		cat->makeSound();
		dog->makeSound();

		animalCopy.makeSound();
		catCopy.makeSound();
		dogCopy.makeSound();

		std::cout << CYAN "\t\tDestructors" << RESET << std::endl;
		delete animal;
		delete cat;
		delete dog;
	}
	{
		std::cout << CYAN "\t\tTest WrongAnimal/WrongCat" << RESET << std::endl;

		WrongAnimal	wrongAnimal;
		WrongCat	wrongCat;

		WrongAnimal* wrongAnimal2 = new WrongCat;

		std::cout << CYAN "\t\tTypes showcase" << RESET << std::endl;

		std::cout << RED << wrongAnimal.getType() << RESET<< std::endl;
		std::cout << RED << wrongCat.getType() << RESET<< std::endl;

		std::cout << RED << wrongAnimal2->getType() << RESET<< std::endl;

		std::cout << CYAN "\t\tSounds showcase" << RESET << std::endl;

		wrongAnimal.makeSound();
		wrongCat.makeSound();

		wrongAnimal2->makeSound();

		std::cout << CYAN "\t\tDestructors" << RESET << std::endl;

		delete wrongAnimal2;
	}
	
	return (0);
}
