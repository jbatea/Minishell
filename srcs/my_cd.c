#include "../includes/minishell.h"

void	my_pwd_maj(t_minishell *minishell)
{
	char	tmp[BUF_SIZE];
	t_env	*pwd;
	t_env	*o_pwd;

	ft_bzero(tmp, BUF_SIZE);
	getcwd(tmp, BUF_SIZE);
	pwd = my_env_chr(minishell, "PWD");
	o_pwd = my_env_chr(minishell, "OLDPWD");
	(o_pwd && o_pwd->value) ? ft_strdel(&(o_pwd->value)) : 0;
	o_pwd->value = ((pwd && pwd->value) ? ft_strdup(pwd->value) : NULL);
	(pwd && pwd->value) ? ft_strdel(&(pwd->value)) : 0;
	pwd->value = ((tmp[0]) ? ft_strdup(tmp) : NULL);
}

void	my_check_cd(t_minishell *minishell, char *path)
{
	if (access(path, F_OK))
		ft_printf("cd: no such file or directory: %s\n", path);
	else if (access(path, R_OK))
		ft_printf("cd: permission denied %s\n", path);
	if (!chdir(path))
		my_pwd_maj(minishell);
}

void	my_cd(t_minishell *minishell)
{
	char	*tmp;
	t_env	*env;

	if (minishell->tab[1])
	{
		if (!ft_strcmp(minishell->tab[1], "-"))
		{
			env = my_env_chr(minishell, "OLDPWD");
			(env && env->value) ? my_check_cd(minishell, env->value) : my_check_cd(minishell, my_home(minishell));
		}
		else
		{
			if (minishell->tab[1][0] == '~')
			{
				(tmp = ft_strdup(minishell->tab[1] + 1)) ? 0 : MALLOC;
				ft_strdel(&(minishell->tab[1]));
				(minishell->tab[1] = ft_strjoin(my_home(minishell), tmp)) ? 0 : MALLOC;
				ft_strdel(&tmp);	
			}
			my_check_cd(minishell, minishell->tab[1]);
		}
	}
	else
		my_check_cd(minishell, my_home(minishell));
}
