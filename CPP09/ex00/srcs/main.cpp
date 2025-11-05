#include <cstdlib>
#include <iostream>

#include "BitcoinExchange.hpp"

int	main(int ac, char **av)
{
	if (ac < 2) {
		std::cout << "Usage: ./btc <input_file>" << std::endl;
		return (EXIT_FAILURE);
	}

	std::string	input = av[1];
	std::string	database;

	if (ac == 3) {
		database = av[2];
	} else {
		database = "database/data.csv";
	}

	try
	{
		BitcoinExchange btc(database, input);
		btc.processInput();
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	return (EXIT_SUCCESS);
}
