/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr_cnt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbateau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 14:49:16 by jbateau           #+#    #+#             */
/*   Updated: 2017/06/07 14:49:38 by jbateau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int			ft_strrchr_cnt(char *s, char c)
{
	int		cnt;

	cnt = ft_strlen(s);
	while (cnt > 0 && s[cnt] != c)
		cnt--;
	if (s[cnt] == c)
		return (cnt);
	return (-1);
}
