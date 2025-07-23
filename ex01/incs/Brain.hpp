#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <string>

class Brain {
	private:
		std::string			_ideas[100];

	public:
		Brain(void);
		Brain(const Brain& copy);

		~Brain(void);

		Brain&	operator=(const Brain& src);

		std::string	getIdea(int index) const;
		void		setIdea(int index, std::string idea);
};

#endif
