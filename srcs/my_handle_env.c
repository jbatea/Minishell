/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_handle_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbateau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 14:34:55 by jbateau           #+#    #+#             */
/*   Updated: 2017/06/09 02:09:17 by jbateau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void				my_freeenv(t_minishell *minishell)
{
	t_env			*tmp;
	t_env			*ptmp;

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

void				my_addenv(t_minishell *minishell, char *env, bool n)
{
	t_env			*tmp;
	t_env			*new;
	int				i;

	new = ft_memalloc(sizeof(t_env));
	if ((i = ft_strchr_cnt(env, '=')) > 0)
	{
		new->key = ft_strndup(env, i);
		new->value = ft_strdup(env + i + 1);
	}
	else
		new->key = ft_strdup(env);
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

void				my_getenv(char **env)
{
	int				i;
	t_minishell		minishell;

	minishell = my_minishell(NULL);
	i = 0;
	while (env[i])
	{
		my_addenv(&minishell, env[i], false);
		i++;
	}
	my_update_lvl(&minishell);
	(!i) ? my_empty_env(&minishell) : 0;
	my_minishell(&minishell);
}

void				my_clear_env(t_minishell *minishell)
{
	t_env			*env;

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
				env->value = ft_strdup(env->old_value);
				my_envjoin(env);
			}
		}
		env = env->next;
	}
}

void				my_open_env(t_minishell *minishell)
{
	t_env			*env;

	my_clear_env(minishell);
	env = minishell->env;
	while (env)
	{
		env->close = false;
		env = env->next;
	}
}
