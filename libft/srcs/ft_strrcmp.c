/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbateau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 14:48:45 by jbateau           #+#    #+#             */
/*   Updated: 2017/06/07 14:49:01 by jbateau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int			ft_strrcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	while (((unsigned char)s1[i] == (unsigned char)s2[i]) && s1[i])
		i++;
	return ((unsigned char)s2[i] - (unsigned char)s1[i]);
}
