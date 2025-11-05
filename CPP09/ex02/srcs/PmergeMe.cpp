#include <algorithm>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>

#include "colors.h"
#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _vecTimer(), _deqTimer(), _vec(), _deq() {}

PmergeMe::PmergeMe(const PmergeMe&) {}

PmergeMe&	PmergeMe::operator=(const PmergeMe&) { return (*this); }

PmergeMe::~PmergeMe(void) {}

PmergeMe::PmergeMe(int ac, char **av) : _vecTimer(), _deqTimer() {

	try {

		_vec = parameterValidator(ac, av);
		_deq.assign(_vec.begin(), _vec.end());

	} catch(const std::exception& e) {
		throw;
	}
}


/********************** UTILS **********************/


std::vector<int>	PmergeMe::parameterValidator(int ac, char **av) {

	std::vector<int> args;
	args.reserve(ac - 1);

	for (int i = 1; i < ac; ++i) {

		std::istringstream	iss(av[i]);
		int					value;
		char				leftover;

		if (!(iss >> value) || (iss >> leftover) || value <= 0) {
			throw std::invalid_argument("Error: '" + std::string(av[i]) + "' is not a valid positive integer");
		}

		args.push_back(value);
	}

	return (args);

}


/********************** PRINT_UTILS **********************/


void	PmergeMe::printUnsorted(void) const {

	std::cout << RED "Unsorted:" RESET;

	for (std::vector<int>::const_iterator it = _vec.begin(); it != _vec.end(); it++) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
}

void	PmergeMe::printSorted(void) const {

	std::cout << GREEN "Sorted:" RESET;

	for (std::vector<int>::const_iterator it = _vec.begin(); it != _vec.end(); it++) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
}

void	PmergeMe::printTimer(void) const {
	std::cout << "Time to process a range of " << _vec.size()
			  << " elements with std::vector : " GREEN
			  << std::fixed << std::setprecision(2)
			  << _vecTimer.getElapsedMilliseconds() << " ms" RESET
			  << std::endl;

	std::cout << "Time to process a range of " << _deq.size()
			  << " elements with std::deque : " GREEN
			  << std::fixed << std::setprecision(2)
			  << _deqTimer.getElapsedMilliseconds() << " ms" RESET
			  << std::endl;
}

void	PmergeMe::printGroup(const std::vector<int>& group) const {

	std::cout << "[";
	for (size_t i = 0; i < group.size(); i++) {
		std::cout << group[i];
		if (i + 1 < group.size())
			std::cout << ",";
	}
	std::cout << "]";
}

void	PmergeMe::printGroups(const std::vector<std::vector<int> >& groups) const {

	for (size_t i = 0; i < groups.size(); i++) {
		printGroup(groups[i]);
		if (i + 1 < groups.size())
			std::cout << " ";
	}
	std::cout << std::endl;
}


/********************** main function **********************/


void	PmergeMe::sort(void) {

	printUnsorted();

	_vecTimer.start();
	sortVector();
	_vecTimer.stop();

	_deqTimer.start();
	sortDeque();
	_deqTimer.stop();

	printSorted();
	printTimer();
}




/********************** VECTOR **********************/




void	PmergeMe::sortVector(void) {

	std::vector<std::vector<int> >	groups;

	for (size_t i = 0; i < _vec.size(); i++) {
		std::vector<int> g;
		g.push_back(_vec[i]);
		groups.push_back(g);
	}

	std::vector<std::vector<int> >	sorted = pairingVector(groups, 0);

	_vec.clear();
	for (size_t i = 0; i < sorted.size(); i++) {
		for (size_t j = 0; j < sorted[i].size(); j++) {
			_vec.push_back(sorted[i][j]);
		}
	}
}

