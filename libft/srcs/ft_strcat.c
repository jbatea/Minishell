/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbateau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 11:37:05 by jbateau           #+#    #+#             */
/*   Updated: 2015/11/26 13:07:08 by jbateau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char		*ft_strcat(char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	i;

	s1_len = ft_strlen(s1);
	i = 0;
	while (s2[i])
	{
		s1[s1_len + i] = s2[i];
		i++;
	}
	s1[s1_len + i] = '\0';
	return (s1);
}
