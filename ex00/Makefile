NAME		:= fixed_point

include sources.mk

BUILD_DIR	:= .build/
OBJS 		:= $(patsubst $(SRCSDIR)%.cpp,$(BUILD_DIR)%.o,$(SRCS))
DEPS		:= $(OBJS:.o=.d)

# ********** FLAGS AND COMPILATION FLAGS ************************************* #

CXX			:= c++
CFLAGS		:= -Wall -Wextra -Werror -std=c++98
CPPFLAGS	:= -MMD -MP

RM			:= rm -f
RMDIR		:= rm -rf
MAKEFLAGS	+= --no-print-directory

.DEFAULT_GOAL	:= all

# ********** RULES *********************************************************** #

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "\n$(GREEN_BOLD)✓ $(NAME) is ready$(RESETC)"

$(BUILD_DIR)%.o: $(SRCSDIR)%.cpp
	@mkdir -p $(dir $@)
	@echo "$(CYAN)[Compiling]$(RESETC) $<"
	@$(CXX) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	@$(RM) $(OBJS) $(DEPS)
	@echo "$(RED_BOLD)[Cleaning]$(RESETC)"

.PHONY: fclean
fclean: clean
	@$(RM) $(NAME)
	@$(RMDIR) $(BUILD_DIR)
	@echo "$(RED_BOLD)✓ $(NAME) is fully cleaned!$(RESETC)"

.PHONY: re
re: fclean all

# ********** COLORS AND BACKGROUND COLORS ************************************ #

RESETC				:=	\033[0m
GREEN_BOLD			:= \033[1;32m
RED_BOLD			:= \033[1;31m
CYAN				:= \033[0;36m

-include $(DEPS)



