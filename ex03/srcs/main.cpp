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
	std::cout << std::endl;
}

void	testCaseDegenerateTriangle(void)
{
	Point const	a(2, 0);
	Point const	b(2, 5);
	Point const	c(2, 9);

	Point const	point(2, 9);

	std::cout << CYAN "TEST 4: degenerate triangle" << RESET << std::endl;

	if (bsp(a, b, c, point))
		std::cout << GREEN "true: P is inside the triangle" << RESET << std::endl;
	else
		std::cout << RED "false: P is not inside the triangle" << RESET << std::endl;
	std::cout << std::endl;
}

void	testCaseNegativeCoordinates(void)
{
	Point const	a(-3, -2);
	Point const	b(-1, -4);
	Point const	c(-5, -6);

	Point const	point(-3, -4);

	std::cout << CYAN "TEST 5: triangle with all negative coordinates" << RESET << std::endl;

	if (bsp(a, b, c, point))
		std::cout << GREEN "true: P is inside the triangle" << RESET << std::endl;
	else
		std::cout << RED "false: P is not inside the triangle" << RESET << std::endl;
	std::cout << std::endl;
}

void	testCaseMixedSignCoordinates(void)
{
	Point const	a(-2, 1);
	Point const	b(3, -1);
	Point const	c(1, 4);

	Point const	point(0.5, 1.2);

	std::cout << CYAN "TEST 6: triangle crossing axes (mixed positive/negative)" << RESET << std::endl;

	if (bsp(a, b, c, point))
		std::cout << GREEN "true: P is inside the triangle" << RESET << std::endl;
	else
		std::cout << RED "false: P is not inside the triangle" << RESET << std::endl;
	std::cout << std::endl;
}

void	testCaseVeryCloseToEdge(void)
{
	Point const	a(0, 0);
	Point const	b(4, 0);
	Point const	c(2, 3);

	Point const	point(2, 0.01f);

	std::cout << CYAN "TEST 7: point very close to edge (precision test)" << RESET << std::endl;

	if (bsp(a, b, c, point))
		std::cout << GREEN "true: P is inside the triangle" << RESET << std::endl;
	else
		std::cout << RED "false: P is not inside the triangle" << RESET << std::endl;
	std::cout << std::endl;
}

void	testCaseVerySmallTriangle(void)
{
	Point const	a(0, 0);
	Point const	b(0.1f, 0);
	Point const	c(0.05f, 0.1f);

	Point const	point(0.05f, 0.03f);

	std::cout << CYAN "TEST 8: very small triangle" << RESET << std::endl;

	if (bsp(a, b, c, point))
		std::cout << GREEN "true: P is inside the triangle" << RESET << std::endl;
	else
		std::cout << RED "false: P is not inside the triangle" << RESET << std::endl;
	std::cout << std::endl;
}

void	testCaseVeryLargeTriangle(void)
{
	Point const	a(-1000, -1000);
	Point const	b(1000, -1000);
	Point const	c(0, 1000);

	Point const	point(0, 0);

	std::cout << CYAN "TEST 9: very large triangle" << RESET << std::endl;

	if (bsp(a, b, c, point))
		std::cout << GREEN "true: P is inside the triangle" << RESET << std::endl;
	else
		std::cout << RED "false: P is not inside the triangle" << RESET << std::endl;
	std::cout << std::endl;
}

void	testCasePointFarOutside(void)
{
	Point const	a(1, 1);
	Point const	b(3, 1);
	Point const	c(2, 3);

	Point const	point(-100, -100);

	std::cout << CYAN "TEST 10: point very far outside triangle" << RESET << std::endl;

	if (bsp(a, b, c, point))
		std::cout << GREEN "true: P is inside the triangle" << RESET << std::endl;
	else
		std::cout << RED "false: P is not inside the triangle" << RESET << std::endl;
	std::cout << std::endl;
}

void	testCaseClockwiseTriangle(void)
{
	Point const	a(0, 0);
	Point const	b(0, 4);
	Point const	c(4, 0);

	Point const	point(1, 1);

	std::cout << CYAN "TEST 11: clockwise oriented triangle" << RESET << std::endl;

	if (bsp(a, b, c, point))
		std::cout << GREEN "true: P is inside the triangle" << RESET << std::endl;
	else
		std::cout << RED "false: P is not inside the triangle" << RESET << std::endl;
	std::cout << std::endl;
}

