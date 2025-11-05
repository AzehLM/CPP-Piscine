#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "BitcoinExchange.hpp"

#define WHITESPACE " \t\n\r\f\v"


BitcoinExchange::BitcoinExchange(void) {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& src) : _database(src._database), _inputFilename(src._inputFilename) {}

BitcoinExchange::BitcoinExchange(const std::string& databaseFile, const std::string& inputFile) {
	loadDatabase(databaseFile);
	loadInput(inputFile);
}

BitcoinExchange::~BitcoinExchange(void) {}


BitcoinExchange&	BitcoinExchange::operator=(const BitcoinExchange& src) {
	if (this != &src) {
		_database = src._database;
		_inputFilename = src._inputFilename;
	}
	return (*this);
}

void BitcoinExchange::loadDatabase(const std::string& filename) {

	std::ifstream	file(filename.c_str());
	if (!file.is_open()) {
		throw std::runtime_error("Error: could not open database file.");
	}
	if (!file.good()) {
		file.close();
		throw std::runtime_error("Error: database file is corrupted or unreadable.");
	}

	std::string	line;
	if (!std::getline(file, line)) {
		file.close();
		throw std::runtime_error("Error: database file is empty or header is missing.");
	}

	while (std::getline(file, line)) {
		if (file.bad()) {
			file.close();
			throw std::runtime_error("Error: failed to read from database file.");
		}

		if (line.empty())
			continue ;

		std::stringstream ss(line);
		std::string date, valueStr;

		if (std::getline(ss, date, ',') && std::getline(ss, valueStr)) {

			trimWhitespace(date);
			trimWhitespace(valueStr);

			if (date.empty() || valueStr.empty())
				continue ;

			if (isValidDate(date)) {
				std::stringstream valueStream(valueStr);
				double value;
				if (valueStream >> value && valueStream.eof()) {
					if (value >= 0) {
						_database[date] = value;
					}
				}
			}
		}
	}

	if (file.bad()) {
		file.close();
		throw std::runtime_error("Error: failed to read from database file.");
	}

	file.close();
	if (_database.empty()) {
		throw std::runtime_error("Error: no valid data found in database file.");
	}
}

void BitcoinExchange::loadInput(const std::string& filename) {
	_inputFilename = filename;
}

void BitcoinExchange::processInput() {

	std::ifstream file(_inputFilename.c_str());

	if (!file.is_open()) {
		throw std::runtime_error("Error: could not open input file.");
	}

	if (!file.good()) {
		file.close();
		throw std::runtime_error("Error: input file is corrupted or unreadable.");
	}

	std::string line;

	if (!std::getline(file, line)) {
		file.close();
		throw std::runtime_error("Error: input file is empty or header is missing.");
	}

	while (std::getline(file, line)) {
		if (file.bad()) {
			file.close();
			throw std::runtime_error("Error: failed to read from input file.");
		}

		if (line.empty())
			continue ;

		std::stringstream ss(line);
		std::string date, valueStr;

		if (std::getline(ss, date, '|') && std::getline(ss, valueStr))
		{
			trimWhitespace(date);
			trimWhitespace(valueStr);

			if (date.empty() || valueStr.empty()) {
				std::cout << "Error: bad input => " << line << std::endl;
				continue;
			}

			if (!isValidDate(date)) {
				std::cout << "Error: bad input => " << date << std::endl;
				continue;
			}

			std::stringstream valueStream(valueStr);
			double btcAmount;

			if (!(valueStream >> btcAmount) || !valueStream.eof()) {
				std::cout << "Error: bad input => " << line << std::endl;
				continue ;
			}

			if (!isValidValue(btcAmount)) {
				if (btcAmount < 0) {
					std::cout << "Error: not a positive number." << std::endl;
				} else {
					std::cout << "Error: number too large." << std::endl;
				}
				continue ;
			}

			double exchangeRate = getExchangeRate(date);

			if (exchangeRate == -1) {
				std::cout << "Error: bad input => " << date << std::endl;
				continue ;
			}

			double result = btcAmount * exchangeRate;

			std::cout << date << " => " << btcAmount << " = " << result << std::endl;
		}
		else
		{
			std::cout << "Error: bad input => " << line << std::endl;
		}
	}

	if (file.bad()) {
		file.close();
		throw std::runtime_error("Error: failed to read from input file.");
	}

	file.close();
}

bool	BitcoinExchange::isValidDate(const std::string& date) {

	if (date.empty() || date.length() != 10) {
		return (false);
	}

	if (date[4] != '-' || date[7] != '-') {
		return (false);
	}

	std::string yearStr = date.substr(0, 4);
	std::string monthStr = date.substr(5, 2);
	std::string dayStr = date.substr(8, 2);

	for (size_t i = 0; i < 4; i++) {
		if (!std::isdigit(static_cast<unsigned char>(yearStr[i])))
			return (false);
	}
	for (size_t i = 0; i < 2; i++) {
		if (!std::isdigit(static_cast<unsigned char>(monthStr[i])) ||
			!std::isdigit(static_cast<unsigned char>(dayStr[i])))
				return (false);
	}

	std::stringstream	yearStream(yearStr);
	std::stringstream	monthStream(monthStr);
	std::stringstream	dayStream(dayStr);

	int year, month, day;

	if (!(yearStream >> year) || !yearStream.eof() ||
		!(monthStream >> month) || !monthStream.eof() ||
		!(dayStream >> day) || !dayStream.eof()) {
		return (false);
	}

	if ((year < 1000 || year > 9999) || (month < 1 || month > 12) || (day < 1 || day > 31))
		return (false);

	int	daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (isLeapYear(year)) {
		daysInMonth[1] = 29;
	}

	if (day > daysInMonth[month - 1])
		return (false);
	return (true);
}

bool	BitcoinExchange::isValidValue(double value) {
	return (value >= 0 && value <= 1000);
}

double	BitcoinExchange::getExchangeRate(const std::string& date) {

	std::map<std::string, double>::iterator it = _database.find(date);
	if (it != _database.end()) {
		return (it->second);
	}

	std::map<std::string, double>::iterator lower = _database.lower_bound(date);
	if (lower == _database.begin()) {
		return (-1);
	}

	--lower;
	return (lower->second);
}


void BitcoinExchange::trimWhitespace(std::string& str) {

	if (str.empty())
		return ;

	size_t start = str.find_first_not_of(WHITESPACE);

	if (start == std::string::npos) {
		str.clear();
		return ;
	}

	size_t end = str.find_last_not_of(WHITESPACE);
	if (end != std::string::npos && start <= end) {
		str = str.substr(start, end - start + 1);
	} else {
		str.clear();
	}
}

bool	BitcoinExchange::isLeapYear(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
