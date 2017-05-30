#include "../includes/minishell.h"

char	*my_home(t_minishell *minishell)
{
	t_env	*tmp;
	
	if ((tmp = my_env_chr(minishell, "HOME")))
		return (tmp->value);
	return ("");
}

t_env	*my_env_chr(t_minishell *minishell, char *cmd)
{
	t_env	*tmp;

	tmp = minishell->env;
	while (tmp)
	{
		if (tmp->key && !ft_strcmp(tmp->key, cmd))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void		my_exit(char *error)
{
	t_minishell	minishell;

	minishell = my_minishell(NULL);
	(error) ? ft_printf("%s\n", error) : 0;
	my_freeenv(&minishell);
	(minishell.tab) ? ft_tabfree(minishell.tab) : 0;
	(minishell.line) ? ft_strdel(&(minishell.line)) : 0;
	exit(EXIT_FAILURE);
}

t_minishell	my_minishell(t_minishell *minishell)
{
	static	t_minishell	save;

	save = ((minishell) ? *minishell : save);
	return (save);
}

