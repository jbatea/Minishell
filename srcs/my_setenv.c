/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbateau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 17:04:47 by jbateau           #+#    #+#             */
/*   Updated: 2017/06/09 17:05:09 by jbateau          ###   ########.fr       */
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
			(tmp->value) ? (tmp->old_value = ft_strdup(tmp->value)) : 0;
			tmp->tmp = true;
		}
		(tmp->value) ? ft_strdel(&(tmp->value)) : 0;
		tmp->value = ft_strdup(tab + ft_strlen(key));
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
		if (tab[0] && ft_isalpha(tab[0]))
		{
			if (ft_strchr(tab, '='))
				key = ft_strndup(tab, ft_strchr_cnt(tab, '='));
			else
				key = ft_strdup(tab);
			if (!my_env_exist(minishell, key, n, tab))
				my_addenv(minishell, tab, n);
			(key) ? ft_strdel(&key) : 0;
		}
		else
			ft_printf("setenv: Variable name must begin with a letter\n");
	}
	*i = 1;
}
