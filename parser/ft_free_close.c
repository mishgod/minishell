#include "parser.h"

void	initial_variables(t_par *par, char **new_str)
{
	par->flag.pipe = 0;
	par->flag.red_w = 0;
	par->flag.red_r = 0;
	par->fd_redirect_w = -1;
	par->fd_redirect_r = -1;
	*new_str = NULL;
	par->arg = NULL;
}

void	error_close_fd(t_par *par, int num)
{
	printf("minishell: %s\n", strerror(errno));
	g_errnum = errno;
	while (num >= 0)
	{
		close(par->fd[num][0]);
		close(par->fd[num][1]);
		num--;
	}
}

void	close_pipes(t_par *par)
{
	int	i;

	i = 0;
	while (i != par->num_of_pipes)
	{
		close(par->fd[i][0]);
		close(par->fd[i][1]);
		i++;
	}
}

int	free_str_par(t_par *par, char *str)
{
	if (str)
		free(str);
	free(par);
	return (1);
}

int	close_and_free(t_par *par, char *new_str)
{
	close_pipes(par);
	free(new_str);
	free(par);
	return (1);
}
