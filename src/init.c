/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:54:29 by yalthaus          #+#    #+#             */
/*   Updated: 2022/01/08 18:06:03 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

t_sprite *init_sprite(t_game *game)
{
	t_sprite	*sprite;

	sprite = (t_sprite *)malloc(sizeof(t_sprite));
	if (sprite == NULL)
		exit (1);
	sprite->w = 32;
	sprite->h = 32;
	sprite->playerf1 = mlx_xpm_file_to_image(game->mlx,"./assets/player/playerface1.xpm", &sprite->w, &sprite->h);
	sprite->playerf2 = mlx_xpm_file_to_image(game->mlx,"./assets/player/playerface2.xpm", &sprite->w, &sprite->h);
	sprite->playerb1 = mlx_xpm_file_to_image(game->mlx,"./assets/player/playerback1.xpm", &sprite->w, &sprite->h);
	sprite->playerb2 = mlx_xpm_file_to_image(game->mlx,"./assets/player/playerback2.xpm", &sprite->w, &sprite->h);
	sprite->playerl1 = mlx_xpm_file_to_image(game->mlx,"./assets/player/playerleft1.xpm", &sprite->w, &sprite->h);
	sprite->playerl2 = mlx_xpm_file_to_image(game->mlx,"./assets/player/playerleft2.xpm", &sprite->w, &sprite->h);
	sprite->playerr1 = mlx_xpm_file_to_image(game->mlx,"./assets/player/playerright1.xpm", &sprite->w, &sprite->h);
	sprite->playerr2 = mlx_xpm_file_to_image(game->mlx,"./assets/player/playerright2.xpm", &sprite->w, &sprite->h);
	sprite->exit = mlx_xpm_file_to_image(game->mlx, "./assets/terrain/exit.xpm", &sprite->w, &sprite->h);
	sprite->coin = mlx_xpm_file_to_image(game->mlx, "./assets/other/coin.xpm", &sprite->w, &sprite->h);
	sprite->wall = mlx_xpm_file_to_image(game->mlx, "./assets/terrain/rock.xpm", &sprite->w, &sprite->h);
	sprite->background = mlx_xpm_file_to_image(game->mlx, "./assets/terrain/grass.xpm", &sprite->w, &sprite->h);
	sprite->monster = NULL;
	return (sprite);	
}

void	init_case(t_game *game, t_case *cell, char c, t_pos *pos)
{
	if (c == '1')
		cell->img = game->map->sprite->wall;
	else if (c == 'C')
	{
		cell->status = 0;
		cell->img =  game->map->sprite->coin;
	}
	else if (c == 'P')
	{
		cell->old_type = empty;
		cell->img =  game->map->sprite->playerf1; 
		game->map->player_pos = pos;
	}
	else if (c == 'E')
	{
		cell->status = 0;
		cell->img =  game->map->sprite->exit;
	}
	else if (c == 'M')
		cell->img = game->map->sprite->monster;
	else
		cell->img = NULL;
	cell->type = c;
	cell->background = game->map->sprite->background;
}

void	malloc_grid(t_game *game)
{
	int		x;
	int		y;

	y = -1;
	game->map->grid = (t_case ***)malloc((game->map->ymax + 1) * sizeof(t_case **));
	if (game->map->grid == NULL)
		exit(1);
	while (++y < game->map->ymax)
	{
		x = -1;
		game->map->grid[y] = (t_case **)malloc((game->map->xmax + 1) * sizeof(t_case *));
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
			if (game->map->map[y][x] == 'C')
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
	game->map->sprite = init_sprite(game);
	game->map->xmax = ft_strlen(*(game->map->map));
	game->map->ymax = ft_mapline(game->map);
	game->win = mlx_new_window(game->mlx, 32 * game->map->xmax, 32 * game->map->ymax , "Romancing Saga 42");
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
				   	game->map->grid[y][x]->background, x * 32, y * 32);
		}
	}	
}

void	init_obj(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < game->map->ymax)
	{
		x = -1;
		while (++x < game->map->xmax)
		{
			if (game->map->grid[y][x]->img != NULL)
				mlx_put_image_to_window(game->mlx, game->win,
					game->map->grid[y][x]->img, x * 32, y * 32);

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
	init_map(game, fd);
	init_grass(game);
	init_obj(game);
	mlx_hook(game->win, KEY_PRESS, 0, &key_press, game);
	mlx_loop(game->mlx);
	return (game);
}
