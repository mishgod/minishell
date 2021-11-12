#include "parser.h"

static void	first_pipe(t_par *par, int i)
{
	par->pid[par->current_pipe - 1] = fork();
	if (par->pid[par->current_pipe - 1] == 0)
	{
		while (i < par->num_of_pipes)
		{
			close(par->fd[i][0]);
			if (i != 0)
				close(par->fd[i][1]);
			i++;
		}
		if (par->flag.red_r)
			dup2(par->fd_redirect_r, STDIN_FILENO);
		if (par->flag.red_w)
			dup2(par->fd_redirect_w, STDOUT_FILENO);
		else
			dup2(par->fd[par->current_pipe - 1][1], STDOUT_FILENO);
		ft_exec_command(par);
		exit (errno);
	}
}

static void	close_fd(t_par *par)
{
	int	i;

	i = 0;
	while (i < par->num_of_pipes)
	{
		if (i != par->current_pipe - 2)
			close(par->fd[i][0]);
		if (i != par->current_pipe - 1)
			close(par->fd[i][1]);
		i++;
	}
}

static void	after_first_pipe(t_par *par)
{
	int	fd[2];
	int	fd_before[2];

	fd[0] = par->fd[par->current_pipe - 1][0];
	fd[1] = par->fd[par->current_pipe - 1][1];
	fd_before[0] = par->fd[par->current_pipe - 2][0];
	fd_before[1] = par->fd[par->current_pipe - 2][1];
	par->pid[par->current_pipe - 1] = fork();
	if (par->pid[par->current_pipe - 1] == 0)
	{
		close_fd(par);
		if (par->flag.red_r)
			dup2(par->fd_redirect_r, STDIN_FILENO);
		else
			dup2(fd_before[0], STDIN_FILENO);
		if (par->flag.red_w)
			dup2(par->fd_redirect_w, STDOUT_FILENO);
		else
			dup2(fd[1], STDOUT_FILENO);
		ft_exec_command(par);
		exit (errno);
	}
}

void	ft_pipe(t_par *par)
{
	if (par->current_pipe == 1)
		first_pipe(par, 0);
	else
		after_first_pipe(par);
}

int	ft_pipe_to_fd(t_par *par)
{
	int	i;

	i = 0;
	while (i < par->num_of_pipes)
	{
		if (pipe(par->fd[i]))
		{
			error_close_fd(par, i - 1);
			return (1);
		}
		par->pid[i] = -1;
		i++;
	}
	while (i < 1000)
	{
		par->fd[i][0] = STDIN_FILENO;
		par->fd[i][1] = STDOUT_FILENO;
		par->pid[i] = -1;
		i++;
	}
	return (0);
}
