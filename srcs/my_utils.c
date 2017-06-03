#include "../includes/minishell.h"

void	my_envjoin(t_env *env)
{
	char	*tmp;

	tmp = NULL;
	(env->env) ? ft_strdel(&(env->env)) : 0;
	if (!env->key && !env->value)
		return;
	if (env->key && env->value)
	{
		(tmp = ft_strjoin(env->key, "=")) ? 0 : MALLOC;
		(env->env = ft_strjoin(tmp, env->value)) ? 0 : MALLOC;
		ft_strdel(&tmp);
	}
	else
		(env->env = ft_strjoin(env->key, "=")) ? 0 : MALLOC;
}

char	*my_home(t_minishell *minishell)
{
	t_env	*tmp;
	
	if ((tmp = my_env_chr(minishell, "HOME")))
		return (tmp->value);
	return ("");
}

t_env	*my_env_chr(t_minishell *minishell, char *cmd)
{
	t_env	*tmp;

	tmp = minishell->env;
	while (tmp)
	{
		if (tmp->key && !ft_strcmp(tmp->key, cmd))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void		my_exit(char *error)
{
	t_minishell	minishell;

	minishell = my_minishell(NULL);
	(error) ? ft_printf("%s\n", error) : 0;
	(minishell.str_error) ? ft_strdel(&(minishell.str_error)) : 0;
	my_freeenv(&minishell);
	exit(EXIT_FAILURE);
}

t_minishell	my_minishell(t_minishell *minishell)
{
	static	t_minishell	save;

	save = ((minishell) ? *minishell : save);
	return (save);
}

