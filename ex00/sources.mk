# override SRCSDIR	:= srcs/
# override SRCS		:= $(addprefix $(SRCSDIR), $(SRC))

# SRC		+= $(addsuffix .cpp, $(MAIN))

# override MAIN		:= \
# 	main \


SRCSDIR	:= srcs/

MAIN	:= \
	main \
	Fixed \

SRCS	:= $(addprefix $(SRCSDIR), $(addsuffix .cpp, $(MAIN)))
