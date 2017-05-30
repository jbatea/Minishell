/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eolflag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbateau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 18:47:11 by jbateau           #+#    #+#             */
/*   Updated: 2016/03/16 13:59:10 by jbateau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int			ft_eolflag(char *tmp)
{
	int		i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i + 1] && tmp[i + 2] == '\0' &&
				ft_isflag(tmp[i + 1]) == 1 && tmp[i] == '%')
			return (1);
		if (!tmp[i + 1] && (ft_isflag(tmp[i]) == 1 || tmp[i] == '%'))
			return (1);
		i++;
	}
	return (0);
}
