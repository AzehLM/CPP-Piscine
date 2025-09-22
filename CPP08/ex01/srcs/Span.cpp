#include <algorithm>
#include <climits>
#include <iostream>

#include "Span.hpp"

Span::Span(void) {}

Span::Span(unsigned int n) : _n(n), _v(std::vector<int>()) {}

Span::Span(const Span& src) : _n(src._n), _v(src._v) {}

Span::~Span(void) {}

Span&	Span::operator=(const Span& src) {
	if (this != &src) {
		this->_n = src._n;
		this->_v = src._v;
	}
	return (*this);
}

const int&	Span::operator[](unsigned int i) const {
	return (this->_v.at(i));
}

void	Span::addNumber(const int toAdd) {
	if (_v.size() == this->_n) {
		throw std::length_error("Attempting to add number to full container");
	}
	this->_v.push_back(toAdd);
}

void	Span::addNumbers(std::vector<int>::const_iterator begin, std::vector<int>::const_iterator last) {

	size_t distance = std::distance(begin, last);

	if (_v.size() + distance > _n) {
		throw std::length_error("Attempting to add number to full container");
	}

	this->_v.insert(_v.end(), begin, last);
}

// O(n*log(n)) complexity
long	Span::shortestSpan(void) const {

	if (this->_v.size() <= 1) {
		throw std::length_error("Not enough numbers stored, no span can be found");
	}

	std::vector<int> sorted = this->_v;
	long minSpan = LONG_MAX;

	std::sort(sorted.begin(), sorted.end());

	for (size_t i = 1; i < sorted.size(); i++) {
		minSpan = std::min(minSpan, static_cast<long>(sorted[i] - sorted[i - 1]));
		if (minSpan == 0) {
			return (minSpan);
		}
	}

	return (minSpan);
}

// Could change const_iterator for iterator if we also remove const in the function prototype
// O(n) complexity
long	Span::longestSpan(void) const {

	if (this->_v.size() <= 1) {
		throw std::length_error("Not enough numbers stored, no span can be found");
	}

	std::vector<int>::const_iterator min_it = std::min_element(_v.begin(), _v.end());
	std::vector<int>::const_iterator max_it = std::max_element(_v.begin(), _v.end());
	long span = *max_it - *min_it;
	return (span);
}

void	Span::print(void) const {

	for (std::vector<int>::const_iterator it = _v.begin(); it !=  _v.end(); it++) {
		std::cout << *it << std::endl;
	}
}
