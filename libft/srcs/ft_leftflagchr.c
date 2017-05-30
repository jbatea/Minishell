/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_leftflagchr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbateau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 14:00:33 by jbateau           #+#    #+#             */
/*   Updated: 2016/03/19 17:24:24 by jbateau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int			ft_leftflagchr(char *str)
{
	int		i;

	i = 1;
	while (str[i] && ft_basicflags(str[i]))
	{
		if (str[i] == '-')
			return (1);
		i++;
	}
	return (0);
}
