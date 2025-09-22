#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <deque>
# include <stack>

// default c type is a deque (underlying container) but it could be any Sequence Container
template<typename T, typename Container = std::deque<T> >
class MutantStack : public std::stack<T, Container> {

	private:

	public:
		typedef typename Container::iterator iterator;
		typedef typename Container::const_iterator const_iterator;
		typedef typename Container::reverse_iterator reverse_iterator;
		typedef typename Container::const_reverse_iterator const_reverse_iterator;

		MutantStack(void) : std::stack<T, Container>() {}

		MutantStack(const MutantStack& src) : std::stack<T, Container>(src) {}

		MutantStack&	operator=(const MutantStack& src) {
			if (this != &src) {
				std::stack<T, Container>::operator=(src);
			}
			return (*this);
		}

		~MutantStack(void) {}

		iterator begin() {
			return (this->c.begin());
		}

		iterator end() {
			return (this->c.end());
		}

		const_iterator begin() const {
			return (this->c.begin());
		}

		const_iterator end() const {
			return (this->c.end());
		}

		reverse_iterator rbegin() {
			return (this->c.rbegin());
		}

		reverse_iterator rend() {
			return (this->c.rend());
		}

		const_reverse_iterator rbegin() const {
			return (this->c.rbegin());
		}

		const_reverse_iterator rend() const {
			return (this->c.rend());
		}
};


#endif
