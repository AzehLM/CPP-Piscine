#ifndef FIXED_HPP
# define FIXED_HPP


class	Fixed
{
	private:
		static const int	_fractionalBits;
		int					_fixedPointValue;

		public:
			Fixed(void);
			~Fixed(void);

			// Fixed(Fixed); // Copy constructor
			// copy assignment operator overload (syntax ?)

			int		getRawBits(void) const;
			void	setRawBits(int const raw);
};


#endif
