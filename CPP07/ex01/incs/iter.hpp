#ifndef ITER_HPP
# define ITER_HPP

#include <cstdlib>

template<typename T>
void	iter(T* ptr, size_t len, void (*f)(T&))
{
	for (size_t i = 0; i < len; i++) {
		f(ptr[i]);
	}
}

template<typename T>
void	iter(const T* ptr, size_t len, void (*f)(const T&)) {
    for (size_t i = 0; i < len; i++) {
        f(ptr[i]);
    }
}

#endif
