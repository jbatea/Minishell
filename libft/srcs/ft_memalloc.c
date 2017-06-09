/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbateau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 16:28:29 by jbateau           #+#    #+#             */
/*   Updated: 2017/06/09 02:00:19 by jbateau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void		*ft_memalloc(size_t size)
{
	void	*mem;

	mem = (void *)malloc(sizeof(size_t) * (size));
	(!mem) ? MALLOC : 0;
	ft_bzero(mem, size);
	return (mem);
}
