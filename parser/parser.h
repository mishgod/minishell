#ifndef PARSER_H
# define PARSER_H

# include "../libshell.h"

typedef struct s_flags
{
	int	pipe;
	int	red_w;
	int	red_r;
	int	build_in;
}				t_flag;

typedef struct s_parser
{
	t_flag	flag;
	pid_t	pid[1000];
	int		fd[1000][2];
	int		num_of_pipes;
	int		current_pipe;
	int		fd_redirect_w;
	int		fd_redirect_r;
	char	**arg;
	char	***envp;
	int		errno_exit;
}				t_par;

void	initial_variables(t_par *par, char **new_str);
int		ft_preparsing(char *str);
int		num_of_pipes(t_par *par, char *orig_str);
int		ft_pipe_to_fd(t_par *par);
char	*get_one_command(t_par *par, char *str, char **new_str);
char	*remove_redirects(t_par *par, char *str);
char	**new_split(t_par *par, char *str);
char	*parser_one_command(t_par *par, char *str);
void	ft_pipe(t_par *par);
void	last_command(t_par *par);
void	ft_exec_command(t_par *par);
char	*ft_dollar(char *str, int *i, char *envp[]);
char	*take_value_from_key(char *str, int i);
char	*ft_slash(char *str, int *i);
char	*ft_one_quoter(char *str, int *i);
char	*ft_double_quoter(char *str, int *i, char *envp[]);
void	pipe_case(t_par *par);
void	skip_quoters(char *str, int *i, char ch);
char	*ft_redirects(char *str, int *i, t_par *par);
char	*ft_double_redir_open(char *str, int *i, t_par *par);
char	*parser_filename(t_par *par, char *str_orig);
int		check_in_redirect(t_par *par, char *str, int *i, char *token);
void	error_open(char **str, char *file_name);
void	error_close_fd(t_par *par, int num);
void	close_pipes(t_par *par);
int		free_str_par(t_par *par, char *str);
int		close_and_free(t_par *par, char *new_str);
char	**cmd_cd(char **arr, char **envp);
char	**cmd_env(char **envp, t_par *par);
char	**cmd_pwd(char **envp, t_par *par);
char	**cmd_unset(char **arr, char **envp);
void	cmd_other(char **arr, char **envp);
void	cmd_echo(char **arr);
char	**cmd_export(char **arr, char **envp, t_par *par);
char	**change_envp2(char *name, char **arr);
int		export_dst(char *str);
void	dup_fd(t_par *par);
void	redirect(char *str, t_par *par);
#endif
