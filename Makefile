NAME = minishell
CC = gcc
# CFLAGS = -Wall -Wextra -Werror
CFLAGS = -g3 -fsanitize=address
SRCS_DIR =	./srcs	\
			./srcs/blt_func	\
			./srcs/utils

OBJS_DIR = ./objs
INC_DIR = ./includes

SRCS =	./srcs/main.c	\
		./srcs/builtin.c	\
		./srcs/check_syntax_err.c		\
		./srcs/find.c		\
		./srcs/parse.c		\
		./srcs/read_cmd.c	\
		./srcs/run.c		\
		./srcs/separate.c	\
		./srcs/token.c	\
		./srcs/blt_func/blt_echo.c	\
		./srcs/blt_func/blt_cd.c	\
		./srcs/utils/ft_calloc.c	\
		./srcs/utils/ft_isalnum.c	\
		./srcs/utils/ft_isalpha.c	\
		./srcs/utils/ft_isdigit.c	\
		./srcs/utils/ft_isprint.c	\
		./srcs/utils/ft_memcpy.c	\
		./srcs/utils/ft_memmove.c	\
		./srcs/utils/ft_memset.c	\
		./srcs/utils/ft_putstr_fd.c	\
		./srcs/utils/ft_split.c	\
		./srcs/utils/ft_str_char_join.c	\
		./srcs/utils/ft_strchr.c	\
		./srcs/utils/ft_strcmp.c	\
		./srcs/utils/ft_strdup.c	\
		./srcs/utils/ft_strjoin.c	\
		./srcs/utils/ft_strlcpy.c	\
		./srcs/utils/ft_strlen.c	\
		./srcs/utils/ft_strncmp.c	\
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
