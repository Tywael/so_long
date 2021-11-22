/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:54:29 by yalthaus          #+#    #+#             */
/*   Updated: 2021/11/22 18:09:28 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_player(t_pose pos)
{
	t_player player;

	player = (t_player *)malloc(sizeof(t_player));
	if (player == NULL)
		exit(1);
	player->name = "Tywael";
	player->life = 100;
	player->lifemax = 100;
	player->pos = pos;
	
}

void	*init_monstre(t_pose pose)
{
	t_monstre *mstr;

	mstr = (t_monstre *)malloc(sizeof(t_monstre));
	if (mstr == NULL)
		exit(1);
	mstr->name = "Musty le dragon";
	mstr->life = 1000;
	mstr->lifemax = 1000;
	mstr->pos = pose;
	return (mstr);
}

void	init_case(t_case *cell, char c, t_pose *pose)
{
	if (c == '1')
		cell->content = init_wall(pose);
	else if (c == 'C')
		cell->content = init_coin(pose);
	else if (c == 'P')
		cell->content = init_player(pose);
	else if (c == 'E')
		cell->content = init_exit(map, pose);
	else if (c == 'M')
		cell->content = init_monster(map, pose);
	else
		cell->content = NULL;
	cell->type = c;
}
void	malloc_grid(t_map *map)
{
	int		x;
	int		y;

	y = -1;
	map->grid = (t_case ***)malloc(map->ymax + 1);
	if (map->grid == NULL)
		exit(1);
	while (++y < map->ymax)
	{
		x = -1;
		map->grid[y] = (t_case **)malloc(map->xmax + 1);
		if (map->grid[y] == NULL)
			exit(1);
		while (++x < map->xmax)
		{
			map->grid[y][x] = (t_case *)malloc(sizeof(t_case));
			if (map->grid[y][x] == NULL)
				exit(1);
		}
		map->grid[y][x] = NULL;
	}
	map->grid[y] = NULL;
}

void	init_grid(t_map *map)
{
	int		x;
	int		y;
	t_pose	*pose;

	y = -1;
	while (++y < map->ymax)
	{
		x = -1;
		while (++x < map->xmax)
		{
			pose = (t_pose *)malloc(sizeof(t_pose));
			pos->x = x;
			pos->y = y;
			init_case(map->grid[y][x], map->map[y][x], pose);
		}
	}
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
	if (ft_putstr(map_checker(game->map->map)))
		exit(1);
	map->move = 0;
	map->xmax = ft_strlen(*(map->map));
	map->ymap = ft_mapline(map);
	init_grid(map);
	return (map);
}

t_game	*init_game(int fd)
{
	t_game *game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->map = init_map(fd);
		return (0);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1920, 1080, "Romancing Saga 42");
	mlx_loop(game->mlx);
}


