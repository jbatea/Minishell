/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbateau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 14:21:51 by jbateau           #+#    #+#             */
/*   Updated: 2017/06/09 04:17:50 by jbateau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	my_check_cd(t_minishell *minishell, char *path, char *str)
{
	if (access(path, F_OK))
		ft_printf("cd: no such file or directory: %s\n", path);
	else if (access(path, R_OK))
		ft_printf("cd: permission denied %s\n", path);
	if (!chdir(path))
		my_pwd_maj(minishell, str);
}

void	my_replace_home(t_minishell *minishell, char **tab, char *str, int i)
{
	char	*tmp;

	tmp = NULL;
	if (tab[i][0] == '~')
	{
		tmp = ft_strdup(tab[i] + 1);
		ft_strdel(&tab[i]);
		tab[i] = ft_strjoin(my_home(minishell), tmp);
		ft_strdel(&tmp);
	}
	my_check_cd(minishell, tab[i], str);
}

char	*my_oldpwd(t_minishell *minishell, char *tmp)
{
	t_env	*env;
	int		i;

	ft_strdel(&tmp);
	env = my_env_chr(minishell, "PWD");
	if (!env || !env->value)
		return (ft_strdup("/"));
	i = ft_strrchr_cnt(env->value, '/');
	if (i <= 0)
		return (ft_strdup("/"));
	return (ft_strndup(env->value, i));
}

void	my_cd_flags(t_minishell *minishell, char **tab)
{
	struct stat sb;

	if (tab[2])
	{
		lstat(tab[2], &sb);
		if (!ft_strcmp(tab[1], "-P") && S_ISLNK(sb.st_mode))
			my_replace_home(minishell, tab, NULL, 2);
		else
			my_replace_home(minishell, tab, tab[2], 2);
	}
	else
	{
		lstat(tab[1], &sb);
		(!ft_strcmp(tab[1], "..")) ? (tab[1] = my_oldpwd(minishell, tab[1]))\
			: 0;
		(S_ISLNK(sb.st_mode)) ?\
			my_replace_home(minishell, tab, tab[1], 1) :\
			my_replace_home(minishell, tab, NULL, 1);
	}
}

void	my_cd(t_minishell *minishell, char **tab, bool *i)
{
	t_env	*env;

	if (tab[1])
	{
		if (!ft_strcmp(tab[1], "-"))
		{
			env = my_env_chr(minishell, "OLDPWD");
			(env && env->value) ? ft_printf("%s\n", env->value) : 0;
			(env && env->value) ?\
				my_check_cd(minishell, env->value, NULL) :\
				ft_printf("OLDPWD not set\n");
		}
		else
			my_cd_flags(minishell, tab);
	}
	else
		my_check_cd(minishell, my_home(minishell), NULL);
	*i = 1;
}
