override SRCSDIR	:= srcs/
override SRCS		= $(addprefix $(SRCSDIR), $(SRC))

SRC	+= $(addsuffix .cpp, $(MAIN))

override MAIN			:= \
	AMateria \
	Character \
	Cure \
	Ice \
	main \
	MateriaSource
