#ifndef POINT_HPP
# define POINT_HPP

# include "Fixed.hpp"

class	Point
{
	private:
		const Fixed _x;
		const Fixed _y;

	public:
		Point(void);
		Point(const Point& copy);
		Point(const float f1, const float f2);

		~Point(void);

		Point&	operator=(const Point& copy);

		// setter -> getter ?

};


# endif
