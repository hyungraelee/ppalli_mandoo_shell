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
typedef struct	s_redirect	t_redirect;


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

#endif
