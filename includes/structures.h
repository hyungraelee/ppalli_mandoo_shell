#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct	s_token		t_token;
typedef struct	s_cmdline 	t_cmdline;

struct	s_token
{
	void	*by_type;
	t_token	*l_child;
	t_token	*r_child;
};

/*
** void *by_type -> t_cmdline / t_pipe
*/

// struct s_pipe
// {
// 	char	*in;
// 	char	*out;
// };

struct	s_cmdline
{
	char	*cmd;
	char	*arg;
};

#endif