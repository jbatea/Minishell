/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbateau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 14:23:43 by jbateau           #+#    #+#             */
/*   Updated: 2017/06/09 17:05:05 by jbateau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		my_unsetenv(t_minishell *minishell, char **tab, bool *i)
{
	t_env	*tmp;
	char	*key;
	int		j;

	j = 0;
	key = NULL;
	tmp = NULL;
	while (tab[j])
	{
		if (ft_strchr(tab[j], '='))
			key = ft_strndup(tab[j], ft_strchr_cnt(tab[j], '='));
		else
			key = ft_strdup(tab[j]);
		tmp = my_env_chr(minishell, key);
		(tmp && tmp->key) ? ft_strdel(&(tmp->key)) : 0;
		(tmp && tmp->value) ? ft_strdel(&(tmp->value)) : 0;
		(tmp && tmp->env) ? ft_strdel(&(tmp->env)) : 0;
		(tmp && tmp->old_value) ? ft_strdel(&(tmp->old_value)) : 0;
		(key) ? ft_strdel(&key) : 0;
		j++;
	}
	*i = 1;
}

int			my_print_error(char **tab, bool *i, char *func)
{
	int		ret;

	ret = false;
	if (!tab[1])
	{
		*i = 1;
		ft_printf("%s: Too few arguments\n", func);
		ret = true;
	}
	return (ret);
}

void		my_handle_env(t_minishell *minishell, char **tab, bool *i)
{
	int		j;

	j = 1;
	if (!ft_strcmp("setenv", tab[0]))
	{
		while (tab[j])
		{
			my_setenv(minishell, tab[j], i, i);
			j++;
		}
		my_print_error(tab, i, "setenv");
	}
	if (!ft_strcmp("unsetenv", tab[0]) && !my_print_error(tab, i, "unsetenv"))
		my_unsetenv(minishell, tab, i);
}

bool		my_check_builtin(t_minishell *minishell, char **tab)
{
	bool	i;
	int		n;

	i = 0;
	(!ft_strcmp("echo", tab[0])) ? my_echo(tab, &i) : 0;
	(!ft_strcmp("env", tab[0])) ? my_env(minishell, tab, &i) : 0;
	(!ft_strcmp("cd", tab[0])) ? my_cd(minishell, tab, &i) : 0;
	my_handle_env(minishell, tab, &i);
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