void	testCaseNearlyDegenerateTriangle(void)
{
	Point const	a(0, 0);
	Point const	b(10, 0);
	Point const	c(5, 0.01f);

	Point const	point(5, 0.005f);

	std::cout << CYAN "TEST 12: nearly degenerate triangle (very flat)" << RESET << std::endl;

	if (bsp(a, b, c, point))
		std::cout << GREEN "true: P is inside the triangle" << RESET << std::endl;
	else
		std::cout << RED "false: P is not inside the triangle" << RESET << std::endl;
	std::cout << std::endl;
}

void	testCaseZeroCoordinates(void)
{
	Point const	a(0, 0);
	Point const	b(2, 0);
	Point const	c(1, 2);

	Point const	point(0, 0);

	std::cout << CYAN "TEST 13: point exactly on vertex (0,0)" << RESET << std::endl;

	if (bsp(a, b, c, point))
		std::cout << GREEN "true: P is inside the triangle" << RESET << std::endl;
	else
		std::cout << RED "false: P is not inside the triangle" << RESET << std::endl;
	std::cout << std::endl;
}

void	testCaseTriangleAroundOrigin(void)
{
	Point const	a(-1, -1);
	Point const	b(1, -1);
	Point const	c(0, 1);

	Point const	point(0, 0);

	std::cout << CYAN "TEST 14: triangle around origin, point at (0,0)" << RESET << std::endl;

	if (bsp(a, b, c, point))
		std::cout << GREEN "true: P is inside the triangle" << RESET << std::endl;
	else
		std::cout << RED "false: P is not inside the triangle" << RESET << std::endl;
	std::cout << std::endl;
}

void	testCaseRightTriangle(void)
{
	Point const	a(0, 0);
	Point const	b(3, 0);
	Point const	c(0, 4);

	Point const	point(1, 1);

	std::cout << CYAN "TEST 15: right triangle" << RESET << std::endl;

	if (bsp(a, b, c, point))
		std::cout << GREEN "true: P is inside the triangle" << RESET << std::endl;
	else
		std::cout << RED "false: P is not inside the triangle" << RESET << std::endl;
	std::cout << std::endl;
}

void	testCaseEquilateralTriangle(void)
{
	Point const	a(0, 0);
	Point const	b(2, 0);
	Point const	c(1, 1.732f);

	Point const	point(1, 0.866f);

	std::cout << CYAN "TEST 16: equilateral triangle" << RESET << std::endl;

	if (bsp(a, b, c, point))
		std::cout << GREEN "true: P is inside the triangle" << RESET << std::endl;
	else
		std::cout << RED "false: P is not inside the triangle" << RESET << std::endl;
	std::cout << std::endl;
}

void	testCaseNegativePoint(void)
{
	Point const	a(1, 1);
	Point const	b(4, 1);
	Point const	c(2.5f, 4);

	Point const	point(-2, -3);

	std::cout << CYAN "TEST 17: negative point with positive triangle" << RESET << std::endl;

	if (bsp(a, b, c, point))
		std::cout << GREEN "true: P is inside the triangle" << RESET << std::endl;
	else
		std::cout << RED "false: P is not inside the triangle" << RESET << std::endl;
	std::cout << std::endl;
}

void	testCaseAlmostOnEdge(void)
{
	Point const	a(0, 0);
	Point const	b(4, 0);
	Point const	c(2, 3);

	Point const	point(2, -0.001f);

	std::cout << CYAN "TEST 18: point almost on edge but outside" << RESET << std::endl;

	if (bsp(a, b, c, point))
		std::cout << GREEN "true: P is inside the triangle" << RESET << std::endl;
	else
		std::cout << RED "false: P is not inside the triangle" << RESET << std::endl;
	std::cout << std::endl;
}

int	main(void)
{
	testCasePointIn();

	testCasePointVertice();
	testCasePointOnEdge();
	testCaseDegenerateTriangle();

	testCaseNegativeCoordinates();
	testCaseMixedSignCoordinates();

	testCaseVeryCloseToEdge();

	testCaseVerySmallTriangle();

	testCaseVeryLargeTriangle();
	testCasePointFarOutside();

	testCaseClockwiseTriangle();
	testCaseNearlyDegenerateTriangle();

	testCaseZeroCoordinates();

	testCaseTriangleAroundOrigin();
	testCaseRightTriangle();
	testCaseEquilateralTriangle();

	testCaseNegativePoint();
	testCaseAlmostOnEdge();

	return (0);
}
