/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbateau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 18:37:14 by jbateau           #+#    #+#             */
/*   Updated: 2017/06/09 01:58:49 by jbateau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	char		*scat;
	int			i;
	int			j;

	i = 0;
	j = 0;
	scat = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	(!scat) ? MALLOC : 0;
	while (s1[i])
	{
		scat[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		scat[i] = s2[j];
		i++;
		j++;
	}
	scat[i] = '\0';
	return (scat);
}
