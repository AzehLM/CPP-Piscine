override SRCSDIR	:= srcs/
override SRCS		= $(addprefix $(SRCSDIR), $(SRC))

SRC	+= $(addsuffix .cpp, $(MAIN))

override MAIN			:= \
	AForm \
	Bureaucrat \
	main \
	PresidentialPardonForm \
	RobotomyRequestForm \
	ShrubberyCreationForm
