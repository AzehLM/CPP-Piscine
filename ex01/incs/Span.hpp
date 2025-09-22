#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>

class Span {

	private:
		unsigned int		_n;
		std::vector<int>	_v;
		Span(void);

	public:
		Span(const unsigned int n);
		Span(const Span& src);

		~Span(void);

		Span&	operator=(const Span& src);

		const int&	operator[](unsigned int i) const;

		void	addNumber(const int toAdd);
		void	addNumbers(std::vector<int>::const_iterator begin, std::vector<int>::const_iterator last);

		long	shortestSpan(void) const;
		long	longestSpan(void) const;

		void	print(void) const;
};

#endif
