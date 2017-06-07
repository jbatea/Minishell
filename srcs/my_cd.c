/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbateau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 14:21:51 by jbateau           #+#    #+#             */
/*   Updated: 2017/06/07 15:19:33 by jbateau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	my_pwd_maj(t_minishell *minishell, char *s)
{
	char	tmp[BUF_SIZE];
	char	*str;
	t_env	*pwd;
	t_env	*o_pwd;

	str = NULL;
	pwd = NULL;
	o_pwd = NULL;
	ft_bzero(tmp, BUF_SIZE);
	(s) ? ft_strcpy(tmp, s) : getcwd(tmp, BUF_SIZE);
	pwd = my_env_chr(minishell, "PWD");
	(str = ft_strjoin("PWD=", tmp)) ? 0 : MALLOC;
	(!pwd) ? my_addenv(minishell, str, false) : 0;
	pwd = my_env_chr(minishell, "PWD");
	o_pwd = my_env_chr(minishell, "OLDPWD");
	(o_pwd && o_pwd->value) ? ft_strdel(&(o_pwd->value)) : 0;
	if (o_pwd)
		o_pwd->value = ((pwd && pwd->value) ? ft_strdup(pwd->value) : NULL);
	(pwd && pwd->value) ? ft_strdel(&(pwd->value)) : 0;
	pwd->value = ((pwd && tmp[0]) ? ft_strdup(tmp) : NULL);
	(pwd) ? my_envjoin(pwd) : 0;
	(o_pwd) ? my_envjoin(o_pwd) : 0;
}

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
		(tmp = ft_strdup(tab[i] + 1)) ? 0 : MALLOC;
		ft_strdel(&tab[i]);
		(tab[i] = ft_strjoin(my_home(minishell), tmp)) ? 0 : MALLOC;
		ft_strdel(&tmp);
	}
	my_check_cd(minishell, tab[i], str);
}

void	my_cd_flags(t_minishell *minishell, char **tab)
{
	struct stat sb;
	char		*tmp;

	tmp = NULL;
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
			(env && env->value) ?\
				my_check_cd(minishell, env->value, NULL) :\
				my_check_cd(minishell, my_home(minishell), NULL);
			(env && env->value) ? ft_printf("%s\n", env->value) : 0;
		}
		else
			my_cd_flags(minishell, tab);
	}
	else
		my_check_cd(minishell, my_home(minishell), NULL);
	*i = 1;
}
