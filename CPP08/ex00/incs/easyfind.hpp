#ifndef EASYFIND_HPP
# define EASYFIND_HPP

#include <algorithm>

/* Choose not to throw an exception here to mimic the stdlib common behavior.
   Would have thrown one if we expected the element searched to always be found */

template<typename T>
typename	T::const_iterator easyfind(const T& container, int searched) {
	return (std::find(container.begin(), container.end(), searched));
}

template<typename T>
typename	T::iterator easyfind(T& container, int searched) {
	return (std::find(container.begin(), container.end(), searched));
}

#endif
