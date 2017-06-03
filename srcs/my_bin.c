#include "../includes/minishell.h"

void		my_printenv(t_minishell *minishell)
{
	t_env	*env;

	env = minishell->env;
	while (env)
	{
		(env->env && !(env->close)) ? ft_printf("%s\n", env->env) : 0;
		env = env->next;
	}
}

int	my_env_len(t_minishell *minishell)
{
	t_env	*env;
	int	i;

	i = 0;
	env = minishell->env;
	while (env)
	{
		(env->env && !(env->close)) ? i++ : 0;
		env = env->next;
	}
	return (i);
}

char	**my_filltab(t_env *env, int i)
{
	int	j;
	char	**tab;

	j = 0;
	(tab = (char **)malloc(sizeof(char *) * (i + 1))) ? 0 : MALLOC;
	while (env)
	{
		if (env->env && !(env->close))
		{
			(tab[j] = ft_strdup(env->env)) ? 0 : MALLOC;
			j++;
		}
		env = env->next;
	}
	tab[j] = NULL;
	return (tab);
}

char	**my_env_tab(t_minishell *minishell)
{
	t_env	*env;
	int	i;
	char	**tab;

	tab = NULL;
	if ((env = minishell->env))
	{
		i = my_env_len(minishell);
		tab = my_filltab(env, i);
	}
	return (tab);
}

bool	my_check_bin(t_minishell *minishell, char **tab)
{
	bool	ret;
	char	**env;

	env = my_env_tab(minishell);
	ret = my_check_path(minishell, tab, env);
	(!ret) ? (ret = my_check_access(tab, tab[0], env)) : 0;
	if (!ret)
	{
		(minishell->str_error) ? ft_strdel(&(minishell->str_error)) :\
			0;
		(minishell->str_error = ft_strdup(tab[0])) ? 0 : MALLOC;
	}
	(env) ? ft_tabfree(&env) : 0;
	return (ret);
}
