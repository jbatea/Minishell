/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbateau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 14:32:07 by jbateau           #+#    #+#             */
/*   Updated: 2017/06/09 05:25:27 by jbateau          ###   ########.fr       */
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
	str = ft_strjoin("PWD=", tmp);
	(!pwd) ? my_addenv(minishell, str, false) : 0;
	(str) ? ft_strdel(&str) : 0;
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

char	**my_find_path(t_minishell *minishell)
{
	t_env	*env;
	char	**path;

	path = NULL;
	env = my_env_chr(minishell, "PATH");
	if (env && env->close)
		return (path);
	if (env && env->value)
		path = ft_strsplit(env->value, ':');
	return (path);
}

bool	my_fork_and_exec(char *str, char **tab, char **env)
{
	pid_t	pid;

	pid = fork();
	(pid < 0) ? my_exit("Fork Failed", 0) : 0;
	(!pid) ? execve(str, tab, env) : 0;
	waitpid(pid, 0, 0);
	return (true);
}

bool	my_check_access(char **tab, char *str, char **env)
{
	bool	ret;

	ret = false;
	if (!access(str, F_OK) && access(str, X_OK))
	{
		ft_printf("minishell: permission denied: %s\n", str);
		ret = true;
	}
	else if (!access(str, F_OK))
		ret = my_fork_and_exec(str, tab, env);
	return (ret);
}

bool	my_check_path(t_minishell *minishell, char **tab, char **env)
{
	char	**path;
	bool	ret;
	char	*tmp;
	char	*str;
	int		i;

	i = 0;
	tmp = NULL;
	str = NULL;
	ret = false;
	if (!(path = my_find_path(minishell)))
		return (ret);
	while (path[i] && ret == false)
	{
		tmp = ft_strjoin(path[i], "/");
		str = ft_strjoin(tmp, tab[0]);
		(tmp) ? ft_strdel(&tmp) : 0;
		ret = my_check_access(tab, str, env);
		(str) ? ft_strdel(&str) : 0;
		i++;
	}
	(path) ? ft_tabfree(&path) : 0;
	return (ret);
}
