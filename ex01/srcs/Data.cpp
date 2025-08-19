#include "Data.hpp"

Data::Data(void) : _id(0), _name("default") {}

Data::Data(const Data& src) : _id(src._id), _name(src._name) {}

Data::Data(int id, const std::string& name) : _id(id), _name(name) {}

Data::~Data(void) {}

Data&	Data::operator=(const Data& src) {

	if (this != &src) {
		this->_id = src._id;
		this->_name = src._name;
	}
	return (*this);
}

int	Data::getId(void) const {
	return (this->_id);
}

std::string	Data::getName(void) const {
	return (this->_name);
}

std::ostream&	operator<<(std::ostream& o, const Data& d) {
	o << "Struct ID:	" << d.getId()<< std::endl;
	o << "Struct name:	" << d.getName();
	return (o);
}
