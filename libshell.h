#ifndef LIBSHELL_H
# define LIBSHELL_H
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "lib/libft.h"
# include <signal.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <errno.h>
# include <string.h>

int		g_errnum;

int		ft_parser(char *str, char **envp[]);
char	*join_strings_with_free_first(char *str1, char *str2);
char	*input_value_to_string(char *str, char *str_var, int len, int begin);
void	free_arr(char **arr);
char	**change_envp(char *name, char *arg, char **arr);
char	**get_envp(char **arr);
char	**add_line(char *str, char **arr);
int		cmp_names(char *str, char *envp);
char	*return_str_value(char *key, char **envp);
char	**del_line(char **envp, int i);
int		count_args(char **arr);
void	catch_signal_c(int signum);
void	signal_c_child_readline(int signum);
void	catch_empty_signal_c(int signum);
#endif