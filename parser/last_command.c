#include "parser.h"

int	check_build_in(t_par *par)
{
	char	*str;

	str = par->arg[0];
	if (!ft_strncmp(str, "cd", 3) || !ft_strncmp(str, "pwd", 4) || \
	!ft_strncmp(str, "unset", 6) || !ft_strncmp(str, "export", 4) || \
	!ft_strncmp(str, "env", 4) || !ft_strncmp(str, "exit", 5))
		return (1);
	else
		return (0);
}

void	pipe_case(t_par *par)
{
	int	i;

	i = 0;
	while (i < par->num_of_pipes)
	{
		if (i != par->current_pipe - 1)
			close(par->fd[i][0]);
		close(par->fd[i][1]);
		i++;
	}
	if (par->flag.red_r)
		dup2(par->fd_redirect_r, STDIN_FILENO);
	else
		dup2(par->fd[par->current_pipe - 1][0], STDIN_FILENO);
}

static void	child_process(t_par *par)
{
	errno = 0;
	if (par->current_pipe)
		pipe_case(par);
	if (par->flag.red_w)
		dup2(par->fd_redirect_w, STDOUT_FILENO);
	if (par->flag.red_r && !par->current_pipe)
		dup2(par->fd_redirect_r, STDIN_FILENO);
	if (!par->flag.build_in)
		ft_exec_command(par);
	exit(errno);
}

void	last_command(t_par *par)
{
	int	status;

	status = 0;
	par->flag.build_in = check_build_in(par);
	par->pid[par->current_pipe] = fork();
	if (par->pid[par->current_pipe] == 0)
		child_process(par);
	signal(SIGINT, SIG_IGN);
	if (par->flag.build_in)
		ft_exec_command(par);
	else
		*par->envp = change_envp("_", par->arg[0], *par->envp);
	close_pipes(par);
	waitpid(par->pid[par->current_pipe--], &status, 0);
	signal(SIGINT, catch_signal_c);
	status = WSTOPSIG(status);
	if (!par->flag.build_in)
		g_errnum = status;
	while (par->current_pipe >= 0 && !par->flag.build_in)
		waitpid(par->pid[par->current_pipe--], NULL, 0);
	if (par->flag.red_w)
		close(par->fd_redirect_w);
	if (par->flag.red_r)
		close(par->fd_redirect_r);
}
