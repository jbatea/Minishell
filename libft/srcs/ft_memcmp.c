/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbateau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 18:23:40 by jbateau           #+#    #+#             */
/*   Updated: 2015/12/07 11:25:32 by jbateau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int				ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t		i;
	const char	*str1;
	const char	*str2;

	i = 0;
	str1 = s1;
	str2 = s2;
	if (n == 0)
		return (0);
	while (((i + 1) < n) && ((unsigned char)str1[i] == (unsigned char)str2[i]))
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