std::vector<std::vector<int> > PmergeMe::pairingVector(std::vector<std::vector<int> > elements, int depth) {

	// Phase 1: Pre-sort by pairs (pairs or pairs, etc)
	if (elements.size() <= 1) {
		return (elements);
	}

	std::vector<std::vector<int> >	paired;
	std::vector<int>				leftover;
	bool							hasLeftover = false;
	size_t							elementsSize = elements.size();

	for (size_t i = 0; i + 1 < elementsSize; i += 2) {
		std::vector<int>	first = elements[i];
		std::vector<int>	second = elements[i + 1];

		sortPairsVector(first, second, depth);

		std::vector<int>	merged;
		merged.insert(merged.end(), first.begin(), first.end());
		merged.insert(merged.end(), second.begin(), second.end());
		paired.push_back(merged);
	}

	if (elementsSize % 2 != 0) {
		leftover = elements.back();
		hasLeftover = true;
	}

	std::vector<std::vector<int> > sorted = pairingVector(paired, depth + 1);

	// End of recursive

	if (sorted.empty()) {
		return (sorted);
	}

	// Phase 2: Create main and pend groups to prepare insertion
	size_t groupSize = sorted[0].size();
	size_t halfSize = groupSize / 2;

	std::vector<std::vector<int> > main;
	std::vector<std::vector<int> > pending;

	for (size_t i = 0; i < sorted.size(); i++) {
		std::vector<int>& group = sorted[i];

		if (group.size() == groupSize) {
			std::vector<int> smaller(group.begin(), group.begin() + halfSize);
			std::vector<int> larger(group.begin() + halfSize, group.end());

			if (i == 0) {
				main.push_back(smaller);
				main.push_back(larger);
			} else {
				pending.push_back(smaller);
				main.push_back(larger);
			}
		} else {
			main.push_back(group);
		}
	}

	// std::cout << YELLOW "depth: " << depth << RESET << std::endl;
	// std::cout << BLUE "Main chain:\t" RESET;
	// printGroups(main);
	// std::cout << BLUE "Pending:\t" RESET;
	// printGroups(pending);

	// Phase 3: Binary insertion with Jacobsthal sequence
	if (pending.size() >= 1) {
		std::vector<size_t> insertionOrder = JacobsthalInsertionOrderVector(pending.size());

		for (size_t i = 0; i < insertionOrder.size(); i++) {
			size_t pendingIdx = insertionOrder[i];

			size_t numInserted = i + 1;
			size_t maxSearchRange = pendingIdx + 1 + numInserted;

			pendingInsertionVector(main, pending[pendingIdx], maxSearchRange);
		}
	}

	if (hasLeftover) {
		pendingInsertionVector(main, leftover, main.size());
	}

	return (main);
}

/**
 * @brief Compares and sorts two groups (pairs) based on their largest elements.
 *
 * @param depth When @p depth is 0, the function gets the largest elements explicitly using @c getLargest() to ensure
 *        correct initial ordering. For deeper recursive calls, the function assumes
 *        that the groups are already partially sorted and simply compares their
 *        back elements (the last ones), reducing redundant maximum checks.
 *
 * @note This optimization minimizes calls to @c getLargest(), which can be
 *       expensive in recursion. Improvements possible: I could have changed the whole
 *       logic by making the first value of the elements being the largest to use
 *       @c first.front(), but I didn't bother change the whole logic of the other functions, would be too much.
 */
void		PmergeMe::sortPairsVector(std::vector<int>& first, std::vector<int>& second, int depth) {

	int	largest1, largest2;

	if (depth == 0) {
		largest1 = getLargestVector(first);
		largest2 = getLargestVector(second);
	} else {
		largest1 = first.empty() ? -1 : first.back();
		largest2 = second.empty() ? -1 : second.back();
	}

	if (largest1 > largest2) {
		std::swap(first, second);
	}
}

int	PmergeMe::getLargestVector(const std::vector<int>& group) {
	if (group.empty())
		return (-1);
	return (*std::max_element(group.begin(), group.end()));
}

/**
 * @brief Generates the Jacobsthal sequence up to a given maximum size.
 * @return A vector containing all Jacobsthal numbers up to @p maxSize
 */
