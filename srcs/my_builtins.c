#include "../includes/minishell.h"

void	my_echo(t_minishell *minishell)
{
	int	i;
	int	j;

	j = ((minishell->tab[1] && !ft_strcmp(minishell->tab[1], "-n")) ? 2 : 1);
	i = j;
	while (minishell->tab[i])
	{
		(j != i) ? ft_printf(" ") : 0;
		ft_printf("%s", minishell->tab[i]);
		i++;
	}
	(minishell->tab[1] && !ft_strcmp(minishell->tab[1], "-n")) ? 0 : ft_printf("\n");
}

void	my_setenv(t_minishell *minishell)
{
	t_env	*tmp;
	char	*key;
	
	key = NULL;
	if (minishell->tab[1])
	{
		if (ft_strchr(minishell->tab[1], '='))
			key = ft_strndup(minishell->tab[1], ft_strchr_cnt(minishell->tab[1], '='));
		else
			key = ft_strdup(minishell->tab[1]);
		tmp = my_env_chr(minishell, key);
		if (tmp)
		{
			ft_strdel(&(tmp->value));
			tmp->value = ft_strdup(minishell->tab[1] + ft_strlen(key) + 1);
		}
		else
			my_addenv(minishell, minishell->tab[1]);
		(key) ? ft_strdel(&key) : 0;
	}
}

void	my_unsetenv(t_minishell *minishell)
{
	t_env	*tmp;
	char	*key;
	
	key = NULL;
	tmp = NULL;
	if (minishell->tab[1])
	{
		if (ft_strchr(minishell->tab[1], '='))
			key = ft_strndup(minishell->tab[1], ft_strchr_cnt(minishell->tab[1], '='));
		else
			key = ft_strdup(minishell->tab[1]);
		tmp = my_env_chr(minishell, key);
		(tmp && tmp->key) ? ft_strdel(&(tmp->key)) : 0;
		(tmp && tmp->value) ? ft_strdel(&(tmp->value)) : 0;
		(key) ? ft_strdel(&key) : 0;
	}
}

void	my_check_builtin(t_minishell *minishell)
{
	(!ft_strcmp("echo", minishell->tab[0])) ? my_echo(minishell) : 0;
	(!ft_strcmp("env", minishell->tab[0])) ? my_printenv(minishell->env) : 0;
	(!ft_strcmp("cd", minishell->tab[0])) ? my_cd(minishell) : 0;
	(!ft_strcmp("exit", minishell->tab[0])) ? my_exit(NULL) : 0;
	(!ft_strcmp("setenv", minishell->tab[0])) ? my_setenv(minishell) : 0;
	(!ft_strcmp("unsetenv", minishell->tab[0])) ? my_unsetenv(minishell) : 0;
}
