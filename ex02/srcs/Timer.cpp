#include "Timer.hpp"

Timer::Timer(void) : _start(), _end(), _running(false) {}

Timer::Timer(const Timer&) {}

Timer&Timer::operator=(const Timer&) { return (*this); }

Timer::~Timer(void) {}


void	Timer::start(void) {

	gettimeofday(&_start, NULL);
	_running = true;
}

void	Timer::stop(void) {

	gettimeofday(&_end, NULL);
	_running = false;
}

double	Timer::getElapsedMicroseconds(void) const {

	if (_running)
		return (-1);
	return ((_end.tv_sec - _start.tv_sec) * 1000000 + (_end.tv_usec - _start.tv_usec));
}

double	Timer::getElapsedMilliseconds(void) const {

	return (getElapsedMicroseconds() / 1000);
}
