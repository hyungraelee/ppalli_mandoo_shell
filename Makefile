NAME = minishell
CC = gcc
# CFLAGS = -Wall -Wextra -Werror
# CFLAGS = -g3 -fsanitize=address

ifeq ($(DEBUG),true)
	CFLAGS += -g
endif

SRCS_DIR =	./srcs	\
			./srcs/pre_setting	\
			./srcs/pre_setting/cursor	\
			./srcs/pre_setting/tokenize	\
			./srcs/run	\
			./srcs/run/blt_func	\
			./srcs/run/utils	\
			./srcs/utils

OBJS_DIR = ./objs
INC_DIR = ./includes

SRCS =	./srcs/main.c	\
		./srcs/minishell.c	\
		./srcs/pre_setting/check_syntax.c	\
		./srcs/pre_setting/check_syntax2.c	\
		./srcs/pre_setting/handle_enter_normal.c	\
		./srcs/pre_setting/handle_key_arrow.c	\
		./srcs/pre_setting/handle_special_key.c	\
		./srcs/pre_setting/init.c	\
		./srcs/pre_setting/prompt.c	\
		./srcs/pre_setting/read_cmd.c	\
		./srcs/pre_setting/cursor/cursor.c	\
		./srcs/pre_setting/tokenize/parse.c	\
		./srcs/pre_setting/tokenize/separate.c	\
		./srcs/pre_setting/tokenize/make_token_list.c	\
		./srcs/pre_setting/tokenize/token_array.c	\
		./srcs/pre_setting/tokenize/token.c	\
		./srcs/run/builtin.c	\
		./srcs/run/error.c	\
		./srcs/run/find.c	\
		./srcs/run/handle_no_cmd.c	\
		./srcs/run/inner_func.c	\
		./srcs/run/pipe.c	\
		./srcs/run/redirect.c	\
		./srcs/run/run.c	\
		./srcs/run/signal.c	\
		./srcs/run/blt_func/blt_cd.c	\
		./srcs/run/blt_func/blt_echo.c	\
		./srcs/run/blt_func/blt_env.c	\
		./srcs/run/blt_func/blt_exit.c	\
		./srcs/run/blt_func/blt_export.c	\
		./srcs/run/blt_func/blt_export2.c	\
		./srcs/run/blt_func/blt_export3.c	\
		./srcs/run/blt_func/blt_export4.c	\
		./srcs/run/blt_func/blt_pwd.c	\
		./srcs/run/blt_func/blt_unset.c	\
		./srcs/run/utils/free.c	\
		./srcs/run/utils/change_env.c	\
		./srcs/run/utils/is_pipe_exist.c	\
		./srcs/run/utils/replace_env_in_arg.c	\
		./srcs/run/utils/save_old_fds.c	\
		./srcs/run/utils/turn_on_flag.c	\
		./srcs/utils/ft_atoi.c	\
		./srcs/utils/ft_calloc.c	\
		./srcs/utils/ft_isalnum.c	\
		./srcs/utils/ft_isalpha.c	\
		./srcs/utils/ft_isdigit.c	\
		./srcs/utils/ft_isprint.c	\
		./srcs/utils/ft_itoa.c	\
		./srcs/utils/ft_memcpy.c	\
		./srcs/utils/ft_memmove.c	\
		./srcs/utils/ft_memset.c	\
		./srcs/utils/ft_putstr_fd.c	\
		./srcs/utils/ft_split.c	\
		./srcs/utils/ft_str_char_del.c	\
		./srcs/utils/ft_str_char_embed.c	\
		./srcs/utils/ft_str_char_join.c	\
		./srcs/utils/ft_strchr.c	\
		./srcs/utils/ft_strcmp.c	\
		./srcs/utils/ft_strcpy_i_to_j.c	\
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
	@$(CC) $(CFLAGS) -lncurses -o $@ $^

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
