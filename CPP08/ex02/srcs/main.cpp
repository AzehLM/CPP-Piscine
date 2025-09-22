#include <cassert>
#include <iostream>
#include <exception>
#include <cstdlib>
#include <list>
#include <vector>
#include <deque>
#include <sstream>

#include "MutantStack.hpp"
#include "colors.h"

int main(void)
{
	{
		std::cout << CYAN "\tCanonical form tests - MutantStack" RESET << std::endl;

		MutantStack<int> mstack1;
		MutantStack<int> mstack2(mstack1);
		MutantStack<int> mstack3;

		mstack3 = mstack2;

		mstack1.push(42);
		mstack2.push(24);
		mstack3.push(84);

		assert(mstack1.size() == 1);
		assert(mstack2.size() == 1);
		assert(mstack3.size() == 1);

		assert(mstack1.top() == 42);
		assert(mstack2.top() == 24);
		assert(mstack3.top() == 84);

		std::cout << GREEN " ✓ MutantStack canonical forms work" RESET << std::endl;
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tBasic stack operations" RESET << std::endl;

		try {
			MutantStack<int> mstack;

			assert(mstack.empty() == true);
			assert(mstack.size() == 0);

			mstack.push(5);
			mstack.push(17);

			assert(mstack.empty() == false);
			assert(mstack.size() == 2);
			assert(mstack.top() == 17);

			mstack.pop();

			assert(mstack.size() == 1);
			assert(mstack.top() == 5);

			mstack.push(3);
			mstack.push(5);
			mstack.push(737);
			mstack.push(0);

			assert(mstack.size() == 5);
			assert(mstack.top() == 0);

			std::cout << GREEN " ✓ Basic stack operations work correctly" RESET << std::endl;
		}
		catch (const std::exception& e) {
			std::cout << RED "Unexpected exception: " << e.what() << RESET << std::endl;
			assert(false);
		}
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tIterator functionality" RESET << std::endl;

		try {
			MutantStack<int> mstack;
			mstack.push(5);
			mstack.push(17);
			mstack.pop();
			mstack.push(3);
			mstack.push(5);
			mstack.push(737);
			mstack.push(0);

			MutantStack<int>::iterator it = mstack.begin();
			MutantStack<int>::iterator ite = mstack.end();

			++it;
			--it;

			std::vector<int> values;
			while (it != ite) {
				values.push_back(*it);
				++it;
			}

			assert(values.size() == 5);
			assert(values[0] == 5);   // First pushed (bottom of stack)
			assert(values[1] == 3);
			assert(values[2] == 5);
			assert(values[3] == 737);
			assert(values[4] == 0);   // Last pushed (top of stack)

			std::cout << GREEN " ✓ Iterator functionality works correctly" RESET << std::endl;
		}
		catch (const std::exception& e) {
			std::cout << RED "Unexpected exception: " << e.what() << RESET << std::endl;
			assert(false);
		}
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tComparison with std::list (subject requirement)" RESET << std::endl;

		try {
			MutantStack<int> mstack;
			mstack.push(5);
			mstack.push(17);
			std::cout << "MutantStack top: " << mstack.top() << std::endl;
			mstack.pop();
			std::cout << "MutantStack size after pop: " << mstack.size() << std::endl;
			mstack.push(3);
			mstack.push(5);
			mstack.push(737);
			mstack.push(0);

			std::vector<int> mstack_values;
			MutantStack<int>::iterator it = mstack.begin();
			MutantStack<int>::iterator ite = mstack.end();
			++it;
			--it;
			while (it != ite) {
				mstack_values.push_back(*it);
				++it;
			}

			std::stack<int> s(mstack);
			assert(s.size() == mstack.size());

			std::list<int> lst;
			lst.push_back(5);
			lst.push_back(17);
			std::cout << "List back: " << lst.back() << std::endl;
			lst.pop_back();
			std::cout << "List size after pop: " << lst.size() << std::endl;
			lst.push_back(3);
			lst.push_back(5);
			lst.push_back(737);
			lst.push_back(0);

			std::vector<int> list_values;
			std::list<int>::iterator lit = lst.begin();
			std::list<int>::iterator lite = lst.end();
			++lit;
			--lit;
			while (lit != lite) {
				list_values.push_back(*lit);
				++lit;
			}

			std::list<int> lst2(lst);
			assert(lst2.size() == lst.size());

			assert(mstack_values.size() == list_values.size());
			for (size_t i = 0; i < mstack_values.size(); i++) {
				assert(mstack_values[i] == list_values[i]);
			}

			std::cout << GREEN " ✓ MutantStack and std::list produce identical output" RESET << std::endl;
		}
		catch (const std::exception& e) {
			std::cout << RED "Unexpected exception: " << e.what() << RESET << std::endl;
			assert(false);
		}
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tReverse iterator functionality" RESET << std::endl;

		try {
			MutantStack<int> mstack;
			mstack.push(1);
			mstack.push(2);
			mstack.push(3);
			mstack.push(4);

			std::vector<int> forward;
			for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it) {
				forward.push_back(*it);
			}

			std::vector<int> reverse;
			for (MutantStack<int>::reverse_iterator rit = mstack.rbegin(); rit != mstack.rend(); ++rit) {
				reverse.push_back(*rit);
			}

			assert(forward.size() == reverse.size());
			for (size_t i = 0; i < forward.size(); i++) {
				assert(forward[i] == reverse[reverse.size() - 1 - i]);
			}

			assert(forward[0] == 1 && reverse[0] == 4);
			assert(forward[3] == 4 && reverse[3] == 1);

			std::cout << GREEN " ✓ Reverse iterators work correctly" RESET << std::endl;
		}
		catch (const std::exception& e) {
			std::cout << RED "Unexpected exception: " << e.what() << RESET << std::endl;
			assert(false);
		}
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tDifferent underlying containers" RESET << std::endl;

		try {
			// vector
			MutantStack<int, std::vector<int> > vstack;
			vstack.push(10);
			vstack.push(20);
			vstack.push(30);

			std::vector<int> vvalues;
			for (MutantStack<int, std::vector<int> >::iterator it = vstack.begin();
				 it != vstack.end(); ++it) {
				vvalues.push_back(*it);
			}

			assert(vvalues.size() == 3);
			assert(vvalues[0] == 10 && vvalues[1] == 20 && vvalues[2] == 30);
			assert(vstack.top() == 30);

			// deque (default)
			MutantStack<int, std::deque<int> > dstack;
			dstack.push(100);
			dstack.push(200);

			std::vector<int> dvalues;
			for (MutantStack<int, std::deque<int> >::iterator it = dstack.begin();
				 it != dstack.end(); ++it) {
				dvalues.push_back(*it);
			}

			assert(dvalues.size() == 2);
			assert(dvalues[0] == 100 && dvalues[1] == 200);
			assert(dstack.top() == 200);

			std::cout << GREEN " ✓ Different underlying containers work correctly" RESET << std::endl;
		}
		catch (const std::exception& e) {
			std::cout << RED "Unexpected exception: " << e.what() << RESET << std::endl;
			assert(false);
		}
	}

	std::cout << std::endl;

	{
		std::cout << CYAN "\tconst_reverse_iterator" RESET << std::endl;
		try {
			MutantStack<int> mstack;
			mstack.push(10);
			mstack.push(20);
			mstack.push(30);
			std::vector<int> vvalues;
			for (MutantStack<int>::const_reverse_iterator rit = mstack.rbegin();
				rit != mstack.rend(); ++rit) {
				vvalues.push_back(*rit);
			}

			assert(vvalues.size() == 3);
			assert(vvalues[0] == 30 && vvalues[1] == 20 && vvalues[2] == 10);
			assert(mstack.top() == 30);
			std::cout << GREEN " ✓ Const Reverse iterators work correctly" RESET << std::endl;
		}
		catch (const std::exception& e) {
			std::cout << RED "Unexpected exception: " << e.what() << RESET << std::endl;
			assert(false);
		}
	}

	return (0);
}
