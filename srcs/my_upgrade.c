/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_upgrade.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbateau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 14:40:18 by jbateau           #+#    #+#             */
/*   Updated: 2017/06/09 03:31:35 by jbateau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void				my_empty_env(t_minishell *minishell)
{
	char			cwd[BUF_SIZE];
	char			*tmp;

	ft_bzero(cwd, BUF_SIZE);
	getcwd(cwd, BUF_SIZE);
	tmp = ft_strjoin("PWD=", cwd);
	my_addenv(minishell, tmp, false);
	ft_strdel(&tmp);
	my_addenv(minishell, "SHLVL=1", false);
	my_addenv(minishell, "_=./minishell", false);
}

void				my_update_lvl(t_minishell *minishell)
{
	t_env			*env;
	int				i;

	if (!(env = my_env_chr(minishell, "SHLVL")) || !(env->value))
		return ;
	i = ft_atoi(env->value) + 1;
	ft_strdel(&(env->value));
	env->value = ft_itoa(i);
	my_envjoin(env);
}

void				my_echo(char **tab, bool *k)
{
	int				i;
	int				j;

	j = ((tab[1] && !ft_strcmp(tab[1], "-n")) ? 2 : 1);
	i = j;
	while (tab[i])
	{
		(j != i) ? ft_printf(" ") : 0;
		ft_printf("%s", tab[i]);
		i++;
	}
	(tab[1] && !ft_strcmp(tab[1], "-n")) ? 0 : ft_printf("\n");
	*k = 1;
}

void				my_apply_sigint(int sign)
{
	t_minishell minishell;

	minishell = my_minishell(NULL);
	if (sign == SIGINT)
	{
		ft_printf("\n$> ");
		minishell.display = 1;
		my_minishell(&minishell);
	}
}

void				my_sig_handler(int sign)
{
	(sign == SIGINT) ? my_apply_sigint(sign) : 0;
	(sign == SIGHUP) ? my_exit("minishell: terminal line hangup", 0) : 0;
	if (sign == SIGILL)
		my_exit("minishell: illegal hardware instruction", 0);
	(sign == SIGTRAP) ? my_exit("minishell: trace trap", 0) : 0;
	(sign == SIGABRT) ? my_exit("minishell: abort", 0) : 0;
	(sign == SIGEMT) ? my_exit("minishell: EMT instruction", 0) : 0;
	(sign == SIGFPE) ? my_exit("minishell: floating point exception", 0) : 0;
	(sign == SIGKILL) ? my_exit("minishell: kill program", 0) : 0;
	(sign == SIGBUS) ? my_exit("minishell: bus error", 0) : 0;
	(sign == SIGSEGV) ? my_exit("minishell: segmentation fault", 0) : 0;
	(sign == SIGSYS) ? my_exit("minishell: invalid system call", 0) : 0;
	if (sign == SIGPIPE)
		my_exit("minishell: write on a pipe with no reader", 0);
	(sign == SIGALRM) ? my_exit("minishell: real-time timer expired", 0) : 0;
	(sign == SIGXCPU) ? my_exit("minishell: cpu limit exceeded", 0) : 0;
	(sign == SIGXFSZ) ? my_exit("minishell: file size limit exceeded", 0) : 0;
	(sign == SIGVTALRM) ? my_exit("minishell: virtual time alarm", 0) : 0;
	(sign == SIGPROF) ? my_exit("minishell: profile signal", 0) : 0;
	(sign == SIGUSR1) ? my_exit("minishell: User defined signal 1", 0) : 0;
	(sign == SIGUSR2) ? my_exit("minishell: User defined signal 2", 0) : 0;
}
