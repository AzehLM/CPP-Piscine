#include "Point.hpp"

Point::Point() : _x(0), _y(0) {}

Point::~Point() {}

Point::Point(const Point& copy) : _x(copy._x), _y(copy._y) {}

Point::Point(const float f1, const float f2) : _x(f1), _y(f2) {}

Point&	Point::operator=(const Point& copy)
{
	return (*this);
}
