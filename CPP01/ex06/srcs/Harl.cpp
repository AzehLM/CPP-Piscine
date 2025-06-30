#include <iostream>

#include "Harl.hpp"

Harl::Harl(void) {}

Harl::~Harl(void) {}

void	Harl::debug(void)
{
	std::cout
		<< "[DEBUG] "
		<< "First step into being happy." << std::endl;
}

void	Harl::info(void)
{
	std::cout
		<< "[INFO] "
		<< "Should be first step tho, gives insight on your work." << std::endl;
}

void	Harl::warning(void)
{
	std::cout
		<< "[WARNING] "
		<< "Did you friend told you to write this ? If so, change friends" << std::endl;
}

void	Harl::error(void)
{

	std::cout
		<< "[ERROR] "
		<< "This is unacceptable! I want to speak to your manager. Now!" << std::endl;
}

void	Harl::other(void)
{
	std::cout
		<< "[OTHER] "
		<< "Would have been funnier if it was an 'otter'. " << std::endl;
	std::cout << "Anyway, change command this one doesn't exist..." << std::endl;
}

void	Harl::complain(std::string level)
{
	const std::string levels[4] = {"DEBUG", "ERROR", "INFO", "WARNING"};

	size_t	start = 0;

	for (; start < OTHER; start++)
		if (levels[start] == level)
			break ;

	switch (start)
	{
		case DEBUG:
			this->debug(); //fallthrough
		case INFO:
			this->info(); //fallthrough
		case WARNING:
			this->warning(); //fallthrough
		case ERROR:
			this->error();
			break ;
		default:
			this->other();
	}
}
