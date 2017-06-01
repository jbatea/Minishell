#include "../includes/minishell.h"

void	my_replace_path(t_minishell *minishell, char **tab)
{
	t_env	*env;
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i][0] == '$' && (env = my_env_chr(minishell, tab[i] + 1)))
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

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;
	char		*line;

	(void)argc;
	(void)argv;
	line = NULL;
	ft_bzero(&minishell, sizeof(minishell));
	my_minishell(&minishell);
	my_getenv(env);
	minishell = my_minishell(NULL);
	ft_printf("$> ");
	while (get_next_line(0, &line))
	{
		(line) ? my_split_cmd(&minishell, line) : 0;
		ft_printf("$> ");
	}
	my_exit(NULL);
	return (0);
}
