#include <iostream>

#include "colors.h"
#include "Serializer.hpp"

int	main(void)
{
	{
		Data* data = new Data(20, "yo");

		std::cout << "Raw data:		" << GREEN << data << RESET << std::endl;
		std::cout << BLUE << *data << RESET << std::endl;
		std::cout << std::endl;

		uintptr_t raw = Serializer::serialize(data);
		std::cout << "Data serialized:	" << RED << raw << RESET << std::endl;
		std::cout << std::endl;

		data = Serializer::deserialize(raw);
		std::cout << "Data deserialized:	"  << GREEN << data << RESET << std::endl;
		std::cout << BLUE << *data << RESET << std::endl;

		delete data;
	}
	return (0);
}
