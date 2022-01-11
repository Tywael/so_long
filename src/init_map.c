/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 19:36:20 by yalthaus          #+#    #+#             */
/*   Updated: 2022/01/11 10:11:51 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_case(t_game *game, t_case *cell, char c)
{
	if (c == '1')
		cell->img = game->map->sprite->wall;
	else if (c == 'C')
		cell->img = game->map->sprite->coin;
	else if (c == 'P')
		cell->img = game->map->sprite->playerf[0];
	else if (c == 'E')
		cell->img = game->map->sprite->exit;
	else if (c == 'M')
		cell->img = game->map->sprite->slimef;
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
	game->map->grid = (t_case ***)malloc((game->map->ymax + 1)
			* sizeof(t_case **));
	if (game->map->grid == NULL)
		exit(1);
	while (++y < game->map->ymax)
	{
		x = -1;
		game->map->grid[y] = (t_case **)malloc((game->map->xmax + 1)
				* sizeof(t_case *));
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

int	init_pos(int x, int y, char c, t_game *game)
{
	t_pos	*pos;

	pos = (t_pos *)malloc(sizeof(t_pos));
	pos->x = x;
	pos->y = y;
	if (c == 'M')
		game->map->monster_pos = pos;
	else
		game->map->player_pos = pos;
	return (0);
}

void	init_grid(t_game *game)
{
	int		x;
	int		y;

	y = -1;
	while (++y < game->map->ymax)
	{
		x = -1;
		while (++x < game->map->xmax)
		{
			if (game->map->map[y][x] == 'C')
				game->map->ncoin += 1;
			if (game->map->map[y][x] == 'M' || game->map->map[y][x] == 'P')
				init_pos(x, y, game->map->map[y][x], game);
			init_case(game, game->map->grid[y][x], game->map->map[y][x]);
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
	game->map->monster_pos = NULL;
	game->map->sprite = init_sprite(game);
	game->map->xmax = ft_strlen(*(game->map->map));
	game->map->ymax = ft_mapline(game->map);
	game->map->monster_move = 0;
	game->map->monster_side = -1;
	game->win = mlx_new_window(game->mlx, 32 * game->map->xmax,
			32 * game->map->ymax, "Romancing Saga 42");
	malloc_grid(game);
	init_grid(game);
}
