override SRCSDIR	:= srcs/
override SRCS		= $(addprefix $(SRCSDIR), $(SRC))

SRC	+= $(addsuffix .cpp, $(MAIN))

override MAIN			:= \
	Animal \
	Cat \
	Dog \
	main \
	WrongAnimal \
	WrongCat \
