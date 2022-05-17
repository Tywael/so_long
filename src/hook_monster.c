/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_monster.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 19:13:36 by yalthaus          #+#    #+#             */
/*   Updated: 2022/01/11 10:14:10 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_move(t_game *game)
{
	char	*move;

	mlx_put_image_to_window(game->mlx, game->win, game->map->sprite->move,
		0, 0);
	move = ft_itoa(game->map->move);
	//write(1, move, ft_strlen(move));
	//write(1, "\n", 1);
	mlx_string_put(game->mlx, game->win, 5, 16, 0x99000000,
		"Movements : ");
	mlx_string_put(game->mlx, game->win, 100, 16, 0x99000000,
		move);
	free(move);
}

void	anim_monster(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win,
		game->map->sprite->background, (game->map->monster_pos->x
			+ game->map->monster_side) * 32, game->map->monster_pos->y * 32);
	mlx_put_image_to_window(game->mlx, game->win,
		game->map->sprite->background, game->map->monster_pos->x * 32,
		game->map->monster_pos->y * 32);
	if (game->map->monster_side == -1)
		mlx_put_image_to_window(game->mlx, game->win,
			game->map->sprite->slimel[game->map->monster_move % 4],
			game->map->monster_pos->x * 32
			+ (game->map->monster_side * (game->map->monster_move % 4
					+ 1) * 8), game->map->monster_pos->y * 32);
	else
		mlx_put_image_to_window(game->mlx, game->win,
			game->map->sprite->slimer[game->map->monster_move % 4],
			game->map->monster_pos->x * 32
			+ (game->map->monster_side * (game->map->monster_move % 4
					+ 1) * 8), game->map->monster_pos->y * 32);
	usleep(100000);
}

void	move_monster2(t_game *game)
{
	if (game->map->monster_move < 12)
		game->map->monster_side = -1;
	else
		game->map->monster_side = 1;
	if (game->map->monster_move == 24)
	{
		game->map->monster_move = 0;
		game->map->monster_side = -1;
	}
}

int	move_monster(t_game *game)
{
	if (game->map->grid[game->map->monster_pos->y][game->map->monster_pos->x
		+ game->map->monster_side]->type == player)
		exit(1);
	if (game->map->monster_move % 4 == 0
		&& game->map->grid[game->map->monster_pos->y]
		[game->map->monster_pos->x
			+ game->map->monster_side]->type == empty)
	{
		game->map->grid[game->map->monster_pos->y]
		[game->map->monster_pos->x]->type = empty;
		game->map->grid[game->map->monster_pos->y]
		[game->map->monster_pos->x
			+ game->map->monster_side]->type = monstre;
		game->map->monster_pos->x += game->map->monster_side;
		usleep(300000);
	}
	if (game->map->grid[game->map->monster_pos->y]
		[game->map->monster_pos->x + game->map->monster_side]->type
		== empty)
		anim_monster(game);
	move_monster2(game);
	game->map->monster_move++;
	return (0);
}
