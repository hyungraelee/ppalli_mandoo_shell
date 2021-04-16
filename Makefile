NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS_DIR = ./srcs
OBJS_DIR = ./objs
INC_DIR = ./include
SRCS = $(wildcard $(SRCS_DIR)/*.c)

RM = rm -f

all: $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^

$(OBJS_DIR)/%.o : %.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -o $@ -I$(INC_DIR) -c $^

$(OBJS_DIR) :
	@mkdir -p $(OBJS_DIR)

clean :
	@$(RM) -r $(OBJS_DIR)

fclean : clean
	@$(RM) $(NAME)

re : fclean all
