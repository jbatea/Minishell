#include "../includes/minishell.h"

void	my_close_env(t_minishell *minishell)
{
	t_env	*env;

	env = minishell->env;
	while (env)
	{
		env->close = true;
		env = env->next;
	}
}

int	my_env_args(t_minishell *minishell, char **tab, int i)
{
	bool	n;

	n = 0;
	if (tab[i] && !ft_strcmp(tab[i], "-i"))
	{
		my_close_env(minishell);
		minishell->error = true;
		i++;
	}
	while (tab[i] && ft_strchr(tab[i], '='))
	{
		my_setenv(minishell, tab[i], &n, true);
		i++;
	}
	if (tab[i] && !ft_strcmp("env", tab[i]))
		return (my_env_args(minishell, tab, i + 1));
	return (i);
}

char		**my_cpy_args(char **tab, int i, int k)
{
	char	**args;
	int	j;

	j = 0;
	(args = (char **)malloc(sizeof(char *) * (i + 1))) ? 0 : MALLOC;
	while (tab[k])
	{
		(args[j] = ft_strdup(tab[k])) ? 0 : MALLOC;
		k++;
		j++;
	}
	args[j] = NULL;
	return (args);
}

char		**my_new_args(t_minishell *minishell, char **tab)
{
	int	i;
	int	k;

	k = my_env_args(minishell, tab, 1);
	i = k;
	while (tab[i])
		i++;
	i = i - k;
	if (i)
		return (my_cpy_args(tab, i, k));
	else
		my_printenv(minishell);
	return (NULL);
}

void		my_env(t_minishell *minishell, char **tab, bool *i)
{
	char	**args;

	*i = 1;
	args = NULL;
	if (tab[1] && !ft_strcmp("-i", tab[1]) && !tab[2])
		return ;
	if (!tab[1])
		my_printenv(minishell);
	else
	{
		args = my_new_args(minishell, tab);
		(args && !my_check_bin(minishell, args) && !minishell->error)\
		? (*i = 0) : 0;
		my_open_env(minishell);
		(args) ? ft_tabfree(&args) : 0;
		if (minishell->error)
		{
			(minishell->str_error) ?\
			ft_printf("minishell: command not found: %s\n",\
			minishell->str_error) : 0;
			minishell->error = false;
			ft_strdel(&(minishell->str_error));
		}
	}
}
