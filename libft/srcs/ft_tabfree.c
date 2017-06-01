#include "../../includes/libft.h"

void	ft_tabfree(char ***tab)
{
	int	i;

	i = 0;
	while ((*tab)[i])
	{
		((*tab)[i]) ? ft_strdel(&(*tab)[i]) : 0;
		i++;
	}
	((*tab)[i]) ? ft_strdel(&(*tab)[i]) : 0;
	(*tab) ? free(*tab) : 0;
	(*tab) = NULL;
}
