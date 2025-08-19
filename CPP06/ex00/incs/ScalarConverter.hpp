#ifndef SCALAR_CONVERTER_HPP
# define SCALAR_CONVERTER_HPP

# include <string>

class ScalarConverter {

	private:
		ScalarConverter(void);
		ScalarConverter(const ScalarConverter&);

		ScalarConverter&	operator=(const ScalarConverter&);

		static void printChar(const double nb, const bool valid);
		static void printInt(const double nb, const bool valid);
		static void printFloat(const double nb, const bool valid);
		static void printDouble(const double nb, const bool valid);

	public:
		~ScalarConverter(void);

		static void	convert(const std::string& convert);
};

#endif
