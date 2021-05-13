#ifndef STRUCTURES_H
# define STRUCTURES_H

/*	flag	*/
# define NONE 0
# define CMD 1
# define REDIRECT 2
# define PIPE 4
# define ARG 8
# define POSSIBLE 16 // file exist after redirect
# define S_QUOTE 32
# define D_QUOTE 64

# define RD_IN 1
# define RD_OUT 2
# define RD_APPEND 4
# define COMMAND 8
# define ARGUMENT 16

# define IFS " \t\n"

typedef struct	s_cmd		t_cmd;
typedef struct	s_token		t_token;
typedef struct	s_history	t_history;
typedef struct	s_read		t_read;

struct	s_token
{
	int		type;
	char	*arg;
	t_token	*next;
	t_token	*prev;
};

struct	s_cmd
{
	char	*cmd_name;
	int		fds[2];
	t_token	*token;
	t_cmd	*next;
	t_cmd	*prev;
};

struct s_history
{
	char		*record;
	char		*edit_record;
	t_history	*next;
	t_history	*prev;
};

struct s_read
{
	char		*result;
	char		**on_terminal;
	int			c;
	int			cursor;
	char		*new;
	t_history	*temp;
	t_history	*selected_history;
};


#endif
