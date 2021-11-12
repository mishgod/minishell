#include "../libshell.h"
#include "../parser/parser.h"

int	cmp_names(char *str, char *envp)
{
	int	k;

	k = 0;
	while (str[k] && str[k] != '=')
		k++;
	if (!ft_strncmp(str, envp, k))
	{
		k--;
		if ((str[k + 1] == '=' || !str[k + 1]) && (envp[k + 1] == '='
				|| !envp[k + 1]))
			return (1);
	}
	return (0);
}

char	**del_line(char **envp, int i)
{
	char	**arr;
	int		j;
	int		k;

	j = count_args(envp);
	arr = ft_calloc(j + 1, sizeof(char *));
	j = 0;
	k = 0;
	while (envp[j])
	{
		if (j != i)
		{
			arr[k] = ft_strdup(envp[j]);
			k++;
		}
		free (envp[j]);
		j++;
	}
	free (envp);
	return (arr);
}

char	*return_str_value(char *key, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (cmp_names(key, envp[i]))
		{
			if (ft_strlen(envp[i]) > ft_strlen(key) + 1)
				return (envp[i] + ft_strlen(key) + 1);
		}
		i++;
	}
	return (NULL);
}

void	dup_fd(t_par *par)
{
	errno = 0;
	if (par->current_pipe)
		pipe_case(par);
	if (par->flag.red_w)
		dup2(par->fd_redirect_w, STDOUT_FILENO);
	if (par->flag.red_r && !par->current_pipe)
		dup2(par->fd_redirect_r, STDIN_FILENO);
}

void	redirect(char *str, t_par *par)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		dup_fd(par);
		if (str)
			printf("%s\n", str);
		exit (0);
	}
	waitpid(pid, &status, 0);
	status = WSTOPSIG(status);
	g_errnum = status;
}
