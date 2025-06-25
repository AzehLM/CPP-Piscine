#include <iostream>

#include "Point.hpp"

bool bsp( Point const a, Point const b, Point const c, Point const point);


void	testCasePointIn(void)
{
	Point const	a(2, 1);
	Point const	b(6, 1);
	Point const	c(4, 5);

	Point const	point(4, 2.5);

	std::cout << CYAN "TEST 1: integer coordinates with P inside" << RESET << std::endl;

	if (bsp(a, b, c, point))
		std::cout << GREEN "true: P is inside the triangle" << RESET << std::endl;
	else
		std::cout << RED "false: P is not inside the triangle" << RESET << std::endl;
	std::cout << std::endl;
}

void	testCasePointVertice(void)
{
	Point const	a(1.5, 0.8);
	Point const	b(5.2, 1.1);
	Point const	c(3.7, 4.6);

	Point const	point(1.5, 0.8);

	std::cout << CYAN "TEST 2: floating-point coordinates with P on vertice" << RESET << std::endl;

	if (bsp(a, b, c, point))
		std::cout << GREEN "true: P is inside the triangle" << RESET << std::endl;
	else
		std::cout << RED "false: P is not inside the triangle" << RESET << std::endl;
	std::cout << std::endl;
}

void	testCasePointOnEdge(void)
{
	Point const	a(2, 1);
	Point const	b(2, 5);
	Point const	c(6.3, 1);

	Point const	point(2, 3);

	std::cout << CYAN "TEST 3: integer and floating-point coordinates with P on edge" << RESET << std::endl;

	if (bsp(a, b, c, point))
		std::cout << GREEN "true: P is inside the triangle" << RESET << std::endl;
	else
		std::cout << RED "false: P is not inside the triangle" << RESET << std::endl;
}

int	main(void)
{
	testCasePointIn();
	testCasePointVertice();
	testCasePointOnEdge();

	return (0);
}
