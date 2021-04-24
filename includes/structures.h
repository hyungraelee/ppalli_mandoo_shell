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

# define RD_IN 0
# define RD_OUT 1
# define RD_APPEND 2
# define COMMAND 3
# define OPTION 4
# define STR 5
# define ENV 6

# define IFS " \t\n"

typedef struct	s_cmd		t_cmd;
typedef struct	s_pipe		t_pipe;
typedef struct	s_token		t_token;

struct	s_token
{
	int		type;
	char	*arg;
	t_token	*next;
	t_token	*prev;
};

struct	s_cmd
{
	t_token	*token;
	t_pipe	*next;
	t_pipe	*prev;
};

struct s_pipe
{
	int		fd[2];
	t_cmd	*next;
	t_cmd	*prev;
};

#endif
