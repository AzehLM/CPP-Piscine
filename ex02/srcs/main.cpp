#include <cstdlib>
#include <iostream>

#include "PmergeMe.hpp"

int	main(int ac, char **av)
{
	if (ac < 3) {
		std::cerr << "Error: not enough parameters" << std::endl;
		return (EXIT_FAILURE);
	} else {
		try {
			PmergeMe toSort(ac, av);

			toSort.sort();

		} catch(const std::exception& e) {
			std::cerr << e.what() << std::endl;
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
