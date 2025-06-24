#ifndef FIXED_HPP
# define FIXED_HPP

# define BLUE		"\001\033[1;34m\002"
# define CYAN		"\001\033[1;36m\002"
# define GREEN		"\001\033[1;32m\002"
# define RED		"\001\033[0;31m\002"

# define RESET      "\001\033[0m\002"

class	Fixed
{
	private:
		static const int	_fractionalBits;
		int					_fixedPointValue;

		public:
			Fixed(void);
			Fixed(const Fixed& classCopyName);
			Fixed(const int number);
			Fixed(const float number);

			~Fixed(void);

			Fixed& operator=(const Fixed& classCopyName);

			bool	operator>(const Fixed& className) const;
			bool	operator<(const Fixed& className) const;
			bool	operator>=(const Fixed& className) const;
			bool	operator<=(const Fixed& className) const;
			bool	operator==(const Fixed& className) const;
			bool	operator!=(const Fixed& className) const;

			Fixed		operator+(const Fixed& className) const;
			Fixed		operator-(const Fixed& className) const;
			Fixed		operator*(const Fixed& className) const;
			Fixed		operator/(const Fixed& className) const;

			Fixed&		operator++(void);
			Fixed&		operator--(void);
			Fixed		operator++(int);
			Fixed		operator--(int);

			static Fixed& min(Fixed& className1, Fixed& className2);
			static const Fixed& min(const Fixed& className1, const Fixed& className2);
			static Fixed& max(Fixed& className1, Fixed& className2);
			static const Fixed& max(const Fixed& className1, const Fixed& className2);

			int		getRawBits(void) const;
			void	setRawBits(int const raw);

			float	toFloat(void) const;
			int		toInt(void) const;
};

#endif
