/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 15:21:55 by yalthaus          #+#    #+#             */
/*   Updated: 2021/11/13 15:29:40 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	coin_checker(char **map)
{
	int	x;
	int	y;
	int	coin;

	y = -1;
	coin = 0;
	while (*(map + ++y) != NULL)
	{
		x = -1;
		while (*(*(map + y) + ++x))
			if (*(*(map + y) + x) == 'C')
				coin++;
	}
	if (!coin)
		return (1);
	return (0);
}

int	exit_checker(char **map)
{
	int	x;
	int	y;
	int	exit;

	y = -1;
	exit = 0;
	while (*(map + ++y) != NULL)
	{
		x = -1;
		while (*(*(map + y) + ++x))
			if (*(*(map + y) + x) == 'E')
				exit++;
	}
	if (exit != 1)
		return (1);
	return (0);
}
