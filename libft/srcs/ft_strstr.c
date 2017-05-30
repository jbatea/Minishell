/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbateau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 14:32:55 by jbateau           #+#    #+#             */
/*   Updated: 2016/02/26 18:36:40 by jbateau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char		*ft_strstr(const char *s1, const char *s2)
{
	int		i;
	int		j;

	i = 0;
	if (s2[i] == '\0')
		return ((char *)s1);
	while (s1[i])
	{
		j = 0;
		while ((s1[i] == s2[j]) && s2[j])
		{
			i++;
			j++;
		}
		i = i - j;
		if (s2[j] == '\0')
			return ((char *)s1 + i);
		i++;
	}
	return (NULL);
}
