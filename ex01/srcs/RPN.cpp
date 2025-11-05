#include <cstdlib>
#include <sstream>
#include <stdexcept>

#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN& src) : _stack(src._stack) {}

RPN& RPN::operator=(const RPN& src) {

	if (this != &src) {
		_stack = src._stack;
	}
	return (*this);
}

RPN::~RPN() {}

bool	RPN::isValidOperator(const std::string& token) {
	return (token == "+" || token == "-" || token == "*" || token == "/");
}

bool	RPN::isValidNumber(const std::string& token) {

	if (token.empty())
		return (false);

	if (token.length() == 1 && token[0] >= '0' && token[0] <= '9')
		return (true);

	return (false);
}

double	RPN::operate(double a, double b, char op) {

	switch (op) {
		case '+':
			return (a + b);
		case '-':
			return (a - b);
		case '*':
			return (a * b);
		case '/':
			if (b == 0)
				throw std::runtime_error("Error: division by zero");
			return (a / b);
		default:
			throw std::runtime_error("Error: unknown operator");
	}
}

double	RPN::getResult(const std::string& input) {

	std::istringstream	iss(input);
	std::string			token;

	while (iss >> token) {

		if (isValidNumber(token)) {
			double num = token[0] - '0';
			_stack.push(num);
		}
		else if (isValidOperator(token)) {
			if (_stack.size() < 2)
				throw std::runtime_error("Error: not enough parameters");
			double b = _stack.top();
			_stack.pop();
			double a = _stack.top();
			_stack.pop();
			double result = operate(a, b, token[0]);
			_stack.push(result);
		}
		else {
			throw std::runtime_error("Error: incorrect format");
		}
	}

	if (_stack.size() != 1)
		throw std::runtime_error("Error: incorrect format");

	double result = _stack.top();
	_stack.pop();

	return (result);

}
