#include <iostream>

#include "colors.h"
#include "Span.hpp"

int	main(void)
{
	{
		std::cout << CYAN "\t Test: building" RESET << std::endl;

		Span test(10);
		try {
			for (int i = 0; i < 15; i++) {
				test.addNumber(i);
				std::cout << test[i] << std::endl;
			}
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\t Test: shortestSpan functional" RESET << std::endl;

		Span test(3);
		Span test2(3);
		Span test3(3);
		Span test4(4);
		Span test5(5);
		Span test6(1);

		try
		{
			test.addNumber(1);
			test.addNumber(10);
			test.addNumber(12);

			test2.addNumber(5);
			test2.addNumber(5);
			test2.addNumber(10);

			test3.addNumber(100);
			test3.addNumber(200);
			test3.addNumber(201);

			test4.addNumber(-1);
			test4.addNumber(-5);
			test4.addNumber(0);
			test4.addNumber(5);

			test5.addNumber(1);
			test5.addNumber(2);
			test5.addNumber(3);
			test5.addNumber(4);
			test5.addNumber(5);

			test6.addNumber(2);
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
		try
		{
			std::cout << "test1: " << test.shortestSpan() << std::endl;
			std::cout << "test2: " << test2.shortestSpan() << std::endl;
			std::cout << "test3: " << test3.shortestSpan() << std::endl;
			std::cout << "test4: " << test4.shortestSpan() << std::endl;
			std::cout << "test5: " << test5.shortestSpan() << std::endl;
			std::cout << "test6: " << test6.shortestSpan() << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\t Test: longestSpan functional" RESET << std::endl;

		Span test(3);
		Span test2(3);
		Span test3(3);
		Span test4(4);
		Span test5(5);
		Span test6(1);

		try
		{
			test.addNumber(1);
			test.addNumber(10);
			test.addNumber(12);

			test2.addNumber(5);
			test2.addNumber(5);
			test2.addNumber(10);

			test3.addNumber(100);
			test3.addNumber(200);
			test3.addNumber(201);

			test4.addNumber(-1);
			test4.addNumber(-5);
			test4.addNumber(0);
			test4.addNumber(5);

			test5.addNumber(1);
			test5.addNumber(2);
			test5.addNumber(3);
			test5.addNumber(4);
			test5.addNumber(5);

			test6.addNumber(2);
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
		try
		{
			std::cout << "test1: " << test.longestSpan() << std::endl;
			std::cout << "test2: " << test2.longestSpan() << std::endl;
			std::cout << "test3: " << test3.longestSpan() << std::endl;
			std::cout << "test4: " << test4.longestSpan() << std::endl;
			std::cout << "test5: " << test5.longestSpan() << std::endl;
			std::cout << "test6: " << test6.longestSpan() << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tTest addNumbers" RESET << std::endl;
		Span test(30);

		try
		{
			std::vector<int> tmp;

			for (int i = 0; i < 5; i++) {
				tmp.push_back(i);
			}

			test.addNumbers(tmp.begin(), tmp.end());

			test.print();
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
	}

	return (0);
}
