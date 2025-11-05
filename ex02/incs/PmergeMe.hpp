#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>

# include "Timer.hpp"

class PmergeMe {

	private:

		Timer	_vecTimer;
		Timer	_deqTimer;

		std::vector<int>	_vec;
		std::deque<int>		_deq;

		PmergeMe();
		PmergeMe(const PmergeMe&);
		PmergeMe&	operator=(const PmergeMe&);

		std::vector<int>	parameterValidator(int ac, char **av);

		// Vector methods

		void	printUnsorted(void) const;
		void	printSorted(void) const;
		void	printTimer(void) const;

		void	sortVector(void);

		std::vector<std::vector<int> >	pairingVector(std::vector<std::vector<int> > elements, int depth);

		void		sortPairsVector(std::vector<int>& first, std::vector<int>& second, int depth);

		int			getLargestVector(const std::vector<int>& group);

		std::vector<size_t>	JacobsthalSequenceVector(size_t maxSize);
		std::vector<size_t>	JacobsthalInsertionOrderVector(size_t pendingSize);

		void	pendingInsertionVector(std::vector<std::vector<int> >& main, const std::vector<int>& toInsert, size_t maxRange);

		// decided not to duplicate because demonstration on vector is enough + I did build and debug only using vectors functions
		void		printGroup(const std::vector<int>& group) const;
		void		printGroups(const std::vector<std::vector<int> >& groups) const;


		// Deque methods

		void	sortDeque(void);

		std::deque<std::deque<int> >	pairingDeque(std::deque<std::deque<int> > elements, int depth);

		void		sortPairsDeque(std::deque<int>& first, std::deque<int>& second, int depth);

		int			getLargestDeque(const std::deque<int>& group);

		std::deque<size_t>	JacobsthalSequenceDeque(size_t maxSize);
		std::deque<size_t>	JacobsthalInsertionOrderDeque(size_t pendingSize);

		void	pendingInsertionDeque(std::deque<std::deque<int> >& main, const std::deque<int>& toInsert, size_t maxRange);

	public:
		PmergeMe(int ac, char **av);

		~PmergeMe(void);

		void	sort(void);
};

#endif
