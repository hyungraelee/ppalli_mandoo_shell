#ifndef STRUCTURES_H
# define STRUCTURES_H

# define TYPE_PIPE 0
# define TYPE_CMD 1
# define TYPE_REDIRECT 2

# define RD_IN 0
# define RD_OUT 1
# define RD_APPEND 2

typedef struct	s_cmd		t_cmd;
typedef struct	s_pipe		t_pipe;

struct	s_cmd
{
	char	**line;
	char	*cmd;
	char	*arg;
	char	*rd_in;
	char	*rd_out;
	char	*rd_append;
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
