#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <map>
# include <string>

class BitcoinExchange {

	private:
		std::map<std::string, double>	_database;
		std::string 					_inputFilename;
		BitcoinExchange(void);

	public:
		BitcoinExchange(const BitcoinExchange& src);
		BitcoinExchange(const std::string& databaseFile, const std::string& inputFile);

		~BitcoinExchange(void);

		BitcoinExchange& operator=(const BitcoinExchange& src);

		double	getExchangeRate(const std::string& date);

		void	loadDatabase(const std::string& filename);
		void	loadInput(const std::string& filename);

		void	processInput();

		void	trimWhitespace(std::string& str);

		bool	isLeapYear(int year);
		bool	isValidDate(const std::string& date);
		bool	isValidValue(double value);
};

#endif
