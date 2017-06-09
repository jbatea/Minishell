/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbateau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 02:15:34 by jbateau           #+#    #+#             */
/*   Updated: 2017/06/09 02:19:36 by jbateau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strspace(char *str)
{
	int		i;
	char	*trim;

	i = 0;
	trim = ft_memalloc(ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '\t' || str[i] == '\n')
			trim[i] = ' ';
		else
			trim[i] = str[i];
		i++;
	}
	trim[i] = '\0';
	return (trim);
}
