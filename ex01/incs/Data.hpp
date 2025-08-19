#ifndef DATA_HPP
# define DATA_HPP

# include <ostream>
# include <string>

class Data {

	private:
		int			_id;
		std::string _name;

	public:
		Data(void);
		Data(const Data& src);

		Data(int id, const std::string& name);

		~Data(void);

		Data&	operator=(const Data& src);

		int			getId(void) const;
		std::string	getName(void) const;
};

std::ostream&	operator<<(std::ostream& o, const Data& data);

#endif
