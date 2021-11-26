/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:54:29 by yalthaus          #+#    #+#             */
/*   Updated: 2021/11/26 17:29:33 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

t_sprite *init_sprite(t_game *game, char *path)
{
	t_sprite	*sprite;

	sprite = (t_sprite *)malloc(sizeof(t_sprite));
	if (sprite == NULL)
		exit (1);
	sprite->sprite = mlx_xpm_file_to_image(game->mlx, path, &sprite->w, &sprite->h);
	return (sprite);	
}

void	*init_player(t_game *game, t_pos *pos)
{
	t_player *player;

	player = (t_player *)malloc(sizeof(t_player));
	if (player == NULL)
		exit(1);
	player->name = "Tywael";
	player->life = 100;
	player->lifemax = 100;
	player->pos = pos;
	player->back[0] = init_sprite(game, "./assets/player/playerback1.xpm");
	return (player);
}

void	*init_monster(t_game *game, t_pos *pos)
{
	t_monstre *mstr;

	mstr = (t_monstre *)malloc(sizeof(t_monstre));
	if (mstr == NULL)
		exit(1);
	mstr->name = "Musty le dragon";
	mstr->life = 1000;
	mstr->lifemax = 1000;
	mstr->pos = pos;
	mstr->img[0] = init_sprite(game, "./assets/monstre/monstre.xpm");
	return (mstr);
}

void	*init_wall(t_game *game, t_pos *pos)
{
	t_wall	*wall;
	
	wall = (t_wall *)malloc(sizeof(t_wall));
	wall->pos = pos;
	wall->wall = init_sprite(game, "./assets/terrain/rock.xpm");
	return (wall);
}

void	*init_exit(t_game *game, t_pos *pos)
{
	t_exit	*exit;
	
	exit = (t_exit *)malloc(sizeof(t_exit));
	exit->pos = pos;
	exit->exit = init_sprite(game, "./assets/terrain/exit.xpm");
	return (exit);
}

void	*init_coin(t_game *game, t_pos *pos)
{
	t_coin	*coin;
	
	coin = (t_coin *)malloc(sizeof(t_coin));
	coin->pos = pos;
	coin->coin[0] = init_sprite(game, "./assets/terrain/coin.xpm");
	return (coin);
}

void	init_case(t_game *game, t_case *cell, char c, t_pos *pos)
{
//	if (c == '1')
//		cell->content = init_wall(game, pos);
//	else if (c == 'C')
//		cell->content = init_coin(game, pos);
//	else if (c == 'P')
//		cell->content = init_player(game, pos);
//	else if (c == 'E')
//		cell->content = init_exit(game, pos);
//	else if (c == 'M')
//		cell->content = init_monster(game, pos);
//	else
//		cell->content = NULL;
	(void)pos;
	cell->type = c;
	cell->background = init_sprite(game, "./assets/terrain/grass.xpm");
}

void	malloc_grid(t_game *game)
{
	int		x;
	int		y;

	y = -1;
	game->map->grid = (t_case ***)malloc(game->map->ymax + 1);
	if (game->map->grid == NULL)
		exit(1);
	while (++y < game->map->ymax)
	{
		x = -1;
		game->map->grid[y] = (t_case **)malloc(game->map->xmax + 1);
		if (game->map->grid[y] == NULL)
			exit(1);
		while (++x < game->map->xmax)
		{
			game->map->grid[y][x] = (t_case *)malloc(sizeof(t_case));
			if (game->map->grid[y][x] == NULL)
				exit(1);
		}
		game->map->grid[y][x] = NULL;
	}
	game->map->grid[y] = NULL;
}

void	init_grid(t_game *game)
{
	int		x;
	int		y;
	t_pos	*pos;

	y = -1;
	while (++y < game->map->ymax)
	{
		x = -1;
		while (++x < game->map->xmax)
		{
			if (game->map->map[x][y] == 'C')
				game->map->ncoin += 1;
			pos = (t_pos *)malloc(sizeof(t_pos));
			pos->x = x;
			pos->y = y;
			init_case(game, game->map->grid[y][x], game->map->map[y][x], pos);
		}
	}
}


void	init_map(t_game *game, int fd)
{
	game->map = (t_map *)malloc(sizeof(t_map));
	if (game->map == NULL)
		exit(1);
	game->map->map = read_map(fd);
	if (ft_putstr(map_checker(game->map->map)))
		exit(1);
	game->map->move = 0;
	game->map->ncoin = 0;
	game->map->xmax = ft_strlen(*(game->map->map));
	game->map->ymax = ft_mapline(game->map);
	malloc_grid(game);
	init_grid(game);
}

void	init_grass(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < game->map->ymax)
	{
		x = -1;
		while (++x < game->map->xmax)
		{
			mlx_put_image_to_window(game->mlx, game->win,
				   	game->map->grid[y][x]->background->sprite, x * 32, y * 32);
		}
	}	
}

t_game	*init_game(int fd)
{
	t_game *game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1920, 1080, "Romancing Saga 42");
	init_map(game, fd);
	//init_grass(game);
	return (game);
}
