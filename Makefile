NAME = minishell
CC = gcc
# CFLAGS = -Wall -Wextra -Werror
CFLAGS = -g3 -fsanitize=address
SRCS_DIR =	./srcs	\
			./srcs/utils

OBJS_DIR = ./objs
INC_DIR = ./includes

SRCS =	./srcs/main.c	\
		./srcs/check_syntax_err.c		\
		./srcs/parse.c		\
		./srcs/read_cmd.c	\
		./srcs/run.c	\
		./srcs/separate.c	\
		./srcs/tokenizer.c	\
		./srcs/utils/ft_str_char_join.c	\
		./srcs/utils/ft_isalnum.c	\
		./srcs/utils/ft_isalpha.c	\
		./srcs/utils/ft_isdigit.c	\
		./srcs/utils/ft_isprint.c	\
		./srcs/utils/ft_memmove.c	\
		./srcs/utils/ft_str_char_join.c	\
		./srcs/utils/ft_strchr.c	\
		./srcs/utils/ft_strdup.c	\
		./srcs/utils/ft_strlen.c	\
		./srcs/utils/ft_strtrim.c	\
		./srcs/utils/ft_substr.c	\

OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))
vpath %.c $(SRCS_DIR)

RM = rm -f

all: $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^

$(OBJS_DIR) :
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o : %.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -o $@ -I$(INC_DIR) -c $^

run: re
	@./$(NAME)

clean :
	@$(RM) -r $(OBJS_DIR)

fclean : clean
	@$(RM) $(NAME)

re : fclean all
