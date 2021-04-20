#ifndef STRUCTURES_H
# define STRUCTURES_H

# define TYPE_PIPE 0
# define TYPE_CMD 1
# define TYPE_REDIRECT 2

# define RD_IN 0
# define RD_OUT 1
# define RD_OUT_APPEND 2

typedef struct	s_token		t_token;
typedef struct	s_cmdline 	t_cmdline;
typedef struct	s_pipe		t_pipe;

struct	s_token
{
	int		type;
	void	*by_type;
	t_token	*l_child;
	t_token	*r_child;
	t_token	*parent;
};

/*
** void *by_type -> t_cmdline / t_pipe
*/

struct s_pipe
{
	int		fd[2];
	char	*in;
	char	*out;
};

struct	s_cmdline
{
	char	*cmd;
	char	*arg;
	char	*rd;
	int		rd_type;
};

#endif
