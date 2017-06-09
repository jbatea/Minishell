/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbateau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 14:17:01 by jbateau           #+#    #+#             */
/*   Updated: 2017/06/09 05:37:07 by jbateau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		my_replace_path(t_minishell *minishell, char **tab)
{
	t_env	*env;
	int		i;

	i = 0;
	while (tab[i])
	{
		if (tab[i][0] == '$' &&\
		(env = my_env_chr(minishell, tab[i] + 1)))
		{
			ft_strdel(&(tab[1]));
			if (env->value)
				tab[1] = ft_strdup(env->value);
		}
		i++;
	}
}

void		my_split(t_minishell *minishell, char *tmp, bool i)
{
	char	**tab;

	tab = NULL;
	tab = ft_strsplit(tmp, ' ');
	(tmp && i) ? ft_strdel(&tmp) : 0;
	my_replace_path(minishell, tab);
	my_check_cmd(minishell, tab);
	(tab) ? ft_tabfree(&tab) : 0;
}

void		my_parse_cmd(t_minishell *minishell, char *line)
{
	int		i;
	char	*tmp;
	char	**tab;

	i = 0;
	tmp = NULL;
	tab = NULL;
	tab = ft_strsplit(line, ';');
	(line) ? ft_strdel(&line) : 0;
	while (tab[i])
	{
		tmp = ft_strtrim(tab[i]);
		if (ft_strcmp(tmp, ""))
			my_split(minishell, tmp, false);
		(tmp) ? ft_strdel(&tmp) : 0;
		i++;
	}
	(tab) ? ft_tabfree(&tab) : 0;
}

void		my_split_cmd(t_minishell *minishell, char *line)
{
	char		*tmp;
	char		*str;

	tmp = NULL;
	str = NULL;
	str = ft_strtrim(line);
	tmp = ft_strspace(str);
	(str) ? ft_strdel(&str) : 0;
	(line) ? ft_strdel(&line) : 0;
	if (!tmp || !ft_strcmp("", tmp))
	{
		(tmp) ? ft_strdel(&tmp) : 0;
		return ;
	}
	if (ft_strchr(tmp, ';'))
		my_parse_cmd(minishell, tmp);
	else
		my_split(minishell, tmp, true);
}

int			main(int argc, char **argv, char **env)
{
	t_minishell	minishell;
	char		*line;
	int			i;

	(void)argc;
	(void)argv;
	line = NULL;
	i = 0;
	ft_bzero(&minishell, sizeof(minishell));
	my_minishell(&minishell);
	my_getenv(env);
	minishell = my_minishell(NULL);
	while (i < NB_SIGNAL)
	{
		(i != 18 && i != 19) ? signal(i, my_sig_handler) : 0;
		i++;
	}
	ft_printf("$> ");
	while (get_next_line(0, &line))
	{
		(line) ? my_split_cmd(&minishell, line) : 0;
		(!(minishell = my_minishell(NULL)).display) ? ft_printf("$> ") : 0;
		minishell.display = 0;
	}
	return (0);
}
