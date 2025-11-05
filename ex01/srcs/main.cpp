#include <exception>
#include <iostream>

#include "RPN.hpp"

int	main(int ac, char **av)
{
	if (ac != 2) {
		std::cerr << "Usage ./RPN \"STRING\"" << std::endl;
		return (1);
	}
	try {
		RPN		calc;
		double	res = calc.getResult(av[1]);
		std::cout << res << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}
