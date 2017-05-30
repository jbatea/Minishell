#include "../includes/minishell.h"

void	my_parse_cmd(t_minishell *minishell, char *line)
{
	char		*tmp;
	char		**tab;
	int		i;

	i = 0;
	tab = NULL;
	tmp = NULL;
	(tmp = ft_strtrim(line)) ? 0 : MALLOC;
	if (!tmp || !ft_strcmp("", tmp))
		return;
	if (ft_strchr(tmp, ';'))
		(tab = ft_strsplit(tmp, ';')) ? 0 : MALLOC;
	if (tab)
	{
		while (tab[i])
		{
				if (ft_strcmp(tab[i], " "))
				{
					(minishell->tab = ft_strsplit(tab[i], ' ')) ? 0 : MALLOC;
					my_check_builtin(minishell);
				}
			i++;
		}
		ft_tabfree(tab);
	}
	else
	{
		(minishell->tab = ft_strsplit(tmp, ' ')) ? 0 : MALLOC;
		my_check_builtin(minishell);
	}
	(minishell->tab) ? ft_tabfree(minishell->tab) : 0;
	(tmp) ? ft_strdel(&tmp) : 0;
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	ft_bzero(&minishell, sizeof(minishell));
	my_minishell(&minishell);
	my_getenv(env);
	minishell = my_minishell(NULL);
	ft_printf("$> ");
	while (get_next_line(0, &(minishell.line)) && 1)
	{
		(minishell.line) ? my_parse_cmd(&minishell, minishell.line) : 0;
		(minishell.line) ? ft_strdel(&(minishell.line)) : 0;
		ft_printf("$> ");
	}
	my_exit(NULL);
	return (0);
}
