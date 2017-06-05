#include "../includes/minishell.h"

void	my_replace_path(t_minishell *minishell, char **tab)
{
	t_env	*env;
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i][0] == '$' &&\
		(env = my_env_chr(minishell, tab[i] + 1)))
		{
			ft_strdel(&(tab[1]));
			if (env->value)
				(tab[1] = ft_strdup(env->value)) ? 0 : MALLOC;
		}
		i++;
	}
}

void	my_split(t_minishell *minishell, char *tmp)
{
	char		**tab;

	tab = NULL;
	(tab = ft_strsplit(tmp, ' ')) ? 0 : MALLOC;
	my_replace_path(minishell, tab);
	my_check_cmd(minishell, tab);
	(tab) ? ft_tabfree(&tab) : 0;
}

void	my_parse_cmd(t_minishell *minishell, char *line)
{
	int		i;
	char		*tmp;
	char		**tab;

	i = 0;
	tmp = NULL;
	tab = NULL;
	(tab = ft_strsplit(line, ';')) ? 0 : MALLOC;
	while (tab[i])
	{
		(tmp = ft_strtrim(tab[i])) ? 0 : MALLOC;
		if (ft_strcmp(tmp, ""))
			my_split(minishell, tmp);
		(tmp) ? ft_strdel(&tmp) : 0;
		i++;
	}
	(tab) ? ft_tabfree(&tab) : 0;
}

void	my_split_cmd(t_minishell *minishell, char *line)
{
	char		*tmp;

	tmp = NULL;
	(tmp = ft_strtrim(line)) ? 0 : MALLOC;
	(line) ? ft_strdel(&line) : 0;
	if (!tmp || !ft_strcmp("", tmp))
		return;
	if (ft_strchr(tmp, ';'))
		my_parse_cmd(minishell, tmp);
	else
		my_split(minishell, tmp);
	(tmp) ? ft_strdel(&tmp) : 0;
}

void	my_sig_handler(int sign)
{
	(sign == SIGHUP) ? my_exit("minishell: terminal line hangup", 0) : 0;
	(sign == SIGINT) ? ft_printf("\n$> ") : 0; 
	(sign == SIGILL) ? my_exit("minishell: illegal hardware instruction", 0) : 0;
	(sign == SIGTRAP) ? my_exit("minishell: trace trap", 0) : 0;
	(sign == SIGABRT) ? my_exit("minishell: abort", 0) : 0;
	(sign == SIGEMT) ? my_exit("minishell: EMT instruction", 0) : 0;
	(sign == SIGFPE) ? my_exit("minishell: floating point exception", 0) : 0;
	(sign == SIGKILL) ? my_exit("minishell: kill program", 0) : 0;
	(sign == SIGBUS) ? my_exit("minishell: bus error", 0) : 0;
	(sign == SIGSEGV) ? my_exit("minishell: segmentation fault", 0) : 0;
	(sign == SIGSYS) ? my_exit("minishell: invalid system call", 0) : 0;
	(sign == SIGPIPE) ? my_exit("minishell: write on a pipe with no reader", 0) : 0;
	(sign == SIGALRM) ? my_exit("minishell: real-time timer expired", 0) : 0;
	(sign == SIGXCPU) ? my_exit("minishell: cpu limit exceeded", 0) : 0;
	(sign == SIGXFSZ) ? my_exit("minishell: file size limit exceeded", 0) : 0;
	(sign == SIGVTALRM) ? my_exit("minishell: virtual time alarm", 0) : 0;
	(sign == SIGPROF) ? my_exit("minishell: profile signal", 0) : 0;
	(sign == SIGUSR1) ? my_exit("minishell: User defined signal 1", 0) : 0;
	(sign == SIGUSR2) ? my_exit("minishell: User defined signal 2", 0) : 0;
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;
	char		*line;
	int			i;

	(void)argc;
	(void)argv;
	line = NULL;
	i = 0;
	ft_bzero(&minishell, sizeof(minishell));
	my_minishell(&minishell);
	my_getenv(env);
	minishell = my_minishell(NULL);
	while (i < NB_SIGNAL)
	{
		(i != 18 && i != 19) ? signal(i, my_sig_handler) : 0;
		i++;
	}
	ft_printf("$> ");
	while (get_next_line(0, &line))
	{
		(line) ? my_split_cmd(&minishell, line) : 0;
		ft_printf("$> ");
	}
	my_exit(NULL, 0);
	return (0);
}
