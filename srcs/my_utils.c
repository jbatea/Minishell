/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbateau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 14:32:31 by jbateau           #+#    #+#             */
/*   Updated: 2017/06/09 02:11:19 by jbateau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			my_envjoin(t_env *env)
{
	char	*tmp;

	tmp = NULL;
	(env->env) ? ft_strdel(&(env->env)) : 0;
	if (!env->key && !env->value)
		return ;
	if (env->key && env->value)
	{
		tmp = ft_strjoin(env->key, "=");
		env->env = ft_strjoin(tmp, env->value);
		ft_strdel(&tmp);
	}
	else
		env->env = ft_strjoin(env->key, "=");
}

char			*my_home(t_minishell *minishell)
{
	t_env	*tmp;

	if ((tmp = my_env_chr(minishell, "HOME")) && tmp->value)
		return (tmp->value);
	return ("");
}

t_env			*my_env_chr(t_minishell *minishell, char *cmd)
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

void			my_exit(char *error, int n)
{
	t_minishell	minishell;

	minishell = my_minishell(NULL);
	(error) ? ft_printf("%s\n", error) : 0;
	(minishell.str_error) ? ft_strdel(&(minishell.str_error)) : 0;
	my_freeenv(&minishell);
	(n) ? exit((n % 256)) : exit(0);
}

t_minishell		my_minishell(t_minishell *minishell)
{
	static	t_minishell	save;

	save = ((minishell) ? *minishell : save);
	return (save);
}
