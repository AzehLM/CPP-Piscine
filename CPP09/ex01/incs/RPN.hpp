#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <string>

class RPN {

	private:
		std::stack<double>	_stack;

		bool	isValidOperator(const std::string& input);
		bool	isValidNumber(const std::string& input);
		double	operate(double a, double b, char op);

	public:
		RPN(void);
		RPN(const RPN& src);

		~RPN(void);

		RPN&	operator=(const RPN& src);

		double	getResult(const std::string& input);
	};

#endif
