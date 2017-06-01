#include "../includes/minishell.h"

char	**my_find_path(t_minishell *minishell)
{
	t_env	*env;
	char	**path;

	path = NULL;
	env = my_env_chr(minishell, "PATH");
	if (env && env->value)
		(path = ft_strsplit(env->value, ':')) ? 0 : MALLOC;
	return (path);
}

/*char	**my_env_tab(t_minishell *minishell)
{
	char	**env;
	int	i;
	int	j;

	j = 0;
	i = ft_env_len(minishell);
	(env = (char **)malloc(sizeof(char *) * (i + 1))) ? 0 : MALLOC;
	while (j < i)
	{
		(env[j] = (char *)malloc(sizeof(char) * env
		j++;
	}
}*/

//VOID MY FORK AND EXECVE

bool	my_check_access(t_minishell *minishell, char *str, char **tab)
{
	bool	ret;
	//char	**env;

	ret = false;
	(void)minishell;
	//env = my_env_tab(minishell);
	if (!access(tab[0], F_OK))
	{
		//FORK
		//execve(tab[0], tab + 1, env);
		ret = true;
	}
	if (!access(str, F_OK))
	{
		//FORK
		//execve(str, tab + 1, env);
		ret = true;
	}
	//(env) ? ft_strdel(&env) : 0;
	return (ret);
}

bool	my_check_bin(t_minishell *minishell, char **tab)
{
	char	**path;
	int	i;
	char	*tmp;
	char	*str;
	bool	ret;

	i = 0;
	tmp = NULL;
	str = NULL;
	ret = false;
	if (!(path = my_find_path(minishell)))
		return (false);
	while (path[i] && ret == false)
	{
		(tmp = ft_strjoin(path[i], "/")) ? 0 : MALLOC;
		(str = ft_strjoin(tmp, tab[0])) ? 0 : MALLOC;
		(tmp) ? ft_strdel(&tmp) : 0;
		ret = my_check_access(minishell, str, tab);
		(str) ? ft_strdel(&str) : 0;
		i++;
	}
	(path) ? ft_tabfree(&path) : 0;
	return (ret);
}
