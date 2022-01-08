/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:54:29 by yalthaus          #+#    #+#             */
/*   Updated: 2022/01/08 10:48:27 by yalthaus         ###   ########.fr       */
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
	sprite->w = 32;
	sprite->h = 32;
	sprite->img = mlx_xpm_file_to_image(game->mlx, path, &sprite->w, &sprite->h);
	return (sprite);	
}

t_sprite	**init_player(t_game *game)
{
	t_sprite	**player;

	player = (t_sprite **)malloc(sizeof(t_sprite *) * 8);
	if (player == NULL)
		exit(1);
	player[0] = init_sprite(game, "./assets/player/playerface1.xpm");
	player[1] = init_sprite(game, "./assets/player/playerface2.xpm");
	player[2] = init_sprite(game, "./assets/player/playerback1.xpm");
	player[3] = init_sprite(game, "./assets/player/playerback2.xpm");
	player[4] = init_sprite(game, "./assets/player/playerleft1.xpm");
	player[5] = init_sprite(game, "./assets/player/playerleft2.xpm");
	player[6] = init_sprite(game, "./assets/player/playerright1.xpm");
	player[7] = init_sprite(game, "./assets/player/playerright2.xpm");
	return (player);
}

t_sprite	**init_monster(t_game *game)
{
	t_sprite	**mstr;

	mstr = (t_sprite **)malloc((sizeof(t_sprite *)) * 1);
	*mstr = init_sprite(game, "./assets/monstre/monstre.xpm");
	return (mstr);
}

t_sprite	**init_wall(t_game *game)
{
	t_sprite	**wall;
	
	wall = (t_sprite **)malloc(sizeof(t_sprite *) * 1);
	
	*wall = init_sprite(game, "./assets/terrain/rock.xpm");
	return (wall);
}

t_sprite	**init_exit(t_game *game)
{
	t_sprite	**exit;
	
	exit = (t_sprite **)malloc(sizeof(t_sprite *) * 1);
	*exit = init_sprite(game, "./assets/terrain/exit.xpm");
	return (exit);
}

t_sprite	**init_coin(t_game *game)
{
	t_sprite	**coin;
	
	coin = (t_sprite **)malloc(sizeof(t_sprite *) * 4);
	*coin = init_sprite(game, "./assets/other/coin.xpm");
	return (coin);
}

void	init_case(t_game *game, t_case *cell, char c)
{
	if (c == '1')
		cell->sprite = init_wall(game);
	else if (c == 'C')
	{
		cell->status = 1;
		cell->sprite = init_coin(game); 
	}
	else if (c == 'P')
		cell->sprite = init_player(game); 
	else if (c == 'E')
	{
		cell->status = 0;
		cell->sprite = init_exit(game);
	}
	else if (c == 'M')
	{
		cell->status = 1;
		cell->sprite = init_monster(game);
	}
	else
		cell->sprite = NULL;
	cell->type = c;
	cell->background = init_sprite(game, "./assets/terrain/grass.xpm");
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
			init_case(game, game->map->grid[y][x], game->map->map[y][x]);
			game->map->grid[y][x]->pos = pos;
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
				   	game->map->grid[y][x]->background->img, x * 32, y * 32);
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
			if (game->map->grid[y][x]->sprite != NULL)
				mlx_put_image_to_window(game->mlx, game->win,
					game->map->grid[y][x]->sprite[0]->img, x * 32, y * 32);

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
	mlx_loop(game->mlx);
	return (game);
}
