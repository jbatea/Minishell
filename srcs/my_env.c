#include "../includes/minishell.h"

void		my_freeenv(t_minishell *minishell)
{
	t_env	*tmp;
	t_env	*ptmp;

	tmp = minishell->env;
	while (tmp)
	{
		ptmp = tmp->next;
		(tmp->key) ? ft_strdel(&(tmp->key)) : 0;
		(tmp->value) ? ft_strdel(&(tmp->value)) : 0;
		(tmp->env) ? ft_strdel(&(tmp->env)) : 0;
		(tmp->old_value) ? ft_strdel(&(tmp->old_value)) : 0;
		ft_memdel((void **)&tmp);
		tmp = ptmp;
	}
}

void		my_addenv(t_minishell *minishell, char *env, bool n)
{
	t_env	*tmp;
	t_env	*new;
	int	i;

	(new = ft_memalloc(sizeof(t_env))) ? 0 : MALLOC;
	if ((i = ft_strchr_cnt(env, '=')) > 0)
	{
		(new->key = ft_strndup(env, i)) ? 0 : MALLOC;
		(new->value = ft_strdup(env + i + 1)) ? 0 : MALLOC;
	}
	else
		(new->key = ft_strdup(env)) ? 0 : MALLOC;
	my_envjoin(new);
	new->tmp = n;
	tmp = minishell->env;
	if (!tmp)
		minishell->env = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void		my_getenv(char **env)
{
	int		i;
	t_minishell minishell;

	minishell = my_minishell(NULL);
	i = 0;
	while (env[i])
	{
		my_addenv(&minishell, env[i], false);
		i++;
	}
	my_minishell(&minishell);
}

void		my_printenv(t_minishell *minishell)
{
	t_env	*env;

	env = minishell->env;
	while (env)
	{
		(env->env) ? ft_printf("%s\n", env->env) : 0;
		env = env->next;
	}
}

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

int	my_env_args(t_minishell *minishell, char **tab)
{
	int	i;
	bool	n;

	i = 1;
	n = 0;
	if (!ft_strcmp(tab[i], "-i"))
	{
		my_close_env(minishell);
		i++;
	}
	while (tab[i] && ft_strchr(tab[i], '='))
	{
		my_setenv(minishell, tab[i], &n, true);
		i++;
	}
	return (i);
}

char		**my_new_args(t_minishell *minishell, char **tab)
{
	char	**args;
	int	i;
	int	j;
	int	k;

	j = 0;
	k = my_env_args(minishell, tab);
	args = NULL;
	i = k;
	while (tab[i])
		i++;
	i = i - k;
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

void	my_clear_env(t_minishell *minishell)
{
	t_env	*env;

	env = minishell->env;
	while (env)
	{
		if (env->tmp)
		{
			(env->env) ? ft_strdel(&(env->env)) : 0;
			(env->value) ? ft_strdel(&(env->value)) : 0;
			if (!env->old_value)
				(env->key) ? ft_strdel(&(env->key)) : 0;
			else
			{
				(env->value = ft_strdup(env->old_value)) ? 0 : MALLOC;
				my_envjoin(env);
			}

		}
		env = env->next;
	}
}

void		my_open_env(t_minishell *minishell)
{
	t_env	*env;

	env = minishell->env;
	while (env)
	{
		env->close = false;
		env = env->next;
	}
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
		(!my_check_bin(minishell, args)) ? (*i = 0) : 0;
		my_clear_env(minishell);
		my_open_env(minishell);
		(args) ? ft_tabfree(&args) : 0;
		if (!(*i) && !ft_strcmp("-i", tab[1]))
		{
			ft_printf("minishell: command not found: %s\n", tab[2]);
			(*i = 1);
		}
	}
}
