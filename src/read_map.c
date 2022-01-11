/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:04:45 by yalthaus          #+#    #+#             */
/*   Updated: 2022/01/11 09:50:00 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**read_map(int fd)
{
	char	**ret;
	char	*tmp;
	int		i;

	i = 0;
	ret = (char **)malloc(sizeof(char *));
	*ret = NULL;
	while (1)
	{
		tmp = get_next_line(fd);
		if (tmp)
		{
			i++;
			ret = (char **)ft_realloc(ret, sizeof(char *)
					* (i + 1));
			*(ret + i - 1) = tmp;
		}
		else
			break ;
	}
	*(ret + i) = NULL;
	return (ret);
}
