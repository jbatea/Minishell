/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbateau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:03:40 by jbateau           #+#    #+#             */
/*   Updated: 2017/06/09 04:05:51 by jbateau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <dirent.h>
# include <time.h>
# include <signal.h>
# include <stdbool.h>
# include "libft.h"

# define BUF_SIZE	256
# define NB_SIGNAL	32

# define SIGEMT 7
# define SIGBUS 10
# define SIGSYS 12
# define SIGXCPU 24
# define SIGXFSZ 25
# define SIGVTALRM 26
# define SIGPROF 27

typedef struct		s_env
{
	char			*env;
	char			*key;
	char			*value;
	char			*old_value;
	bool			tmp;
	bool			close;
	struct s_env	*next;
}					t_env;

typedef struct		s_minishell
{
	t_env			*env;
	bool			error;
	char			*str_error;
	bool			display;
}					t_minishell;

t_minishell			my_minishell(t_minishell *minishell);
void				my_exit(char *error, int n);
void				my_env(t_minishell *minishell, char **tab, bool *i);
void				my_getenv(char **env);
void				my_open_env(t_minishell *minishell);
void				my_addenv(t_minishell *minishell, char *env, bool n);
void				my_freeenv(t_minishell *minishell);
void				my_envjoin(t_env *env);
t_env				*my_env_chr(t_minishell *minishell, char *cmd);
void				my_setenv(t_minishell *minishell, char *tab,\
bool *i, bool n);
void				my_check_cmd(t_minishell *minishell, char **tab);
void				my_cd(t_minishell *minishell, char **tab, bool *i);
char				*my_home(t_minishell *minishell);
bool				my_check_bin(t_minishell *minishell, char **tab);
bool				my_check_path(t_minishell *minishell, char **tab,\
char **env);
bool				my_check_access(char **tab, char *str, char **env);
void				my_printenv(t_minishell *minishell);
void				my_sig_handler(int sign);
void				my_echo(char **tab, bool *k);
void				my_update_lvl(t_minishell *minishell);
void				my_empty_env(t_minishell *minishell);
void				my_pwd_maj(t_minishell *minishell, char *s);

#endif
