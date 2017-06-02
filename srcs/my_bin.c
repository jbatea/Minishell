#include "../includes/minishell.h"

char	**my_find_path(t_minishell *minishell)
{
	t_env	*env;
	char	**path;

	path = NULL;
	env = my_env_chr(minishell, "PATH");
	if (env->close)
		return (path);
	if (env && env->value)
		(path = ft_strsplit(env->value, ':')) ? 0 : MALLOC;
	return (path);
}

int	my_env_len(t_minishell *minishell)
{
	t_env	*env;
	int	i;

	i = 0;
	env = minishell->env;
	while (env)
	{
		(env->env && !(env->close)) ? i++ : 0;
		env = env->next;
	}
	return (i);
}

void	my_printtab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_printf("%s\n", tab[i], i);
		i++;
	}
}

char	**my_env_tab(t_minishell *minishell)
{
	char	**tab;
	t_env	*env;
	int	i;
	int	j;

	j = 0;
	tab = NULL;
	if ((env = minishell->env))
	{
		i = my_env_len(minishell);
		(tab = (char **)malloc(sizeof(char *) * (i + 1))) ? 0 : MALLOC;
		while (env)
		{
			if (env->env && !(env->close))
			{
				(tab[j] = ft_strdup(env->env)) ? 0 : MALLOC;
				j++;
			}
			env = env->next;
		}
		tab[j] = NULL;
	}
	return (tab);
}

bool	my_fork_and_exec(char *str, char **tab, char **env)
{
	pid_t	pid;

	pid = fork();
	(pid < 0) ? my_exit("Fork Failed") : 0;
	(!pid) ? execve(str, tab, env) : 0;
	waitpid(pid, 0, 0);
	return (true);
}

bool	my_check_access(char **tab, char *str, char **env)
{
	bool	ret;

	ret = false;
	if (!access(str, F_OK))
		ret = my_fork_and_exec(str, tab, env);
	return (ret);
}

bool	my_check_bin(t_minishell *minishell, char **tab)
{
	char	**path;
	int	i;
	char	*tmp;
	char	*str;
	bool	ret;
	char	**env;

	i = 0;
	tmp = NULL;
	str = NULL;
	ret = false;
	env = my_env_tab(minishell);
	path = my_find_path(minishell);
	if (path)
	{
		while (path[i] && ret == false)
		{
			(tmp = ft_strjoin(path[i], "/")) ? 0 : MALLOC;
			(str = ft_strjoin(tmp, tab[0])) ? 0 : MALLOC;
			(tmp) ? ft_strdel(&tmp) : 0;
			ret = my_check_access(tab, str, env);
			(str) ? ft_strdel(&str) : 0;
			i++;
		}
	}
	else
		ret = my_check_access(tab, tab[0], env);
	(path) ? ft_tabfree(&path) : 0;
	(env) ? ft_tabfree(&env) : 0;
	return (ret);
}
