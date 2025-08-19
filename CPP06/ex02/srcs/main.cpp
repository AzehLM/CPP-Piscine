#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>

#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

// Testing purposes classes
#include "colors.h"
#include "D.hpp"
#include "Tmp.hpp"

static Base*	generate(void)
{
	int		r = (rand() % 3) + 1;

	Base* base;

	if (r == 1) {
		base = new A;
		return (base);
	} else if (r == 2) {
		base = new B;
		return (base);
	}
	base = new C;
	return (base);

}

static void	identify(Base* p)
{
	std::cout << "Pointer identification:		";
	if (p == NULL) {
		std::cout << "(null) pointer" << std::endl;
	} else if (dynamic_cast<A*>(p) != NULL) {
		std::cout << "'A'" << std::endl;
	} else if (dynamic_cast<B*>(p) != NULL) {
		std::cout << "'B'" << std::endl;
	} else if (dynamic_cast<C*>(p) != NULL) {
		std::cout << "'C'" << std::endl;
	} else {
		std::cout << "unknown type" << std::endl;
	}
}

static void	identify(Base& p)
{
	std::cout << "Reference identification:	";
	try
	{
		A a = dynamic_cast<A&>(p);
		std::cout << "'A'" << std::endl;
		return ;
	}
	catch(const std::exception& e) {
		// std::cout << e.what() << std::endl;
	}
	try
	{
		B b = dynamic_cast<B&>(p);
		std::cout << "'B'" << std::endl;
		return ;

	}
	catch(const std::exception& e) {
		// std::cout << e.what() << std::endl;
	}
	try
	{
		C c = dynamic_cast<C&>(p);
		std::cout << "'C'" << std::endl;
		return ;
	}
	catch(const std::exception& e) {
		// std::cout << e.what() << std::endl;
	}

	std::cout << "unknown type" << std::endl;
}

int	main(void)
{
	srand (time(NULL));

	std::cout << CYAN "\tTest 1: Functionnal showcase" RESET << std::endl;
	{
		Base* ptr = generate();
		Base& ptrRef = *ptr;

		identify(ptr);
		identify(ptrRef);

		delete ptr;
	}
	{
		std::cout << std::endl;
		std::cout << CYAN "\tTest 2: (null) pointer and unknown reference" RESET << std::endl;

		Base* ptr = generate();

		Tmp* ptrr = NULL;

		identify(ptr);
		identify(*ptr);

		identify((Base*)ptrr);
		identify((Base&)*ptrr);

		delete ptr;
		std::cout << std::endl;
	}
	{
		std::cout << CYAN "\tTest 3: Unknown pointer type" RESET << std::endl;
		Base* unknownPtr = new D;

		identify(unknownPtr);

		delete unknownPtr;
	}

	return (0);
}
