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

bool	my_check_path(t_minishell *minishell, char **tab, char **env)
{
	char	**path;
	bool	ret;
	char	*tmp;
	char	*str;
	int	i;

	i = 0;
	tmp = NULL;
	str = NULL;
	ret = false;
	if (!(path = my_find_path(minishell)))
		return (ret);
	while (path[i] && ret == false)
	{
		(tmp = ft_strjoin(path[i], "/")) ? 0 : MALLOC;
		(str = ft_strjoin(tmp, tab[0])) ? 0 : MALLOC;
		(tmp) ? ft_strdel(&tmp) : 0;
		ret = my_check_access(tab, str, env);
		(str) ? ft_strdel(&str) : 0;
		i++;
	}
	(path) ? ft_tabfree(&path) : 0;
	return (ret);
}

