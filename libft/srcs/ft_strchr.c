/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbateau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 18:12:55 by jbateau           #+#    #+#             */
/*   Updated: 2015/11/26 14:22:46 by jbateau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char		*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] && c != s[i])
		i++;
	if (c == s[i])
		return ((char *)s + i);
	else
		return (NULL);
}