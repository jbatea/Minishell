/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbateau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 12:54:38 by jbateau           #+#    #+#             */
/*   Updated: 2017/06/09 02:03:40 by jbateau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char		*ft_strndup(const char *s1, size_t n)
{
	char	*tmp;
	size_t	i;

	i = 0;
	tmp = ft_strnew(n + 2);
	(!tmp) ? MALLOC : 0;
	while (i < n && s1[i])
	{
		tmp[i] = s1[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
