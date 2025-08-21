#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <ostream>
# include <stdexcept>

# include "colors.h"

template <typename T>
class Array {

	private:
		size_t	_size;
		T*		_array;

	public:

		Array(void) :_size(0), _array(0) {}

		Array(const unsigned int& n) : _size(n), _array(new T[n]()) {}

		~Array(void) {
			delete [] _array;
		}

		Array(const Array& src) : _size(src._size), _array(new T[src._size]) {
			for (size_t i = 0; i < _size; i++) {
				_array[i] = src._array[i];
			}
		}

		Array&	operator=(const Array& src) {
			if (this != &src) {
				delete [] this->_array;
				this->_size = src._size;
				this->_array = new T[_size];
				for (size_t i = 0; i < this->_size; i++) {
					_array[i] = src._array[i];
				}
			}
			return (*this);
		}

		T& operator[](size_t index) {
			if (index >= _size) {
				throw std::out_of_range("Index out of the array range");
			}
			return (_array[index]);
		}

		const T& operator[](size_t index) const {
			if (index >= _size) {
				throw std::out_of_range("Index out of the array range");
			}
			return (_array[index]);
		}

		size_t	size(void) const {
			return (_size);
		}
};

#endif
