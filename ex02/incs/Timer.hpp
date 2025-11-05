#ifndef TIMER_HPP
# define TIMER_HPP

# include <sys/time.h>
# include <iostream>
# include <iomanip>

class Timer {

	private:
		struct	timeval _start;
		struct	timeval _end;
		bool	_running;

		Timer(const Timer&);

		Timer&	operator=(const Timer&);

	public:
		Timer(void);
		~Timer(void);

		void	start();
		void	stop();

		double	getElapsedMicroseconds(void) const;
		double	getElapsedMilliseconds(void) const;
};

#endif