std::vector<size_t>	PmergeMe::JacobsthalSequenceVector(size_t maxSize) {

	std::vector<size_t>	jacobsthal;
	jacobsthal.push_back(0);
	jacobsthal.push_back(1);

	while (jacobsthal.back() < maxSize) {
		size_t	next = jacobsthal[jacobsthal.size() - 1] + 2 * jacobsthal[jacobsthal.size() - 2];
		jacobsthal.push_back(next);
	}

	return (jacobsthal);
}

/**
 * @brief Determines the insertion order of pending elements based on the Jacobsthal sequence.
 * @return A vector containing the indices in the order they will be inserted.
 */
std::vector<size_t>	PmergeMe::JacobsthalInsertionOrderVector(size_t pendingSize) {

	if (pendingSize == 0) {
		return (std::vector<size_t>());
	}

	std::vector<size_t>	jacobsthal = JacobsthalSequenceVector(pendingSize);
	std::vector<size_t>	insertionOrder;
	std::vector<bool>	used(pendingSize, false);

	for (size_t i = 3; i < jacobsthal.size() && jacobsthal[i] <= pendingSize; ++i) {

		size_t j_curr = jacobsthal[i];
		size_t j_prev = jacobsthal[i - 1];

		for (size_t j = j_curr; (j > j_prev) && (j <= pendingSize); --j) {

			size_t actualIndex = j - 1;

			if (!used[actualIndex]) {
				insertionOrder.push_back(actualIndex);
				used[actualIndex] = true;
			}
		}
	}

	for (size_t i = 0; i < pendingSize; ++i) {
		if (!used[i]) {
			insertionOrder.push_back(i);
		}
	}

	return (insertionOrder);
}

/**
 * @brief Performs the binary insertion of the pending elements into the main container.
 */
void PmergeMe::pendingInsertionVector(std::vector<std::vector<int> >& main, const std::vector<int>& toInsert, size_t maxSearchRange)
{
	if (toInsert.empty()) {
		return ;
	}

	size_t searchEnd = std::min(maxSearchRange, main.size());

	int targetMax = getLargestVector(toInsert);

	size_t low = 0;
	size_t high = searchEnd;

	while (low < high) {
		size_t mid = low + (high - low) / 2;
		if (getLargestVector(main[mid]) < targetMax) {
			low = mid + 1;
		} else {
			high = mid;
		}
	}

	main.insert(main.begin() + low, toInsert);
}













/********************** DEQUE **********************/



/**
 * Those are the exact same functions (and logic) as vector, since both containers behaves the same
 * I only had to copy/paste the functions and changes the names/types
 * I also removed the comments to understand a bit further what was happening with vectors so I recommand going back above
 */




void	PmergeMe::sortDeque(void) {

	std::deque<std::deque<int> >	groups;

	for (size_t i = 0; i < _deq.size(); i++) {
		std::deque<int> g;
		g.push_back(_deq[i]);
		groups.push_back(g);
	}

	std::deque<std::deque<int> >	sorted = pairingDeque(groups, 0);

	_deq.clear();
	for (size_t i = 0; i < sorted.size(); i++) {
		for (size_t j = 0; j < sorted[i].size(); j++) {
			_deq.push_back(sorted[i][j]);
		}
	}
}


