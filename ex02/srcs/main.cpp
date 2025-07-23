#include <iostream>

#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongCat.hpp"
#include "Brain.hpp"

int	main(void)
{
	// {
	// 	Animal yo;
	// }

	{
		Animal* test = new Dog();

		test->makeSound();
		delete test;
	}
	{
		const Animal *j = new Dog();
		const Animal *i = new Cat();
		delete j; // should not create a leak
		delete i;
	}
	std::cout << std::endl;
	{
		std::cout << "Subject asked test: " << std::endl;
		Animal* array[10];
		int i = 0;

		for (; i < 5; i++) {
			array[i] = new Dog();
		}

		for (; i < 10; i++) {
			array[i] = new Cat();
		}
		for (int j = 0; j < i; j++) {
			array[j]->makeSound();
		}
		for (int k = 0; k < i; k++) {
			delete array[k];
		}
	}
	{
		Animal* dumbCat[2];

		for (int i = 0; i < 2; i++) {
			dumbCat[i] = new Cat();
			std:: cout << dumbCat[i]->getType() << std::endl;
			delete dumbCat[i];
		}

		Cat* thinkingCats[2];
		for (int i = 0; i < 2; i++) {
			thinkingCats[i] = new Cat();
			for (int j = 0; j < 10; j++) {
				std:: cout << thinkingCats[i]->getIdea(j) << std::endl;
			}
			thinkingCats[i]->setIdea(0, "Should I awake my master");
			thinkingCats[i]->setIdea(1, "omw to do it anyway");
			thinkingCats[i]->setIdea(8, "done");
			std::cout << std::endl;
			for (int j = 0; j < 10; j++) {
				std:: cout << thinkingCats[i]->getIdea(j) << std::endl;
			}
			delete thinkingCats[i];
		}

	}
	{
		Cat src;

		std::cout << src.getIdea(1) << std::endl;

		Cat copy = src;

		std::cout << copy.getIdea(1) << std::endl;

		copy.setIdea(1, "test");
		std::cout << copy.getIdea(1) << std::endl;
		std::cout << src.getIdea(1) << std::endl;
		copy.makeSound();
		src.makeSound();

		Animal* copy2 = new Cat(src);
		copy2->makeSound();

		delete copy2;
		std::cout << src.getIdea(1) << std::endl;
	}
	return (0);
}
