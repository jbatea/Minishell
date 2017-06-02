#ifndef MINSIHELL_H
#define MINISHELL_H
			/*Includes*/

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <time.h>
#include <stdbool.h>
#include "libft.h"

#define MALLOC		my_exit("Malloc Failed");
#define BUF_SIZE	256

typedef struct		s_env
{
	char		*env;
	char		*key;
	char		*value;
	struct s_env	*next;
}			t_env;

typedef struct		s_minishell
{
	t_env		*env;
}			t_minishell;

t_minishell	my_minishell(t_minishell *minishell);
void		my_exit(char *error);
void		my_env(t_minishell *minishell, char **tab, bool *i);
void		my_getenv(char **env);
void		my_addenv(t_minishell *minishell, char *env);
void		my_freeenv(t_minishell *minishell);
void		my_check_cmd(t_minishell *minishell, char **tab);
void		my_cd(t_minishell *minishell, char **tab, bool *i);
t_env		*my_env_chr(t_minishell *minishell, char *cmd);
char		*my_home(t_minishell *minishell);
bool		my_check_bin(t_minishell *minishell, char **tab);
void		my_envjoin(t_env *env);

#endif
