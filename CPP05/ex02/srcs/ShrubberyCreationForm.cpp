#include <fstream>

#include "colors.h"
#include "ShrubberyCreationForm.hpp"


ShrubberyCreationForm::ShrubberyCreationForm(void) : AForm("Default ShrubberyForm", ShrubberyCreationForm::SIGN_GRADE, ShrubberyCreationForm::EXEC_GRADE), _target("Default Target") {
	std::cout << YELLOW "ShrubberyCreationForm (" << this->getName() << ") default constructor called" RESET << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target) :  AForm("ShrubberyCreationForm", ShrubberyCreationForm::SIGN_GRADE, ShrubberyCreationForm::EXEC_GRADE), _target(target) {
	std::cout << YELLOW "ShrubberyCreationForm (" << this->getName() << ") parametric constructor called" RESET << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& src) : AForm(src), _target(src._target) {
	std::cout << YELLOW "ShrubberyCreationForm (" << this->getName() << ") constructor by copy called" RESET << std::endl;
}

ShrubberyCreationForm::~ShrubberyCreationForm(void) {
	std::cout << "ShrubberyCreationForm (" << this->getName() <<  ")" << RED " destructor" RESET << " called" << std::endl;
}

ShrubberyCreationForm&	ShrubberyCreationForm::operator=(const ShrubberyCreationForm& src) {

	if (this != &src) {
		AForm::operator=(src);
		_target = src._target;
	}

	std::cout << BLUE "Assignment operator = called on " << this->getName() << RESET << std::endl;
	return (*this);
}

void	ShrubberyCreationForm::executeForm(void) const {

	std::string		outfileName = this->getTarget() + "_shrubbery";
	std::ofstream	outFile(outfileName.c_str());

	if (!outFile.is_open()) {
		throw ShrubberyCreationForm::OpeningOutStreamFailException();
	}

	outFile << "                       #%" << std::endl
			<< "                      @#%#" << std::endl
			<< "                     &@#%##" << std::endl
			<< "                    &#%&@#$%" << std::endl
			<< "                   &&@#%&&#$%" << std::endl
			<< "                  &%&@#%&@&@#$" << std::endl
			<< "                 &&@#%lou%@#%&#" << std::endl
			<< "                #@#%&@anne&%#@&#" << std::endl
			<< "               &#%@&&#%@&@#%la@#@" << std::endl
			<< "              @#%&@%&#@%best&@@#%@" << std::endl
			<< "             &#%@&@#%&@%#&@%#&@#%&@" << std::endl
			<< "            @#%&@&#%@&@#%@&@#%@#%&&@" << std::endl
			<< "           &#%@&@#pierrick&#%@@#%&@&@" << std::endl
			<< "          @#%&@&#%%@&@#%&@#%@#la%&$@$@" << std::endl
			<< "         &#%@&@#%@&@#%@fraude&@#%&@@#&@" << std::endl
			<< "        @#%&@&#%@&@#%@&@#%&@#%@#%&@@#%&@" << std::endl
			<< "       &#%@&@#%&@%#&@%#&@%#&@%@#%&@@#%&%@" << std::endl
			<< "      @#%&@&#%@&@#%@&@#%&@#%&@@#%&@@#%&&%@" << std::endl
			<< "     &#%@&@#%&@%#&@%#&@%#&@%#&@#%&@@#%&@$^&" << std::endl
			<< "    @#%&@&#%@&@#%@&@#%&@#%&@#%@#%&@@#%&%^&&@" << std::endl
			<< "   &#%@&@#%&@%#&@%#&@%#&@%#&@%@#%&@@#%&@%&%&@" << std::endl
			<< "  @#%&@&#%@&@#%@&@#%&@#%&@#%&@@#%&@@#%&@%&$^&@" << std::endl
			<< " &#%@&@#%&@%#&@%#&@%#&@%#&@%#&@#%&@@#%&@%&@&$%@" << std::endl
			<< "@#%&@&#%@&@#%@&@#%&@#%&@#%&@#%@#%&@@#%&@%&@%&&%@" << std::endl
			<< "                     |||||||" << std::endl
			<< "                     |||||||" << std::endl
			<< "                     |||||||" << std::endl
			<< "                     |||||||" << std::endl
			<< "                     |||||||" << std::endl
			<< "                     |||||||" << std::endl
			<< "                  ~~/|||||||\\~~" << std::endl
			<< "                 ~~//|||||||\\\\~~" << std::endl
			<< "               ~~~///|||||||\\\\~~~" << std::endl;

	if (outFile.fail()) {
		throw ShrubberyCreationForm::OpeningOutStreamFailException();
	}
	outFile.close();
}

std::string	ShrubberyCreationForm::getTarget(void) const {
	return (this->_target);
}

const char* ShrubberyCreationForm::OpeningOutStreamFailException::what(void) const throw() {
	return (RED "File handling failed" RESET);
}
