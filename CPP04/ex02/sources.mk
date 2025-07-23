override SRCSDIR	:= srcs/
override SRCS		= $(addprefix $(SRCSDIR), $(SRC))

SRC	+= $(addsuffix .cpp, $(MAIN))

override MAIN			:= \
	Animal \
	Brain \
	Cat \
	Dog \
	main \
	WrongAnimal \
	WrongCat \
