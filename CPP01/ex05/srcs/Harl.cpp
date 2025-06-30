#include <iostream>

#include "Harl.hpp"

Harl::Harl(void)
{
	_memberFunctions[0] = &Harl::debug;
	_memberFunctions[1] = &Harl::error;
	_memberFunctions[2] = &Harl::info;
	_memberFunctions[3] = &Harl::warning;
	_memberFunctions[4] = &Harl::other;
}

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
	if (level.empty()) {
		std::cout << "Error: empty level" << std::endl;
        return ;
	}

	const std::string	_level[4] = {"DEBUG", "ERROR", "INFO", "WARNING"};

	for (int i = 0; i < 4; i++) {
		if (_level[i] == level) {
			(this->*_memberFunctions[i])();
			return ;
		}
	}
	(this->*_memberFunctions[4])();
}
