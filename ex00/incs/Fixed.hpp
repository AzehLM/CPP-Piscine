#ifndef FIXED_HPP
# define FIXED_HPP


class	Fixed
{
	private:
		static const int	_fractionalBits;
		int					_fixedPointValue;

		public:
			Fixed(void);
			Fixed(Fixed& classCopyName);
			~Fixed(void);

			Fixed& operator=(Fixed& classCopyName);

			int		getRawBits(void) const;
			void	setRawBits(int const raw);
};


#endif
