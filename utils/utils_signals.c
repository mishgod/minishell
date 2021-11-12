#include "../libshell.h"

void	catch_signal_c(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_errnum = 1;
}

void	catch_empty_signal_c(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	g_errnum = 1;
}

void	signal_c_child_readline(int signum)
{
	(void)signum;
	g_errnum = 1;
}
