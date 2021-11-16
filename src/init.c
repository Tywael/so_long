/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:54:29 by yalthaus          #+#    #+#             */
/*   Updated: 2021/11/16 16:50:08 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_player(t_map *map)
{
	map->player->name = "Tywael";
	map->player->life = 100;
	map->player->lifemax = 100;
	map->player->back[0]->sprite = init_sprite();
	
}

t_monstre	*init_monstre(t_map *map)
{

}

t_case	*init_case(t_map *map)
{

}

t_capacity	*init_capacity(t_map *map)
{

}

t_sprite init_sprite(char *path)
{
	
}

t_map	*init_map(int fd)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->map = read_map(fd);
	map->move = 0;
	map->xmax = ft_strlen(*(map->map));
	map->ymap = ft_mapline(map);
	init_player(map);
	init_monstre(map);
	init_case(map);
	init_capacity(map);
	return (map);
}


t_game	*init_game(int fd)
{
	t_game *game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->map = init_map(fd);
	if (ft_putstr(map_checker(game->map->map)))
		return (0);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1920, 1080, "Romancing Saga 42");
	mlx_loop(game->mlx);
}


