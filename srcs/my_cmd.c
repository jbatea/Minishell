/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbateau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 14:23:43 by jbateau           #+#    #+#             */
/*   Updated: 2017/06/09 04:32:34 by jbateau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool		my_env_exist(t_minishell *minishell, char *key, bool n, char *tab)
{
	t_env	*tmp;
	bool	ret;

	ret = false;
	tmp = my_env_chr(minishell, key);
	if (tmp)
	{
		if (n)
		{
			tmp->old_value = ft_strdup(tmp->value);
			tmp->tmp = true;
		}
		(tmp->value) ? ft_strdel(&(tmp->value)) : 0;
		tmp->value = ft_strdup(tab + ft_strlen(key) + 1);
		my_envjoin(tmp);
		tmp->close = false;
		ret = true;
	}
	return (ret);
}

void		my_setenv(t_minishell *minishell, char *tab, bool *i, bool n)
{
	char	*key;

	key = NULL;
	if (tab)
	{
		if (ft_strchr(tab, '='))
			key = ft_strndup(tab, ft_strchr_cnt(tab, '='));
		else
			key = ft_strdup(tab);
		if (!my_env_exist(minishell, key, n, tab))
			my_addenv(minishell, tab, n);
		(key) ? ft_strdel(&key) : 0;
	}
	*i = 1;
}

void		my_unsetenv(t_minishell *minishell, char **tab, bool *i)
{
	t_env	*tmp;
	char	*key;

	key = NULL;
	tmp = NULL;
	if (tab[1])
	{
		if (ft_strchr(tab[1], '='))
			key = ft_strndup(tab[1], ft_strchr_cnt(tab[1], '='));
		else
			key = ft_strdup(tab[1]);
		tmp = my_env_chr(minishell, key);
		(tmp && tmp->key) ? ft_strdel(&(tmp->key)) : 0;
		(tmp && tmp->value) ? ft_strdel(&(tmp->value)) : 0;
		(tmp && tmp->env) ? ft_strdel(&(tmp->env)) : 0;
		(tmp && tmp->old_value) ? ft_strdel(&(tmp->old_value)) : 0;
		(key) ? ft_strdel(&key) : 0;
	}
	*i = 1;
}

bool		my_check_builtin(t_minishell *minishell, char **tab)
{
	bool	i;
	int		n;

	i = 0;
	(!ft_strcmp("echo", tab[0])) ? my_echo(tab, &i) : 0;
	(!ft_strcmp("env", tab[0])) ? my_env(minishell, tab, &i) : 0;
	(!ft_strcmp("cd", tab[0])) ? my_cd(minishell, tab, &i) : 0;
	(!ft_strcmp("setenv", tab[0])) ?\
		my_setenv(minishell, tab[1], &i, i) : 0;
	(!ft_strcmp("unsetenv", tab[0])) ? my_unsetenv(minishell, tab, &i) : 0;
	if (!ft_strcmp("exit", tab[0]))
	{
		i = 1;
		if (tab[1])
		{
			n = ft_atoi(tab[1]);
			ft_tabfree(&tab);
			my_exit(NULL, n);
		}
		ft_tabfree(&tab);
		my_exit(NULL, 0);
	}
	return (i);
}

void		my_check_cmd(t_minishell *minishell, char **tab)
{
	(minishell->str_error) ? ft_strdel(&(minishell->str_error)) : 0;
	minishell->error = my_check_builtin(minishell, tab);
	(!(minishell->error)) ?\
		(minishell->error = my_check_bin(minishell, tab)) : 0;
	if (!minishell->error)
		ft_printf("minishell: command not found: %s\n", tab[0]);
	(minishell->str_error) ? ft_strdel(&(minishell->str_error)) : 0;
}
