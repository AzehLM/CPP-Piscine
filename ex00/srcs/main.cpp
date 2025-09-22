#include <deque>
#include <iostream>
#include <list>
#include <vector>

#include "colors.h"
#include "easyfind.hpp"

int	main(void)
{
	{
		std::cout << CYAN "\tTest with vector" RESET << std::endl;

		std::vector<int> v;
		for (int i = 0; i < 6; i++) {
			v.push_back(i);
		}

		for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); it++) {
			std::cout << *it << std::endl;
		}

		// change value to test;
		int searched = 156;

		std::cout << "Searched value: " BLUE << searched << RESET << std::endl;
		std::vector<int>::const_iterator it = easyfind(v, searched);

		// Printing *it after calling easyfind result in conditional jumps.
		// The find function returns a pointer to container.end()
		// which is a special "past-the-end" iterator that marks the boundary of the container
		// This is an undefined behavior.
		if (it == v.end()) {
			std::cout << RED "Value Not found" RESET << std::endl;
			// std::cout << RED "Last element of the vector:	" << *(it - 1) << RESET << std::endl;
			// std::cout << RED "*it value (equals to v.end()):	" << *it << RESET << std::endl;
		} else {
			std::cout << GREEN "Value found: " << *it << RESET << std::endl;
		}

		searched = v.size() - 1;
		std::cout << "Searched value: " BLUE << searched << RESET << std::endl;
		it = easyfind(v, searched);

		if (it == v.end()) {
			std::cout << RED "Value Not found" RESET << std::endl;
		} else {
			std::cout << GREEN "Value found: " << *it << RESET << std::endl;
		}
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tTest with list" RESET << std::endl;

		std::list<int> list;
		for (int i = 0; i < 5; i ++) {
			list.push_back(i);
		}

		std::list<int>::iterator it = list.end();
		for (int i = 87; i < 92; i++) {
			list.insert(it, i);
		}
		for (std::list<int>::iterator test = list.begin(); test != list.end(); test++) {
			std::cout << *test << std::endl;
		}
		int searched = 90;

		std::cout << "Searched value: " BLUE << searched << RESET << std::endl;
		it = easyfind(list, searched);

		if (it == list.end()) {
			std::cout << RED "Value Not found" RESET << std::endl;
		} else {
			std::cout << GREEN "Value found: " << *it << RESET << std::endl;
		}
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tTest with empty vector" RESET << std::endl;

		std::vector<int> empty_v;
		int searched = 42;

		std::cout << "Searched value in empty container: " BLUE << searched << RESET << std::endl;
		std::vector<int>::const_iterator it = easyfind(empty_v, searched);

		if (it == empty_v.end()) {
			std::cout << GREEN "Correctly handled empty container (no value found)" RESET << std::endl;
		} else {
			std::cout << RED "Error: found value in empty container" RESET << std::endl;
		}
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tTest first and last elements" RESET << std::endl;

		std::vector<int> v;
		for (int i = 10; i <= 20; i++) {
			v.push_back(i);
		}

		int searched = 10;
		std::cout << "Searching first element: " BLUE << searched << RESET << std::endl;
		std::vector<int>::const_iterator it = easyfind(v, searched);

		if (it == v.end()) {
			std::cout << RED "First element not found" RESET << std::endl;
		} else {
			std::cout << GREEN "First element found: " << *it << RESET << std::endl;
		}

		searched = 20;
		std::cout << "Searching last element: " BLUE << searched << RESET << std::endl;
		it = easyfind(v, searched);

		if (it == v.end()) {
			std::cout << RED "Last element not found" RESET << std::endl;
		} else {
			std::cout << GREEN "Last element found: " << *it << RESET << std::endl;
		}
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tTest with duplicate elements" RESET << std::endl;

		std::list<int> list_dup;
		list_dup.push_back(1);
		list_dup.push_back(2);
		list_dup.push_back(2);
		list_dup.push_back(3);
		list_dup.push_back(2);

		std::cout << "List content: ";
		for (std::list<int>::iterator it = list_dup.begin(); it != list_dup.end(); it++) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		int searched = 2;
		std::cout << "Searching duplicate value: " BLUE << searched << RESET << std::endl;
		std::list<int>::iterator it = easyfind(list_dup, searched);

		if (it == list_dup.end()) {
			std::cout << RED "Duplicate value not found" RESET << std::endl;
		} else {
			std::cout << GREEN "First occurrence found: " << *it << RESET << std::endl;
		}
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tTest with negative values" RESET << std::endl;

		std::vector<int> v_neg;
		for (int i = -5; i <= 5; i++) {
			v_neg.push_back(i);
		}

		int searched = -3;
		std::cout << "Searching negative value: " BLUE << searched << RESET << std::endl;
		std::vector<int>::const_iterator it = easyfind(v_neg, searched);

		if (it == v_neg.end()) {
			std::cout << RED "Negative value not found" RESET << std::endl;
		} else {
			std::cout << GREEN "Negative value found: " << *it << RESET << std::endl;
		}
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tTest with deque" RESET << std::endl;

		std::deque<int> deq;
		for (int i = 0; i < 8; i++) {
			deq.push_back(i * 2);
		}

		std::cout << "Deque content: ";
		for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); it++) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		int searched = 6;
		std::cout << "Searching in deque: " BLUE << searched << RESET << std::endl;
		std::deque<int>::iterator it = easyfind(deq, searched);

		if (it == deq.end()) {
			std::cout << RED "Value not found in deque" RESET << std::endl;
		} else {
			std::cout << GREEN "Value found in deque: " << *it << RESET << std::endl;
		}
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tTest with single element container" RESET << std::endl;

		std::vector<int> single;
		single.push_back(42);

		int searched = 42;
		std::cout << "Searching existing single element: " BLUE << searched << RESET << std::endl;
		std::vector<int>::const_iterator it = easyfind(single, searched);

		if (it == single.end()) {
			std::cout << RED "Single element not found" RESET << std::endl;
		} else {
			std::cout << GREEN "Single element found: " << *it << RESET << std::endl;
		}

		searched = 24;
		std::cout << "Searching non-existing element: " BLUE << searched << RESET << std::endl;
		it = easyfind(single, searched);

		if (it == single.end()) {
			std::cout << GREEN "Correctly: element not found in single-element container" RESET << std::endl;
		} else {
			std::cout << RED "Error: found non-existing element" RESET << std::endl;
		}
	}
	return (0);
}
