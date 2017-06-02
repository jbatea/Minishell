#include "../includes/minishell.h"

void		my_freeenv(t_minishell *minishell)
{
	t_env	*tmp;
	t_env	*ptmp;

	tmp = minishell->env;
	while (tmp)
	{
		ptmp = tmp->next;
		(tmp->key) ? ft_strdel(&(tmp->key)) : 0;
		(tmp->value) ? ft_strdel(&(tmp->value)) : 0;
		(tmp->env) ? ft_strdel(&(tmp->env)) : 0;
		ft_memdel((void **)&tmp);
		tmp = ptmp;
	}
}

void		my_addenv(t_minishell *minishell, char *env)
{
	t_env	*tmp;
	t_env	*new;
	int	i;

	(new = ft_memalloc(sizeof(t_env))) ? 0 : MALLOC;
	if ((i = ft_strchr_cnt(env, '=')) > 0)
	{
		(new->key = ft_strndup(env, i)) ? 0 : MALLOC;
		(new->value = ft_strdup(env + i + 1)) ? 0 : MALLOC;
	}
	else
		(new->key = ft_strdup(env)) ? 0 : MALLOC;
	my_envjoin(new);
	tmp = minishell->env;
	if (!tmp)
		minishell->env = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void		my_getenv(char **env)
{
	int		i;
	t_minishell minishell;

	minishell = my_minishell(NULL);
	i = 0;
	while (env[i])
	{
		my_addenv(&minishell, env[i]);
		i++;
	}
	my_minishell(&minishell);
}

void		my_printenv(t_minishell *minishell)
{
	t_env	*env;

	env = minishell->env;
	if (!my_env_chr(minishell, "PATH") /*&& CHECK BIN*/)
		return;
	while (env)
	{
		(env->env) ? ft_printf("%s\n", env->env) : 0;
		env = env->next;
	}
}

char		**my_new_args(char **tab)
{
	char	**args;
	int	i;
	int	j;

	i = 0;
	j = 0;
	args = NULL;
	while (tab[i])
		i++;
	(args = (char **)malloc(sizeof(char *) * i)) ? 0 : MALLOC;
	i = 1;
	while (tab[i])
	{
		(args[j] = ft_strdup(tab[i])) ? 0 : MALLOC;
		i++;
		j++;
	}
	args[j] = NULL;
	return (args);
}

void		my_env(t_minishell *minishell, char **tab, bool *i)
{
	char	**args;

	*i = 1;
	args = NULL;
	if (tab[1] && !ft_strcmp("-i", tab[1]) && !tab[2])
		return ;
	if (!tab[1])
		my_printenv(minishell);
	else
	{
		args = my_new_args(tab);
		(!my_check_bin(minishell, args)) ? (*i = 0) : 0;
		(args) ? ft_tabfree(&args) : 0;
	}
}