std::deque<std::deque<int> > PmergeMe::pairingDeque(std::deque<std::deque<int> > elements, int depth) {

	if (elements.size() <= 1) {
		return (elements);
	}

	std::deque<std::deque<int> >	paired;
	std::deque<int>					leftover;
	bool							hasLeftover = false;
	size_t							elementsSize = elements.size();

	for (size_t i = 0; i + 1 < elementsSize; i += 2) {
		std::deque<int>	first = elements[i];
		std::deque<int>	second = elements[i + 1];

		sortPairsDeque(first, second, depth);

		std::deque<int>	merged;
		merged.insert(merged.end(), first.begin(), first.end());
		merged.insert(merged.end(), second.begin(), second.end());
		paired.push_back(merged);
	}

	if (elementsSize % 2 != 0) {
		leftover = elements.back();
		hasLeftover = true;
	}

	std::deque<std::deque<int> > sorted = pairingDeque(paired, depth + 1);

	if (sorted.empty()) {
		return (sorted);
	}

	size_t groupSize = sorted[0].size();
	size_t halfSize = groupSize / 2;

	std::deque<std::deque<int> > main;
	std::deque<std::deque<int> > pending;

	for (size_t i = 0; i < sorted.size(); i++) {
		std::deque<int>& group = sorted[i];

		if (group.size() == groupSize) {
			std::deque<int> smaller(group.begin(), group.begin() + halfSize);
			std::deque<int> larger(group.begin() + halfSize, group.end());

			if (i == 0) {
				main.push_back(smaller);
				main.push_back(larger);
			} else {
				pending.push_back(smaller);
				main.push_back(larger);
			}
		} else {
			main.push_back(group);
		}
	}

	if (pending.size() >= 1) {
		std::deque<size_t> insertionOrder = JacobsthalInsertionOrderDeque(pending.size());

		for (size_t i = 0; i < insertionOrder.size(); i++) {
			size_t pendingIdx = insertionOrder[i];

			size_t numInserted = i + 1;
			size_t maxSearchRange = pendingIdx + 1 + numInserted;

			pendingInsertionDeque(main, pending[pendingIdx], maxSearchRange);
		}
	}

	if (hasLeftover) {
		pendingInsertionDeque(main, leftover, main.size());
	}

	return (main);
}

void		PmergeMe::sortPairsDeque(std::deque<int>& first, std::deque<int>& second, int depth) {

	int	largest1, largest2;

	if (depth == 0) {
		largest1 = getLargestDeque(first);
		largest2 = getLargestDeque(second);
	} else {
		largest1 = first.empty() ? -1 : first.back();
		largest2 = second.empty() ? -1 : second.back();
	}

	if (largest1 > largest2) {
		std::swap(first, second);
	}
}

int	PmergeMe::getLargestDeque(const std::deque<int>& group) {
	if (group.empty())
		return (-1);
	return (*std::max_element(group.begin(), group.end()));
}


std::deque<size_t>	PmergeMe::JacobsthalSequenceDeque(size_t maxSize) {

	std::deque<size_t>	jacobsthal;
	jacobsthal.push_back(0);
	jacobsthal.push_back(1);

	while (jacobsthal.back() < maxSize) {
		size_t	next = jacobsthal[jacobsthal.size() - 1] + 2 * jacobsthal[jacobsthal.size() - 2];
		jacobsthal.push_back(next);
	}

	return (jacobsthal);
}

std::deque<size_t>	PmergeMe::JacobsthalInsertionOrderDeque(size_t pendingSize) {

	if (pendingSize == 0) {
		return (std::deque<size_t>());
	}

	std::deque<size_t>	jacobsthal = JacobsthalSequenceDeque(pendingSize);
	std::deque<size_t>	insertionOrder;
	std::deque<bool>	used(pendingSize, false);

	for (size_t i = 3; i < jacobsthal.size() && jacobsthal[i] <= pendingSize; ++i) {

		size_t j_curr = jacobsthal[i];
		size_t j_prev = jacobsthal[i - 1];

		for (size_t j = j_curr; (j > j_prev) && (j <= pendingSize); --j) {

			size_t actualIndex = j - 1;

			if (!used[actualIndex]) {
				insertionOrder.push_back(actualIndex);
				used[actualIndex] = true;
			}
		}
	}

	for (size_t i = 0; i < pendingSize; ++i) {
		if (!used[i]) {
			insertionOrder.push_back(i);
		}
	}

	return (insertionOrder);
}

void PmergeMe::pendingInsertionDeque(std::deque<std::deque<int> >& main, const std::deque<int>& toInsert, size_t maxSearchRange)
{
	if (toInsert.empty()) {
		return ;
	}

	size_t searchEnd = std::min(maxSearchRange, main.size());

	int targetMax = getLargestDeque(toInsert);

	size_t low = 0;
	size_t high = searchEnd;

	while (low < high) {
		size_t mid = low + (high - low) / 2;
		if (getLargestDeque(main[mid]) < targetMax) {
			low = mid + 1;
		} else {
			high = mid;
		}
	}

	main.insert(main.begin() + low, toInsert);
}
