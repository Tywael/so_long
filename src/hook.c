/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 10:49:44 by yalthaus          #+#    #+#             */
/*   Updated: 2022/01/11 09:55:56 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	can_go(int x, int y, t_game *game)
{
	if (game->map->grid[y][x]->type == wall)
		return (0);
	else if (game->map->grid[y][x]->type == monstre)
		close_game(game);
	else if (game->map->grid[y][x]->type == coin)
	{
		game->map->ncoin--;
		return (1);
	}
	else if (game->map->grid[y][x]->type == end)
	{
		if (game->map->ncoin == 0)
			close_game(game);
		else
			return (0);
	}
	return (1);
}

int	sprite_update(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win,
		game->map->grid[y][x]->background, x * 32, y * 32);
	if (game->map->grid[y][x]->img != NULL)
		mlx_put_image_to_window(game->mlx, game->win,
			game->map->grid[y][x]->img, x * 32, y * 32);
	return (0);
}

int	move_player(int x, int y, t_game *game, int keycode)
{
	void	*sprite;

	sprite = game->map->sprite->playerf[0];
	if (keycode == KEY_D)
		sprite = game->map->sprite->playerr[game->map->move % 2];
	if (keycode == KEY_W)
		sprite = game->map->sprite->playerb[game->map->move % 2];
	if (keycode == KEY_S)
		sprite = game->map->sprite->playerf[game->map->move % 2];
	if (keycode == KEY_A)
		sprite = game->map->sprite->playerl[game->map->move % 2];
	game->map->grid[game->map->player_pos->y][game->map->player_pos->x]->img
		= NULL;
	game->map->grid[y][x]->img = sprite;
	game->map->grid[game->map->player_pos->y][game->map->player_pos->x]->type
		= empty;
	game->map->grid[y][x]->type = player;
	sprite_update(game, x, y);
	sprite_update(game, game->map->player_pos->x, game->map->player_pos->y);
	game->map->player_pos->x = x;
	game->map->player_pos->y = y;
	return (0);
}

int	player_move(int keycode, t_game *game)
{
	int	x;
	int	y;

	x = game->map->player_pos->x;
	y = game->map->player_pos->y;
	if (keycode == KEY_A)
		--x;
	else if (keycode == KEY_D)
		++x;
	else if (keycode == KEY_W)
		y--;
	else if (keycode == KEY_S)
		y++;
	if (can_go(x, y, game))
	{
		move_player(x, y, game, keycode);
		game->map->move++;
	}
	draw_move(game);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S
		|| keycode == KEY_D)
		if (player_move(keycode, game))
			return (1);
	return (0);
}
