/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 15:39:53 by yalthaus          #+#    #+#             */
/*   Updated: 2022/01/31 15:44:22 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include "so_long.h"

void	close_game(t_game *game)
{
	int	x;
	int	y;

	free(game->map->sprite);
	free(game->map->monster_pos);
	free(game->map->player_pos);
	y = -1;
	while (game->map->ymax > ++y)
	{
		x = -1;
		while (game->map->xmax > ++x)
			free(game->map->grid[y][x]);
		free(game->map->grid[y]);
		free(game->map->map[y]);
	}
	free(game->map->grid);
	free(game->map->map);
	free(game->map);
	free(game);
	exit(0);
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
			if (game->map->grid[y][x]->img != NULL
					&& game->map->grid[y][x]->type != monstre)
				mlx_put_image_to_window(game->mlx, game->win,
					game->map->grid[y][x]->img, x * 32, y * 32);
		}
	}
}

t_game	*init_game(int fd)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->mlx = mlx_init();
	init_map(game, fd);
	init_grass(game);
	init_obj(game);
	draw_move(game);
	mlx_hook(game->win, KEY_PRESS, 0, &key_press, game);
	if (game->map->monster_pos)
		mlx_loop_hook(game->mlx, move_monster, game);
	mlx_loop(game->mlx);
	return (game);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_game	*game;

	if (argc != 2)
	{
		write(1, "Nombre argument incorecte", 25);
		return (0);
	}
	if (ft_extension(*(argv + 1), ".ber"))
	{
		write(1, "extension incorrect", 19);
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		write(1, "fichier inexistant", 18);
		return (0);
	}
	game = init_game(fd);
}
