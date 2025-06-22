#ifndef FIXED_HPP
# define FIXED_HPP

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

			bool	operator>(const Fixed& classCopyName) const;
			bool	operator<(const Fixed& classCopyName) const;
			bool	operator>=(const Fixed& classCopyName) const;
			bool	operator<=(const Fixed& classCopyName) const;
			bool	operator==(const Fixed& classCopyName) const;
			bool	operator!=(const Fixed& classCopyName) const;


			int		getRawBits(void) const;
			void	setRawBits(int const raw);

			float	toFloat(void) const;
			int		toInt(void) const;
};

#endif
