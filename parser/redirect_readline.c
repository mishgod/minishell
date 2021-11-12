#include "parser.h"

static void	child_loop(int len, char *str, int fd[2], char *stopword)
{
	while (1)
	{
		if (g_errnum == 1)
			break ;
		str = readline("> ");
		if (g_errnum == 1)
		{
			if (str)
				free(str);
			break ;
		}
		if (str == NULL)
			break ;
		len = ft_strlen(str);
		if (!ft_strncmp(str, stopword, len + 1) && len)
		{
			free(str);
			break ;
		}
		ft_putendl_fd(str, fd[1]);
		free(str);
	}
}

static void	child_process(int fd[2], char *stopword)
{
	signal(SIGINT, signal_c_child_readline);
	close(fd[0]);
	child_loop(0, NULL, fd, stopword);
	close(fd[1]);
	exit (g_errnum);
}

static int	parent_process(t_par *par, int fd[2], char *stopword, int pid)
{
	int	status;

	close(fd[1]);
	status = 0;
	waitpid(pid, &status, 0);
	status = WSTOPSIG(status);
	free (stopword);
	if (par->flag.red_r)
		close(par->fd_redirect_r);
	if (status != 1)
	{
		par->flag.red_r = 1;
		par->fd_redirect_r = fd[0];
	}
	else
	{
		close(fd[0]);
		g_errnum = 1;
		return (1);
	}
	return (0);
}

static int	readline_loop(t_par *par, char *stopword)
{
	int		fd[2];
	int		pid;
	int		old_g_errnum;

	old_g_errnum = g_errnum;
	g_errnum = 0;
	if (pipe(fd))
	{
		printf("minishell: %s\n", strerror(g_errnum));
		g_errnum = 1;
		free(stopword);
		return (1);
	}
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		child_process(fd, stopword);
	if (parent_process(par, fd, stopword, pid))
		return (1);
	signal(SIGINT, catch_signal_c);
	g_errnum = old_g_errnum;
	return (0);
}

char	*ft_double_redir_open(char *str, int *i, t_par *par)
{
	int		j;
	int		k;
	char	*stopword;

	j = *i;
	*i += 2;
	k = check_in_redirect(par, str, i, "<<");
	if (k == -1)
		return (NULL);
	stopword = ft_substr(str, k, *i - k);
	stopword = parser_filename(par, stopword);
	str = input_value_to_string(str, "", *i - j, j);
	*i = j;
	if (readline_loop(par, stopword))
	{
		free(str);
		str = NULL;
	}
	return (str);
}
