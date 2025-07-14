override SRCSDIR	:= srcs/
override SRCS		= $(addprefix $(SRCSDIR), $(SRC))

SRC	+= $(addsuffix .cpp, $(MAIN))

override MAIN			:= \
	ClapTrap \
	DiamondTrap \
	FragTrap \
	main \
	ScavTrap
