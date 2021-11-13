/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 11:59:34 by yalthaus          #+#    #+#             */
/*   Updated: 2021/11/13 15:17:29 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	return (write(1, s, ft_strlen(s)));
}

int	ft_extension(char *name, char *ext)
{
	int	i;
	int	len;
	int	lext;

	lext = ft_strlen(ext);
	len = ft_strlen(name);
	i = 1;
	if (lext > len)
		return (1);
	while (*(name + len - i) == *(ext + lext - i))
		if (i++ == lext)
			return (0);
	return (1);
}

int	ft_isinset(char c, char *set)
{
	while (*set && c != *set)
		set++;
	return (*set);
}
