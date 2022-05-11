/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 11:36:56 by yalthaus          #+#    #+#             */
/*   Updated: 2022/02/14 14:57:10 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_square(char **map)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(*map);
	while (*(map + ++i))
		if (ft_strlen(*(map + i)) != len)
			return (1);
	return (0);
}

int	map_char(char **map)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (*(map + ++y) != NULL)
	{
		x = -1;
		while (*(*(map + y) + ++x))
			if (!ft_isinset(*(*(map + y) + x), "01MCPE"))
				return (1);
	}
	return (0);
}

int	map_border(char **map)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (*(*map + (++x)))
		if (*(*map + x) != '1')
			return (1);
	while (*(map + (++y)))
		if (**(map + y) != '1' || *(*(map + y) + x - 1) != '1')
			return (1);
	x = -1;
	while (*(*(map + (y - 1)) + (++x)))
		if (*(*(map + (y - 1)) + x) != '1')
			return (1);
	return (0);
}

int	player_checker(char **map)
{
	int	x;
	int	y;
	int	player;

	y = -1;
	player = 0;
	while (*(map + ++y) != NULL)
	{
		x = -1;
		while (*(*(map + y) + ++x))
			if (*(*(map + y) + x) == 'P')
				player++;
	}
	if (player != 1)
		return (1);
	return (0);
}

char	*map_checker(char **map)
{
	if (map_char(map))
		return ("Error\nCharactere de la map non reconnu");
	if (map_square(map))
		return ("Error\nLa map n'est pas rectangulaire");
	if (map_border(map))
		return ("Error\nBord de map incorrect");
	if (player_checker(map))
		return ("Error\nNombre de joueur incorect");
	if (exit_checker(map))
		return ("Error\nNombre de sortie incorect");
	if (coin_checker(map))
		return ("Error\nTrop peu de coin sur la map");
	if (monster_checker(map))
		return ("Error\nTrop de monstre sur la map");
	return ("");
}
