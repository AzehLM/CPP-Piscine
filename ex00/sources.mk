# override SRCSDIR	:= srcs/
# override SRCS		:= $(addprefix $(SRCSDIR), $(SRC))

# SRC		+= $(addsuffix .cpp, $(MAIN))

# override MAIN		:= \
# 	main \


SRCSDIR	:= srcs/

MAIN	:= main

SRCS	:= $(addprefix $(SRCSDIR), $(addsuffix .cpp, $(MAIN)))
