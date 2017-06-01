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
		ft_memdel((void **)&tmp);
		tmp = ptmp;
	}
}

void		my_addenv(t_minishell *minishell, char *env)
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
		my_addenv(&minishell, env[i]);
		i++;
	}
	my_minishell(&minishell);
}

void		my_printenv(t_env *env, bool *i)
{
	while (env)
	{
		(env->key) ? ft_printf("%s=", env->key) : 0;
		(env->value) ? ft_printf("%s", env->value) : 0;
		(env->key || env->value) ? ft_printf("\n") : 0;
		env = env->next;
	}
	*i = 1;
}

